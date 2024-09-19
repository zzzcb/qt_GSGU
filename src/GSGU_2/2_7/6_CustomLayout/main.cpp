#include <QApplication>

#include <QWidget>
#include <QPushButton>

#include "myhlayout.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;

	MyHLayout hLayout(&w);
	for (int i = 0; i < 3; ++i)
	{
		hLayout.addWidget(new QPushButton(QString::number(i)));
	}

	w.show();


	return app.exec();
}
