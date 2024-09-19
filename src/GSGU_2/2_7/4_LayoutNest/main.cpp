#include <QApplication>

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;

	auto mainLayout = new QHBoxLayout(&w);

	QWidget* left = new QWidget; left->setStyleSheet("background-color:red;");
	mainLayout->addWidget(left);

	QVBoxLayout* centerLayout = new QVBoxLayout;
	QWidget* centerTop = new QWidget; centerTop->setStyleSheet("background-color:green;");
	QWidget* centerBottom = new QWidget; centerBottom->setStyleSheet("background-color:green;");
	centerLayout->addWidget(centerTop);
	centerLayout->addWidget(centerBottom);
	mainLayout->addLayout(centerLayout);

	QWidget* right = new QWidget; right->setStyleSheet("background-color:blue;");
	mainLayout->addWidget(right);

	w.resize(500, 300);
	w.show();

	return app.exec();
}





