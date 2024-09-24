#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	void initTheme();
	void setupUi();

	QString m_sConfigPath;
};

#endif 
