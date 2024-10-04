#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLine>
#include <QSlider>
#include <QLabel>

#include "waveformwidget.h"
#include "audioplayer.h"

class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();


private slots:
	void slot_openAudio();
	void slot_closeAudio();

	void slot_togglePlayback();
	void slot_updateLine();
	void slot_seekAudio(int x);
	void slot_setVolume(int volume);

private:

	int currentProgress();

	WaveformWidget* m_pAudioWave = nullptr;
	AudioPlayer*	m_pAudioPlayer = nullptr;
	QToolButton*	m_pPlayBtn = nullptr;
	QSlider*		m_pAudioVolume = nullptr;
	QLabel*			m_pAudioName = nullptr;

	bool			m_bPalying;
};


#endif 
