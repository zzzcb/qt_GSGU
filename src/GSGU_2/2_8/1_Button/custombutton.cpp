#include "custombutton.h"

#include <QStyleOptionButton>
#include <QPainter>

CustomButton::CustomButton(QWidget* parent/*=nullptr*/)
	:QPushButton(parent)
{
}

CustomButton::CustomButton(const QString& text, QWidget* parent /*= nullptr*/)
	:QPushButton(text,parent)
{

}

CustomButton::~CustomButton()
{
}

void CustomButton::paintEvent(QPaintEvent* e)
{
	//QPushButton::paintEvent(e);
	
	QStyleOptionButton option;
	initStyleOption(&option);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// 是否鼠标进入
	bool isHovered = option.state & QStyle::State_MouseOver;
	bool isPressed = option.state & QStyle::State_Sunken;
	QColor highClr = option.palette.color(QPalette::Highlight);
	QColor darkClr = option.palette.color(QPalette::Dark);

	// 画边框,画背景
	painter.save();
	painter.setPen(isHovered ? highClr : darkClr);
	QColor highBgClr(highClr);
	QColor darkBgClr(darkClr);
	highBgClr.setAlpha(25);
	darkBgClr.setAlpha(25);
	if (isPressed)
	{
		QColor pressClr(highClr);
		pressClr.setAlpha(50);
		painter.setBrush(pressClr);
	}
	else
	{
		painter.setBrush(isHovered ? highBgClr : darkBgClr);
	}
	painter.drawPath(processRect2ChamferRect(option.rect,5,5));
	painter.restore();

	// 画文本
	painter.save();
	QTextOption txtOpt;
	txtOpt.setAlignment(Qt::AlignCenter);
	painter.setPen(option.palette.color(QPalette::ButtonText));
	painter.drawText(option.rect, option.text, txtOpt);
	painter.restore();
}

QPainterPath CustomButton::processRect2ChamferRect(QRect rect, qreal xGap /*= 10*/, qreal yGap /*= 10*/)
{
	int x = rect.x();
	int y = rect.y();
	int w = rect.width();
	int h = rect.height();

	QVector<QPointF> vPoint;
	vPoint << QPointF(x + xGap, y)
		<< QPointF(x + w, y)
		<< QPointF(x + w, y + h - yGap)
		<< QPointF(x + w - xGap, y + h)
		<< QPointF(x, y + h)
		<< QPointF(x, y + yGap)
		<< QPointF(x + xGap, y);

	QPainterPath path(vPoint.first());
	for (auto& pt : vPoint)
		path.lineTo(pt);

	return path;
}

