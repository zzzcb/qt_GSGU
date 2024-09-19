#include "formwidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

FormWidget::FormWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto layout = new QFormLayout(this);
	
	layout->addRow("用户名", new QLineEdit());
	layout->addRow("密 码", new QLineEdit());
	layout->addRow(new QPushButton("登录"));
}

FormWidget::~FormWidget()
{

}
