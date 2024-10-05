#include "mainwindow.h"

#include <QSlider>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QTimer>
#include "audiodecoder.h"

#include "global.h"

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent),m_bPalying(false)
{
	auto bar = menuBar();
	auto fileMenu = bar->addMenu("文件");
	auto openAudioAct = fileMenu->addAction("打开音频");
	auto closeAudioAct = fileMenu->addAction("关闭音频");

	auto widget = new QWidget;
	setCentralWidget(widget);

	auto mainLayout = new QVBoxLayout(widget);
	
	auto videoArea = new QWidget;
	auto audioLayout = new QHBoxLayout(videoArea);

	m_pAudioVolume = new QSlider(Qt::Horizontal);
	m_pAudioVolume->setMinimum(0);
	m_pAudioVolume->setMaximum(100);
	m_pAudioVolume->setValue(50);
	m_pPlayBtn = new QToolButton;
	m_pPlayBtn->setStyleSheet("background-color:transparent");
	m_pPlayBtn->setIcon(QIcon(":/images/play.svg"));
	m_pAudioWave = new WaveformWidget;
	m_pAudioName = new QLabel;
	m_pAudioName->setText("--");
	audioLayout->addWidget(m_pAudioName);
	audioLayout->addWidget(m_pAudioVolume);
	audioLayout->addWidget(m_pPlayBtn);
	audioLayout->addWidget(m_pAudioWave,1);

	mainLayout->addStretch();
	mainLayout->addWidget(videoArea);
	{
		auto hLine = new QFrame;
		hLine->setFrameStyle(QFrame::HLine);
		mainLayout->addWidget(hLine);
	}


	m_pAudioPlayer = new AudioPlayer(this);

	connect(openAudioAct, &QAction::triggered, this, &MainWindow::slot_openAudio);
	connect(closeAudioAct, &QAction::triggered, this, &MainWindow::slot_closeAudio);
	connect(m_pPlayBtn, &QToolButton::clicked, this, &MainWindow::slot_togglePlayback);
	connect(m_pAudioWave, &WaveformWidget::signal_clicked, this, &MainWindow::slot_seekAudio);
	connect(m_pAudioVolume, &QSlider::valueChanged, this, &MainWindow::slot_setVolume);
	connect(m_pAudioPlayer, &AudioPlayer::signal_finished, this, &MainWindow::slot_closeAudio);

	auto timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MainWindow::slot_updateLine);
	timer->start(1000);
}


MainWindow::~MainWindow()
{

}


void MainWindow::slot_openAudio()
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Audio File", "", "Audio Files (*.mp3 *.aac *.wav *.ogg)");
	if (!fileName.isEmpty())
	{
		QFileInfo f(fileName);
		m_pAudioName->setText(f.fileName());

		Global::pcmData.clear();
		if (AudioDecoder::decode(fileName))
		{
			m_pAudioWave->updateAudioData();
			m_pAudioPlayer->updatePcm();
			slot_setVolume(m_pAudioVolume->value());
		}
	}
}

void MainWindow::slot_closeAudio()
{
	m_pAudioPlayer->stop();
	Global::pcmData.clear();
	m_pAudioName->setText("--");
	m_pAudioVolume->setValue(50);
	m_pPlayBtn->setIcon(QIcon(":/images/play.svg"));
	m_bPalying = false;
}

void MainWindow::slot_togglePlayback()
{
	if (m_pAudioPlayer->state() == PlayerState::NO_AUDIO)
		return;

	m_pAudioWave->setProgress(currentProgress());

	if (m_bPalying) 
	{
		m_pPlayBtn->setIcon(QIcon(":/images/play.svg"));
		m_pAudioPlayer->pause();
	}
	else 
	{
		m_pPlayBtn->setIcon(QIcon(":/images/pause.svg"));
		if (m_pAudioPlayer->state() == PlayerState::AUDIO_NOPLAY)
		{
			m_pAudioPlayer->play();
		}
		else if (m_pAudioPlayer->state() == PlayerState::AUDIO_PAUSE)
		{
			m_pAudioPlayer->resume();
		}
	}

	m_bPalying = !m_bPalying;
}

void MainWindow::slot_updateLine()
{
	m_pAudioWave->setProgress(currentProgress());
}

void MainWindow::slot_seekAudio(int x)
{
	if (m_pAudioPlayer->state() == NO_AUDIO)
		return;

	int width =  m_pAudioWave->width();

	int duration = m_pAudioPlayer->duration();
	int position = m_pAudioPlayer->position();

	int newPos = x * 1.0 / width * duration;
	m_pAudioPlayer->seek(newPos);

	m_pPlayBtn->setIcon(QIcon(":/images/pause.svg"));
	m_bPalying = true;
	m_pAudioWave->setProgress(currentProgress());
}

void MainWindow::slot_setVolume(int volume)
{
	m_pAudioPlayer->setVolume(volume / 100.);
}

int MainWindow::currentProgress()
{
	int duration = m_pAudioPlayer->duration();
	int position = m_pAudioPlayer->position();

	return 100.0 * position / duration;
}
