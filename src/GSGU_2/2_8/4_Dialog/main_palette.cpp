#include <QApplication>

#include <QMainWindow>
#include <QMenuBar>
#include <QStyleFactory>
#include "palettedialog.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);
	app.setStyle(QStyleFactory::create("Fusion"));

	QMainWindow mw;
	
	auto menu = mw.menuBar()->addMenu("工具");
	auto paletteAct = menu->addAction("Palette面板");
	QObject::connect(paletteAct, &QAction::triggered, [=]() {
		PaletteDialog dlg;
		dlg.exec();
	});

	mw.resize(500, 300);
	mw.show();

	return app.exec();
}