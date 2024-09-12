#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow mw;
	mw.setWindowTitle("我不是Qt");
	mw.resize(300, 300);
	mw.show();

	app.exec();

	return 0;
}
