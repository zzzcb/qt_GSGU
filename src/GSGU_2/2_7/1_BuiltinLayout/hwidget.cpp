#include "hwidget.h"

#include <QHBoxLayout>
#include <QPushButton>

HWidget::HWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto layout = new QHBoxLayout(this);
	
	for (int i = 0; i < 3; i++)
	{
		layout->addWidget(new QPushButton("btn"+QString::number(i)));
	}
}

HWidget::~HWidget()
{

}
