#include <QApplication>

#include <QVBoxLayout>
#include "custombutton.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;
	QVBoxLayout vLayout(&w);

	vLayout.addWidget(new QPushButton("pushbutton"));
	vLayout.addWidget(new CustomButton("custom-button"));

	w.resize(100, 100);
	w.show();

	return app.exec();
}