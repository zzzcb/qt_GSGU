#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPdfView;
class QPdfDocument;
class QLabel;
class QSpinBox;

class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();


private slots:
	void slot_fileOpen();
	void slot_changePage(int page);
	void slot_setPageLabel(int page);
	void slot_zoomPage(qreal factor);
	
private:
	QPdfView* m_pPdfView;
	QPdfDocument* m_pPdfDocument;
	QSpinBox* m_pPageSpin;

	QLabel* m_pPageCount;
};


#endif 
