#include <QApplication>

#include "mainwindow.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);


	MainWindow mw;
	mw.resize(1000, 500);
	mw.show();

	return app.exec();
}


//#include <QProcess>
//int main(int argc, char* argv[])
//{
//	QApplication a(argc, argv);
//
//	// 创建 QProcess 对象
//	QProcess process;
//	
//	// 启动外部程序
//	process.start("D:/dependency/Spleeter/Spleeter.exe", {"-m","4stems", "D:/dependency/Spleeter/love.aac" });
//
//	QObject::connect(&process, &QProcess::readyReadStandardOutput, [&]() {
//		// 获取程序的标准输出
//		QString output = process.readAllStandardOutput();
//		qDebug() << "Output：" << output;
//	});
//
//	QObject::connect(&process, &QProcess::readyReadStandardError, [&]() {
//		// 获取程序的标准输出
//		QString output = process.readAllStandardError();
//		qDebug() << "Output：" << output;
//		});
//
//	return a.exec();
//}
