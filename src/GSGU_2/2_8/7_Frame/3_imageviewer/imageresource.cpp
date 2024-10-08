#include "imageresource.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QStackedWidget>
#include <QListView>
#include <QStandardItemModel>

#include <QFileDialog>
#include <QWheelEvent>

#define ICONSIZE 30
int ImageFullPath_Role = Qt::UserRole + 1;

ImageResource::ImageResource(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	auto mainLayout = new QVBoxLayout(this);
	auto toolLayout = new QHBoxLayout;
	auto importBtn = new QToolButton; importBtn->setStyleSheet("background-color:transparent;");
	importBtn->setIcon(QIcon(":/images/import.svg"));
	auto listBtn = new QToolButton; listBtn->setStyleSheet("background-color:transparent;");
	listBtn->setIcon(QIcon(":/images/listview.svg"));
	auto iconBtn = new QToolButton; iconBtn->setStyleSheet("background-color:transparent;");
	iconBtn->setIcon(QIcon(":/images/iconview.svg"));
	toolLayout->addWidget(importBtn);
	toolLayout->addStretch();
	toolLayout->addWidget(listBtn);
	toolLayout->addWidget(iconBtn);

	mainLayout->addLayout(toolLayout);

	m_pModel = new QStandardItemModel;

	m_pStackedWidget = new QStackedWidget;
	m_pListView = new QListView;
	m_pIconView = new QListView; m_pIconView->setViewMode(QListView::IconMode);
	m_pStackedWidget->addWidget(m_pListView);
	m_pStackedWidget->addWidget(m_pIconView);
	mainLayout->addWidget(m_pStackedWidget);

	m_pListView->setModel(m_pModel);
	m_pIconView->setModel(m_pModel);
	m_pListView->setIconSize(QSize(ICONSIZE, ICONSIZE));
	m_pIconView->setIconSize(QSize(ICONSIZE, ICONSIZE));
	m_pIconView->setGridSize(QSize(ICONSIZE, ICONSIZE));
	
	m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pIconView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(m_pListView, &QListView::clicked, this, &ImageResource::slot_imageClicked);
	connect(m_pIconView, &QListView::clicked, this, &ImageResource::slot_imageClicked);

	m_pStackedWidget->installEventFilter(this);

	//信号槽
	connect(importBtn, &QToolButton::clicked, this, &ImageResource::slot_importImage);
	connect(listBtn, &QToolButton::clicked, this, &ImageResource::slot_listView);
	connect(iconBtn, &QToolButton::clicked, this, &ImageResource::slot_iconView);
}

ImageResource::~ImageResource()
{

}

bool ImageResource::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_pStackedWidget)
	{
		if (event->type() == QEvent::Wheel)
		{
			QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

			if (wheelEvent->modifiers() & Qt::ControlModifier)
			{
				if (wheelEvent->angleDelta().y() > 0)
				{
					m_pListView->setIconSize(m_pListView->iconSize() * 1.1);
					m_pIconView->setIconSize(m_pIconView->iconSize() * 1.1);
					m_pIconView->setGridSize(m_pIconView->gridSize() * 1.1);
				}
				else
				{
					m_pListView->setIconSize(m_pListView->iconSize() * 0.9);
					m_pIconView->setIconSize(m_pIconView->iconSize() * 0.9);
					m_pIconView->setGridSize(m_pIconView->gridSize() * 0.9);
				}

				return true; 
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}

void ImageResource::slot_importImage()
{
	auto filePaths = QFileDialog::getOpenFileNames(this, "请选择图片", ".", "图片(*.jpg *.png *.bmp)");

	if (filePaths.isEmpty())
		return;

	for (auto& filePath : filePaths)
	{
		QStandardItem* item = new QStandardItem;
		QPixmap thumbnail(filePath);
		item->setIcon(thumbnail);
		item->setText(QFileInfo(filePath).fileName());
		item->setData(filePath, ImageFullPath_Role);

		m_pModel->appendRow(item);
	}
}

void ImageResource::slot_listView()
{
	m_pStackedWidget->setCurrentIndex(0);
}

void ImageResource::slot_iconView()
{
	m_pStackedWidget->setCurrentIndex(1);
}

void ImageResource::slot_imageClicked(const QModelIndex& index)
{
	auto item = m_pModel->itemFromIndex(index);
	auto imagePath =  item->data(ImageFullPath_Role).toString();

	emit signal_imageLooking(imagePath);
}
