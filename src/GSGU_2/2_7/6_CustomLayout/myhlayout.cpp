#include "myhlayout.h"

#include <QWidget>

MyHLayout::MyHLayout(QWidget* parent)
	:QLayout(parent)
{

}

MyHLayout::~MyHLayout()
{
	QLayoutItem* item;
	while ((item = takeAt(0)))
		delete item;
}

void MyHLayout::addItem(QLayoutItem* item)
{
	m_lItems.append(item);
}

int MyHLayout::count() const
{
	return m_lItems.size();
}

QLayoutItem* MyHLayout::itemAt(int index) const
{
	return m_lItems.value(index);
}

QLayoutItem* MyHLayout::takeAt(int index)
{
	if (index >= 0 && index < m_lItems.size())
	{
		return m_lItems.takeAt(index);
	}
	return nullptr;
}

QSize MyHLayout::sizeHint() const
{
	QSize s(0, 0);
	int n = m_lItems.count();
	if (n <= 0)
		return QSize(100, 70);		// 返回默认布局大小

	int i = 0;
	while (i < n) 
	{
		QLayoutItem* o = m_lItems.at(i);
		s = s + o->sizeHint();
		++i;
	}
	return s + (n-1) * QSize(spacing(), 0);
}

void MyHLayout::setGeometry(const QRect& r)
{
	QLayout::setGeometry(r);

	if (m_lItems.size() == 0)
		return;

	int x = r.x();
	int averageW = (r.width() - (count() - 1) * spacing()) * 1.0 / count();

	for (auto& item : m_lItems)
	{
		if (auto widget = item->widget())
		{
			int curWidth = widget->width();
			int minW = widget->minimumWidth();
			int maxW = widget->maximumWidth();

			if (averageW < minW)
				curWidth = minW;
			else if (averageW > maxW)
				curWidth = maxW;
			else
				curWidth = averageW;

			QRect geom(x, r.y(),curWidth, r.height());
			item->setGeometry(geom);

			x = x + curWidth + spacing();
		}
	}
}

QSize MyHLayout::minimumSize() const
{
	QSize s(0, 0);

	for (auto& item : m_lItems)
	{
		s = s + item->minimumSize() + QSize(spacing(),0);
	}

	return s;
}
