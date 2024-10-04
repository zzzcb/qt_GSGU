#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QAudioSink>
#include <QBuffer>
#include <QVector>
#include <QObject>
#include <QMediaDevices>

enum PlayerState
{
	NO_AUDIO,
	AUDIO_NOPLAY,
	AUDIO_PLAYING,
	AUDIO_PAUSE,
};

class AudioPlayer : public QObject 
{
	Q_OBJECT

public:
	explicit AudioPlayer(QObject* parent = nullptr);

	void play();		// 初始播放
	void pause();       // 暂停播放
	void resume();      // 恢复播放
	void stop();		// 停止播放

	void updatePcm();	// 更新pcm

	void seek(qint64 second);		// 设置播放位置
	qint64 position() const;		// 获取当前播放位置
	qint64 duration() const;		// 获取音频总时长
	void setVolume(double volume);  // 设置音量（0.0 - 1.0）

	PlayerState state();

signals:
	void signal_finished();

private:
	QAudioSink* m_pAudioSink = nullptr;
	QBuffer* m_pBuffer = nullptr;

	PlayerState		m_eState;
};

#endif // AUDIOPLAYER_H
