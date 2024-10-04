#include <QApplication>

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;
	auto mainLayout = new QVBoxLayout(&w);

	for (int i = 0; i < 3; ++i)
	{
		mainLayout->addWidget(new QPushButton("Btn"));
		auto hLine = new QFrame;
		hLine->setFrameStyle(QFrame::HLine);
		mainLayout->addWidget(hLine);
	}
	mainLayout->addStretch();

	w.resize(500, 200);
	w.show();

	return app.exec();
}