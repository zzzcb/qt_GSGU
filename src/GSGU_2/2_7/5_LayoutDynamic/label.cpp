#include "label.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

Label::Label(QString text, QWidget* parent /*= nullptr*/)
	:QLabel(parent), m_strLabel(text)
{
	setAcceptDrops(true);
	setText(text + QString(" x"));
	setContentsMargins(1,0,1,0);
}

Label::~Label()
{

}

void Label::showEvent(QShowEvent* event)
{
	m_tTxtFont.setPixelSize(this->rect().height() - 5);
	m_tBgClr = this->palette().color(QPalette::Highlight);

	QWidget::showEvent(event);
}

void Label::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// 绘制背景色
	painter.setBrush(m_tBgClr);
	painter.drawRoundedRect(this->rect(),3,3);

	// 设置字体,字体颜色
	painter.setFont(m_tTxtFont);
	painter.setPen(QColor("#fff"));	// 白色字体

	// 设置字体格式
	QTextOption txtOpt;
	txtOpt.setAlignment(Qt::AlignCenter);
	painter.drawText(this->rect(), this->text(), txtOpt);
}

void Label::mousePressEvent(QMouseEvent* event)
{
	QFontMetrics fontMet(m_tTxtFont);
	int txtWidth = fontMet.horizontalAdvance(m_strLabel+" ");

	int posX = event->pos().x();
	// 判断是否点击了叉号
	if (posX > txtWidth)
	{
		emit killed(this);
		return;
	}

	// 下方为触发拖拽操作
	if (event->button() == Qt::LeftButton) 
	{
		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;
		mimeData->setText(m_strLabel); 
		drag->setMimeData(mimeData);

		QPixmap pixmap = grab();
		drag->setPixmap(pixmap);

		drag->exec();
	}
	QLabel::mousePressEvent(event);
}

void Label::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasText()) 
	{
		event->accept();
	}
	else 
	{
		event->ignore();
	}
}

void Label::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasText()) 
	{
		QWidget* sourceWidget = qobject_cast<QWidget*>(event->source());
		if (sourceWidget && sourceWidget != this)
		{
			QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(parentWidget()->layout());
			if (layout) 
			{
				int srcIdx = layout->indexOf(sourceWidget);
				int dstIdx = layout->indexOf(this);

				sourceWidget->setParent(nullptr); 
				layout->removeWidget(sourceWidget);

				int index = layout->indexOf(this);
				if (srcIdx < dstIdx) //向后移动
				{
					index++;
				}
				layout->insertWidget(index, sourceWidget);
			}
		}
		event->accept();
	}
	else 
	{
		event->ignore();
	}
}

