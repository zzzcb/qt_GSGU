#include "imageviewer.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QWheelEvent>
#include <QScrollBar>

ImageViewer::ImageViewer(QWidget* parent /*= nullptr*/)
	:QGraphicsView(parent)
{
	m_pScene = new QGraphicsScene;
	setScene(m_pScene);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setDragMode(QGraphicsView::ScrollHandDrag);

	m_pPixmapItem = new QGraphicsPixmapItem;
	m_pScene->addItem(m_pPixmapItem);
}


void ImageViewer::setImage(const QString& imagePath)
{
	resetTransform();

	m_pPixmapItem->setPixmap(QPixmap(imagePath));
	m_pScene->setSceneRect(0, 0, m_pPixmapItem->boundingRect().width(), m_pPixmapItem->boundingRect().height());

	double imgRatio = m_pPixmapItem->boundingRect().width() / m_pPixmapItem->boundingRect().height();
	double viewerRatio = width()*1.0 / height();

	if (viewerRatio > imgRatio)
	{
		double sy = (height() - 10) * 1.0 / m_pPixmapItem->boundingRect().height();
		scale(sy, sy);
	}
	else
	{
		double sx = (width()-10) * 1.0 / m_pPixmapItem->boundingRect().width();
		scale(sx, sx);
	}
}

void ImageViewer::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		if (event->angleDelta().y() > 0)
		{
			scale(1.1,1.1);
		}
		else
		{
			scale(0.9,0.9);
		}
	}
	else
	{
		auto vBar =verticalScrollBar();
		vBar->setValue(vBar->value() - event->angleDelta().y());
	}
}
