#include "stackwidget.h"

#include <QStackedLayout>
#include <QVBoxLayout>
#include <QPushButton>

StackWidget::StackWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	resize(100, 100);
	
	auto mainLayout = new QVBoxLayout(this);
	auto layout = new QStackedLayout;
	
	for (int i = 0; i < 3; i++)
	{
		auto w = new QWidget;
		QColor bgClr(255, 0, i * 100 + 50);
		w->setStyleSheet(QString("background-color:%1;").arg(bgClr.name())); 
		
		layout->addWidget(w);
	}

	auto btn = new QPushButton("切换");
	connect(btn, &QPushButton::clicked, [=]() {
		int nextIdx = (layout->currentIndex()+1) % 3;
		layout->setCurrentIndex(nextIdx);
	});
	mainLayout->addWidget(btn);
	mainLayout->addLayout(layout);
}

StackWidget::~StackWidget()
{

}
