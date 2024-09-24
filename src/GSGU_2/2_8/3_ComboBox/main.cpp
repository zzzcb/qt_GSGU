#include <QtWidgets/QApplication>

#include <QComboBox>
#include <QFontComboBox>
#include <QHBoxLayout>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QWidget mw;
	QHBoxLayout* hLayout = new QHBoxLayout(&mw);
	QComboBox* cb = new QComboBox(&mw);
	cb->addItems({ "China","USA","Russia" });
	
	QFontComboBox* fcb = new QFontComboBox(&mw);

	hLayout->addWidget(cb);
	hLayout->addWidget(fcb);

	mw.show();

	return a.exec();
}
