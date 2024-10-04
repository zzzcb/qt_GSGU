#include "audiodecoder.h"

#include <QDebug>

AudioDecoder::AudioDecoder()
	:formatContext(nullptr), 
	codecContext(nullptr), 
	audioStreamIndex(-1)
{
	av_register_all();  // 注册 FFmpeg 所有格式和编解码器
}

AudioDecoder::~AudioDecoder()
{
	// 清理资源
	if (formatContext)
	{
		avformat_close_input(&formatContext);
	}
	if (codecContext)
	{
		avcodec_free_context(&codecContext);
	}
	if (swrContext)
	{
		swr_free(&swrContext);
	}
}

bool AudioDecoder::openFile(const QString& filePath)
{
	// 打开音频文件
	if (avformat_open_input(&formatContext, filePath.toStdString().c_str(), nullptr, nullptr) < 0)
	{
		qDebug() << "Failed to open file:" << filePath;
		return false;
	}

	// 获取流信息
	if (avformat_find_stream_info(formatContext, nullptr) < 0)
	{
		qDebug() << "Failed to find stream info";
		return false;
	}

	// 查找音频流
	AVCodec* codec = nullptr;
	audioStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, &codec, 0);
	if (audioStreamIndex < 0) 
	{
		qDebug() << "Failed to find audio stream";
		return false;
	}

	// 初始化解码器上下文
	codecContext = avcodec_alloc_context3(codec);
	if (!codecContext)
	{
		qDebug() << "Failed to allocate codec context";
		return false;
	}

	avcodec_parameters_to_context(codecContext, formatContext->streams[audioStreamIndex]->codecpar);

	if (avcodec_open2(codecContext, codec, nullptr) < 0) 
	{
		qDebug() << "Failed to open codec";
		return false;
	}

	// 初始化重采样上下文
	swrContext = swr_alloc_set_opts(
		nullptr,
		AV_CH_LAYOUT_MONO,               // 输出单声道
		AV_SAMPLE_FMT_S16,               // 输出 16 位 PCM 格式
		44100,                           // 输出采样率 44100 Hz
		codecContext->channel_layout,    // 输入声道布局
		codecContext->sample_fmt,        // 输入采样格式
		codecContext->sample_rate,       // 输入采样率
		0, nullptr
	);
	if (!swrContext || swr_init(swrContext) < 0) {
		qDebug() << "Failed to initialize SwrContext";
		return false;
	}

	return true;

	return true;
}

#include "global.h"

void AudioDecoder::decode()
{
	Global::pcmData.clear();
	// 读取帧并解码
	AVPacket packet;
	AVFrame* frame = av_frame_alloc();

	while (av_read_frame(formatContext, &packet) >= 0) 
	{
		if (packet.stream_index == audioStreamIndex)
		{
			if (avcodec_send_packet(codecContext, &packet) >= 0)
			{
				while (avcodec_receive_frame(codecContext, frame) >= 0)
				{
					// 计算重采样输出的大小
					int outputSampleCount = av_rescale_rnd(
						swr_get_delay(swrContext, codecContext->sample_rate) + frame->nb_samples,
						44100, codecContext->sample_rate, AV_ROUND_UP
					);

					// 分配临时缓冲区存储重采样后的数据
					qint16* buffer = new qint16[outputSampleCount];
					uint8_t* outBuffer[1] = { (uint8_t*)buffer };

					// 重采样
					int convertedSamples = swr_convert(
						swrContext,
						outBuffer, outputSampleCount,
						(const uint8_t**)frame->data, frame->nb_samples
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
		av_packet_unref(&packet);
	}

	av_frame_free(&frame);
}
