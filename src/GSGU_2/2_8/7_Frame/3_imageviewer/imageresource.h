#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QWidget>

class QStandardItemModel;
class QListView;
class QStackedWidget;
class ImageResource :public QWidget
{
	Q_OBJECT
public:
	ImageResource(QWidget* parent = nullptr);
	virtual ~ImageResource();


signals:
	void signal_imageLooking(QString path);


protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void slot_importImage();
	void slot_listView();
	void slot_iconView();
	void slot_imageClicked(const QModelIndex& index);


	QStandardItemModel* m_pModel = nullptr;
	QStackedWidget* m_pStackedWidget = nullptr;
	QListView* m_pListView = nullptr;
	QListView* m_pIconView = nullptr;
};

#endif 
