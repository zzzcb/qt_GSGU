#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
class ImageViewer;
class QSplitter;
class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();

protected:
	void showEvent(QShowEvent* event) override;

private slots:
	void slot_imageLooking(QString path);

private:
	ImageViewer* m_pImageViewer;

	QSplitter* m_pHSplitter;
	QSplitter* m_pVSplitter;

};

#endif 
