#include <QApplication>

#include "hwidget.h"
#include "vwidget.h"
#include "gridwidget.h"
#include "formwidget.h"
#include "stackwidget.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	HWidget hw;
	hw.show();

	VWidget vw;
	vw.show();

	GridWidget gw;
	gw.show();

	FormWidget fw;
	fw.show();

	StackWidget sw;
	sw.show();

	return app.exec();
}