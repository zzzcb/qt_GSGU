#include <QApplication>

#include "calibwizard.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	CalibWizard calibWizard;
	calibWizard.show();

	return app.exec();
}