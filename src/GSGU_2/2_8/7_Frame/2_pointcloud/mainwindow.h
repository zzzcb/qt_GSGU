#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <pcl/visualization/pcl_visualizer.h>

class QProgressBar;
class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();

signals:
	void signal_loadProgress(int percent);
	void signal_setGlobalEnable(bool enable);

private slots:
	void slot_openFile();
	void slot_loadProgress(int percent);
	void slot_setGlobalEnable(bool enable);

private:
	pcl::visualization::PCLVisualizer::Ptr m_pViewer;

	QProgressBar* m_pProgressBar = nullptr;

};

#endif 
