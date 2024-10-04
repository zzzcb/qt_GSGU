#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>

class QStandardItemModel;
class QListView;
class QStackedWidget;
class ImageViewer :public QWidget
{
	Q_OBJECT
public:
	ImageViewer(QWidget* parent = nullptr);
	virtual ~ImageViewer();


protected:
	bool eventFilter(QObject* watched, QEvent* event) override;


private:
	void slot_importImage();
	void slot_listView();
	void slot_iconView();

	QStandardItemModel* m_pModel = nullptr;
	QStackedWidget* m_pStackedWidget = nullptr;
	QListView* m_pListView = nullptr;
	QListView* m_pIconView = nullptr;
};

#endif 
