#include "gridwidget.h"

#include <QGridLayout>
#include <QPushButton>

GridWidget::GridWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto layout = new QGridLayout(this);
	
	for (int i = 0; i < 3; i++)
	{
		for (int j=0;j<3;j++)
		{
			layout->addWidget(new QPushButton("btn" + QString::number(i) +" " + QString::number(j)), i, j);
		}
	}
}

GridWidget::~GridWidget()
{

}
