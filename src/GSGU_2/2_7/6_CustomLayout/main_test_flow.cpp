#include <QApplication>

#include <QWidget>
#include <QPushButton>

#include "flowlayout.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;

	FlowLayout layout(&w);
	for (int i = 0; i < 20; ++i)
	{
		layout.addWidget(new QPushButton(QString("qpushbutton %1").arg(i)));
	}

	w.show();


	return app.exec();
}
