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
	void setupShortCut();
	void saveShortCut();
	void loadShortCut();

	QString m_sShortCutConf;
	QVector<QAction*>	m_vAllAction;
};

// 主窗体全局变量
extern MainWindow* g_mainWindow;