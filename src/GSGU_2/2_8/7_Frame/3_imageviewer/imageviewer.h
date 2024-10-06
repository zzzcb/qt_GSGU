#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>

class QGraphicsScene;
class QGraphicsPixmapItem;
class ImageViewer : public QGraphicsView
{
	Q_OBJECT
public:
	ImageViewer(QWidget* parent = nullptr);

	void setImage(const QString& imagePath);


protected:
	void wheelEvent(QWheelEvent* event) override;

private:
	QGraphicsScene* m_pScene = nullptr;
	QGraphicsPixmapItem* m_pPixmapItem = nullptr;
};

#endif 
