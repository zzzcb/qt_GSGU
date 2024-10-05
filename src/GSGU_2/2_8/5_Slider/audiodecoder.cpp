#include "audiodecoder.h"

#include <QDebug>

#include "global.h"

bool AudioDecoder::decode(const QString& filePath)
{
	//初始化/注册编解码器/注册格式等
	av_register_all();

	//打开容器
	AVFormatContext* pFormatCtxt = nullptr;
	if (avformat_open_input(&pFormatCtxt, filePath.toStdString().c_str(), nullptr, nullptr) < 0)
	{
		qDebug() << "avformat_open_input err";
		return false;
	}
	//打开流
	if (avformat_find_stream_info(pFormatCtxt, nullptr) < 0)
	{
		qDebug() << "avformat_find_stream_info err";
		return false;
	}

	//查找音频流索引及其解码器
	AVCodec* pDecoder = nullptr;
	int audioIndex = av_find_best_stream(pFormatCtxt, AVMEDIA_TYPE_AUDIO, -1, -1, &pDecoder, 0);
	if (audioIndex < 0)
	{
		qDebug() << "av_find_best_stream err";
		return false;
	}

	//初始化decoder的上下文
	AVCodecParameters* pDecoderParm = pFormatCtxt->streams[audioIndex]->codecpar;
	AVCodecContext* pDecoderCtx = avcodec_alloc_context3(pDecoder);
	if (!pDecoderCtx)
	{
		qDebug() << "avcodec_alloc_context3 err";
		return false;
	}
	avcodec_parameters_to_context(pDecoderCtx, pDecoderParm);
	//打开解码器上下文
	if (avcodec_open2(pDecoderCtx, pDecoder, nullptr) < 0)
	{
		qDebug() << "avcodec_open2 err";
		return false;
	}
	
	// 手动设置 channel_layout( wav 格式需要设置) 
	// 对于某些编解码器，尤其是老旧或特殊的编解码器，FFmpeg 可能不会自动推断 channel_layout。在这种情况下，需要手动设置它。
	if (pDecoderCtx->channel_layout == 0) 
	{
		// 根据声道数量推断声道布局
		pDecoderCtx->channels = pDecoderParm->channels;
		if (pDecoderCtx->channels == 1)
		{
			pDecoderCtx->channel_layout = AV_CH_LAYOUT_MONO;
		}
		else if (pDecoderCtx->channels == 2) 
		{
			pDecoderCtx->channel_layout = AV_CH_LAYOUT_STEREO;
		}
		else 
		{
			// 处理更多声道的情况
			pDecoderCtx->channel_layout = av_get_default_channel_layout(pDecoderCtx->channels);
		}
	}

	// 初始化重采样上下文
	auto pSwrContext = swr_alloc_set_opts(
		nullptr,
		AV_CH_LAYOUT_MONO,               // 输出单声道
		AV_SAMPLE_FMT_S16,               // 输出 16 位 PCM 格式
		44100,                           // 输出采样率 44100 Hz
		pDecoderCtx->channel_layout,    // 输入声道布局
		pDecoderCtx->sample_fmt,        // 输入采样格式
		pDecoderCtx->sample_rate,       // 输入采样率
		0, nullptr
	);
	if (!pSwrContext || swr_init(pSwrContext) < 0) 
	{
		qDebug() << "Failed to initialize SwrContext";
		return false;
	}

	//读取音频流数据
	AVPacket* pPacket = av_packet_alloc();
	AVFrame* pFrame = av_frame_alloc();

	while (av_read_frame(pFormatCtxt, pPacket) >= 0)
	{
		if (pPacket->stream_index == audioIndex)
		{
			//将pPacket发送给解码器
			if (avcodec_send_packet(pDecoderCtx, pPacket) == 0)
			{
				//获取解码后的av frame
				if (avcodec_receive_frame(pDecoderCtx, pFrame) == 0)
				{
					//计算重采样输出的大小
					int outputSampleCount = av_rescale_rnd(
						swr_get_delay(pSwrContext, pDecoderCtx->sample_rate) + pFrame->nb_samples,
						44100, pDecoderCtx->sample_rate, AV_ROUND_UP
					);
					
					// 分配临时缓冲区存储重采样后的数据
					qint16* buffer = new qint16[outputSampleCount];
					uint8_t* outBuffer[1] = { (uint8_t*)buffer };
					
					// 重采样
					int convertedSamples = swr_convert(
						pSwrContext,
						outBuffer, outputSampleCount,
						(const uint8_t**)pFrame->data, pFrame->nb_samples
					);
					
					// 将转换后的样本数据存储到 QVector 中
					for (int i = 0; i < convertedSamples; ++i) 
					{
						Global::pcmData.append(buffer[i]);
					}
					
					delete[] buffer;
				}
			}
		}
		av_packet_unref(pPacket);
		av_frame_unref(pFrame);
	}
	av_packet_free(&pPacket);
	av_frame_free(&pFrame);

	//释放解码器
	avcodec_free_context(&pDecoderCtx);

	//记得关闭输入上下文
	avformat_close_input(&pFormatCtxt);

	return true;
}
