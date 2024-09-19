#include "vwidget.h"

#include <QVBoxLayout>
#include <QPushButton>

VWidget::VWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto layout = new QVBoxLayout(this);
	
	for (int i = 0; i < 3; i++)
	{
		layout->addWidget(new QPushButton("btn"+QString::number(i)));
	}
}

VWidget::~VWidget()
{

}
