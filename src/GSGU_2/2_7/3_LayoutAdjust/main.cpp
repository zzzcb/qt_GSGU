#include <QApplication>

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	// 内容margin
	QWidget marginW;
	{
		auto hLayout = new QHBoxLayout(&marginW);
		for (int i=0;i<3;i++)
		{
			hLayout->addWidget(new QPushButton(QString("btn-%1").arg(i)));
		}
		//取消默认的内容margin
		//hLayout->setContentsMargins(0,0,0,0);
	}
	marginW.show();

	// 内容padding
	QWidget paddingW;
	{
		auto hLayout = new QHBoxLayout(&paddingW);
		for (int i = 0; i < 3; i++)
		{
			hLayout->addWidget(new QPushButton(QString("btn-%1").arg(i)));
		}
		
		// 取消默认的内容padding
		//hLayout->setSpacing(0);
	}
	paddingW.show();

	// 布局内添加spacer
	QWidget alignW;
	{
		auto hLayout = new QHBoxLayout(&alignW);
		for (int i = 0; i < 3; i++)
		{
			hLayout->addWidget(new QPushButton(QString("btn-%1").arg(i)));
			if (i == 1)
			{
				hLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
			}
		}
	}
	alignW.show();


	return app.exec();
}

