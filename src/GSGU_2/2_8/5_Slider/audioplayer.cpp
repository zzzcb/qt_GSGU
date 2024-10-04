#include "AudioPlayer.h"
#include <QAudioFormat>
#include <QDebug>
#include "global.h"

#define SAMPLE_RATE 44100

AudioPlayer::AudioPlayer(QObject* parent)
	: QObject(parent) 
{
	QAudioFormat format;
	format.setSampleRate(SAMPLE_RATE);
	format.setChannelCount(1);
	format.setSampleFormat(QAudioFormat::Int16);

	// 检查设备是否支持该音频格式
	auto audioDeviceInfo = QMediaDevices::defaultAudioOutput();
	if (!audioDeviceInfo.isFormatSupported(format)) 
	{
		qWarning() << "不支持的音频格式！";
		return;
	}

	// 创建 QAudioSink
	m_pAudioSink = new QAudioSink(audioDeviceInfo, format, this);
	m_pBuffer = new QBuffer(this);

	m_eState = PlayerState::NO_AUDIO;


	connect(m_pAudioSink, &QAudioSink::stateChanged, [=](QAudio::State state) {
		if (state == QAudio::IdleState)
		{
			emit signal_finished();
		}
	});
}

void AudioPlayer::updatePcm()
{
	// 清空buffer 
	m_pBuffer->close();
	m_pBuffer->setData(QByteArray());

	// 创建 QBuffer 并加载 PCM 数据
	QByteArray byteArray(reinterpret_cast<const char*>(Global::pcmData.data()), Global::pcmData.size() * sizeof(qint16));

	m_pBuffer->setData(byteArray);
	m_pBuffer->open(QIODevice::ReadOnly); // 打开缓冲区为只读模式

	m_eState = PlayerState::AUDIO_NOPLAY;
}

void AudioPlayer::play() 
{
	if (m_eState != PlayerState::AUDIO_NOPLAY)
	{
		stop();
		updatePcm();
	}

	m_pAudioSink->start(m_pBuffer);
	m_eState = PlayerState::AUDIO_PLAYING;
}

PlayerState AudioPlayer::state()
{
	return m_eState;
}

void AudioPlayer::pause() 
{
	m_pAudioSink->suspend();  // 暂停播放
	m_eState = PlayerState::AUDIO_PAUSE;
}

void AudioPlayer::resume() 
{
	m_pAudioSink->resume();  // 恢复播放
	m_eState = PlayerState::AUDIO_PLAYING;
}

void AudioPlayer::stop()
{
	m_pAudioSink->reset(); 
	
	//清空buffer
	m_pBuffer->close();
	m_pBuffer->setData(QByteArray());

	//清空pcm
	Global::pcmData.clear();

	m_eState = PlayerState::NO_AUDIO;
}

void AudioPlayer::seek(qint64 second)
{
	qint64 samplePosition = second * SAMPLE_RATE; // 转换为样本位置
	qint64 target =  samplePosition * sizeof(qint16);

	if (target >= 0 && target < m_pBuffer->size())
	{
		m_pBuffer->seek(target); 

		if (m_eState == PlayerState::AUDIO_NOPLAY)
		{
			play();
		}
		else
		{
			resume();
		}
	}
}

qint64 AudioPlayer::position() const
{
	return m_pBuffer->pos() * 1.0 / sizeof(qint16) / SAMPLE_RATE;
}

qint64 AudioPlayer::duration() const
{
	return m_pBuffer->size() * 1.0 / sizeof(qint16) * 1.0 / SAMPLE_RATE; 
}

void AudioPlayer::setVolume(double volume)
{
	m_pAudioSink->setVolume(volume);  // 设置音量
}

