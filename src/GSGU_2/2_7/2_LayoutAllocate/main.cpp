#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QFrame>

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;
	auto mainLayout = new QVBoxLayout(&w);

	// layout设置stretch,内部widget不设置policy，不设置maxsize
	{
		QHBoxLayout* hLayout = new QHBoxLayout(&w);
		QPushButton* btn1 = new QPushButton("stretch1");
		QPushButton* btn2 = new QPushButton("normal");
		QPushButton* btn3 = new QPushButton("stretch3");
		QPushButton* btn4 = new QPushButton("normal");
		hLayout->addWidget(btn1, 1);
		hLayout->addWidget(btn2);
		hLayout->addWidget(btn3, 3);
		hLayout->addWidget(btn4);
		mainLayout->addLayout(hLayout);
	}

	// layout设置stretch,内部widget设置policy，不设置maxsize
	{
		QHBoxLayout* hLayout = new QHBoxLayout(&w);
		QPushButton* btn1 = new QPushButton("stretch1");
		QPushButton* btn2 = new QPushButton("expanding");
		QPushButton* btn3 = new QPushButton("stretch3");
		QPushButton* btn4 = new QPushButton("normal");
		btn2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		hLayout->addWidget(btn1, 1);
		hLayout->addWidget(btn2);
		hLayout->addWidget(btn3, 3);
		hLayout->addWidget(btn4);
		mainLayout->addLayout(hLayout);
	}

	// layout设置stretch,设置maxsize
	{
		QHBoxLayout* hLayout = new QHBoxLayout(&w);
		QPushButton* btn1 = new QPushButton("stretch1");
		QPushButton* btn2 = new QPushButton("normal");
		QPushButton* btn3 = new QPushButton("stretch3");
		QPushButton* btn4 = new QPushButton("normal");
		btn1->setMaximumWidth(100);
		hLayout->addWidget(btn1, 1);
		hLayout->addWidget(btn2);
		hLayout->addWidget(btn3, 3);
		hLayout->addWidget(btn4);
		mainLayout->addLayout(hLayout);
	}

	auto hLine = new QFrame;
	hLine->setFrameShape(QFrame::HLine);
	mainLayout->addWidget(hLine);

	// layout不设置stretch,内部widget设置policy，不设置maxsize
	{
		QHBoxLayout* hLayout = new QHBoxLayout(&w);
		QPushButton* btn1 = new QPushButton("expanding");
		QPushButton* btn2 = new QPushButton("normal");
		QPushButton* btn3 = new QPushButton("normal");
		QPushButton* btn4 = new QPushButton("normal");
		btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		hLayout->addWidget(btn1);
		hLayout->addWidget(btn2);
		hLayout->addWidget(btn3);
		hLayout->addWidget(btn4);
		mainLayout->addLayout(hLayout);
	}

	// layout不设置stretch,内部widget设置policy，设置maxsize
	{
		QHBoxLayout* hLayout = new QHBoxLayout(&w);
		QPushButton* btn1 = new QPushButton("expanding");
		QPushButton* btn2 = new QPushButton("normal");
		QPushButton* btn3 = new QPushButton("normal");
		QPushButton* btn4 = new QPushButton("normal");
		btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		btn1->setMaximumWidth(200);
		hLayout->addWidget(btn1);
		hLayout->addWidget(btn2);
		hLayout->addWidget(btn3);
		hLayout->addWidget(btn4);
		mainLayout->addLayout(hLayout);
	}

	w.show();

	return app.exec();
}