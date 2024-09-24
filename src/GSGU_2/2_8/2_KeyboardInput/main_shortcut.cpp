#include <QApplication>

#include <QPushButton>


#include "mainwindow.h"
#include "keyboarddialog.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	MainWindow mw;

	//配置快捷键按钮
	auto btn = new QPushButton("点击以配置快捷键");
	QObject::connect(btn, &QPushButton::clicked, [&]() {
		auto bar = mw.menuBar();
		KeyboardDialog kd;
		kd.exec();
		});
	mw.setCentralWidget(btn);

	mw.show();
	mw.resize(500, 300);

	return app.exec();
}