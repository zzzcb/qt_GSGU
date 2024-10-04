#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QVector>

class WaveformWidget :public QWidget
{
	Q_OBJECT
public:
	WaveformWidget(QWidget* parent = nullptr);
	virtual ~WaveformWidget();

	void updateAudioData();
	void setProgress(int value);

signals:
	void signal_clicked(int x);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	int			m_nProgress = 0; // 0 - 100
};

#endif 

