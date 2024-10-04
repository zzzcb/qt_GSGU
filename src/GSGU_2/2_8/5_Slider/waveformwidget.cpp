#include "waveformwidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "global.h"

WaveformWidget::WaveformWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	setFixedHeight(50);
}

WaveformWidget::~WaveformWidget()
{

}

void WaveformWidget::updateAudioData()
{
	update();
}

void WaveformWidget::setProgress(int value)
{
	m_nProgress = value;
	update();
}

void WaveformWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	if (Global::pcmData.empty())
		return;

	int width = this->width();
	int height = this->height();
	int totalSamples = Global::pcmData.size();

	// 绘制音频波形
	painter.setPen(QColor("#1296db"));
	int centerY = height / 2;

	for (int i = 0; i < width; i++)
	{
		int sampleStart = i * 1.0 / width * totalSamples;  // 当前帧的起始样本索引
		int sampleEnd = (i + 1) * 1.0 / width * totalSamples;  // 当前帧的结束样本索引

		if (sampleEnd >= totalSamples) sampleEnd = totalSamples - 1;

		// 计算这一段样本中的最小值和最大值
		int16_t minSample = 32767;
		int16_t maxSample = -32768;
		for (int j = sampleStart; j < sampleEnd; ) 
		{
			int16_t sample = Global::pcmData[j];
			if (sample < minSample) minSample = sample;
			if (sample > maxSample) maxSample = sample;

			j += 100;
		}

		int yMin = centerY - (minSample * centerY / 32768);
		int yMax = centerY - (maxSample * centerY / 32768);

		// 绘制这一段的波形范围
		painter.drawLine(i, yMin, i, yMax);
	}

	// 绘制进度
	int x = width * m_nProgress * 1.0 / 100;
	painter.setPen(Qt::red);
	painter.drawLine(x, 0, x, height);
}

void WaveformWidget::mousePressEvent(QMouseEvent* event)
{
	emit signal_clicked(event->x());
}
