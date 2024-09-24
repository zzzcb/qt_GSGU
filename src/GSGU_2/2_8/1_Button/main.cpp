#include <QApplication>

#include <QVBoxLayout>
#include <QFrame>

#include <QCheckBox>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QFile>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


	QWidget mw;
	QVBoxLayout vLayout(&mw);

	//QCheckBox
	QCheckBox* ck = new QCheckBox;
	ck->setText("已阅读上述协议,并同意条款");
	vLayout.addWidget(ck);

	QCheckBox* ck2 = new QCheckBox;
	ck2->setText("已阅读上述协议,并同意条款2");
	ck2->setTristate();
	ck2->setCheckState(Qt::PartiallyChecked);	
	vLayout.addWidget(ck2);
	{
		auto line = new QFrame;
		line->setFrameStyle(QFrame::HLine);
		vLayout.addWidget(line);
	}

	//QPushButton
	vLayout.addWidget(new QPushButton("我不是Qt"));

	QIcon icon(":/images/love.png");
	QPushButton* btn2 = new QPushButton;
	btn2->setIcon(icon);
	vLayout.addWidget(btn2);
	{
		auto line = new QFrame;
		line->setFrameStyle(QFrame::HLine);
		vLayout.addWidget(line);
	}

	//QRadioButton
	vLayout.addWidget(new QRadioButton("text"));
	vLayout.addWidget(new QRadioButton("text2"));

	auto coutry1 = new QRadioButton("china");
	auto coutry2 = new QRadioButton("usa");
	auto coutry3 = new QRadioButton("russia");
	vLayout.addWidget(coutry1);
	vLayout.addWidget(coutry2);
	vLayout.addWidget(coutry3);

	//QButtonGroup* btnGroup = new QButtonGroup(&mw);
	//btnGroup->addButton(coutry1);
	//btnGroup->addButton(coutry2);
	//btnGroup->addButton(coutry3);
	{
		auto line = new QFrame;
		line->setFrameStyle(QFrame::HLine);
		vLayout.addWidget(line);
	}

	//QToolButton
	QIcon icon2(":/images/cp.png");
	QToolButton* toolBtn = new QToolButton;
	toolBtn->setIcon(icon2);
	QToolButton* toolBtn2 = new QToolButton;
	toolBtn2->setIcon(icon2);
	toolBtn2->setText("PC");
	toolBtn2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	vLayout.addWidget(toolBtn);
	vLayout.addWidget(toolBtn2);
	//toolBtn2->setIconSize(QSize(50,50));
	//QFile qss(":/btn.qss");
	//if (qss.open(QIODevice::ReadOnly))
	//{
	//	toolBtn2->setStyleSheet(QString(qss.readAll()));
	//}
	{
		auto line = new QFrame;
		line->setFrameStyle(QFrame::HLine);
		vLayout.addWidget(line);
	}

	//QCommandLinkButton
	QCommandLinkButton* cmdLinkBtn = new QCommandLinkButton("text", "description");
	vLayout.addWidget(cmdLinkBtn);
	{
		auto line = new QFrame;
		line->setFrameStyle(QFrame::HLine);
		vLayout.addWidget(line);
	}

	mw.resize(500, 500);
	mw.show();

    return a.exec();
}

