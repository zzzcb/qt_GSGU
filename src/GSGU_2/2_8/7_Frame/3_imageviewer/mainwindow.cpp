#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "imageresource.h"
#include "imageviewer.h"

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	auto center = new QWidget;
	setCentralWidget(center);

	auto mainLayout = new QVBoxLayout(center);
	
	m_pVSplitter = new QSplitter(Qt::Vertical);
	mainLayout->addWidget(m_pVSplitter);

	m_pHSplitter = new QSplitter(Qt::Horizontal);
	m_pVSplitter->addWidget(m_pHSplitter);

	setStyleSheet("background-color:#525252;");
	auto imageResource = new ImageResource; imageResource->setStyleSheet("background-color:#353535;color:white;");
	m_pImageViewer = new ImageViewer; m_pImageViewer->setStyleSheet("background-color:#353535;");
	auto w3 = new QWidget; w3->setStyleSheet("background-color:#353535;");

	m_pHSplitter->addWidget(imageResource);
	m_pHSplitter->addWidget(m_pImageViewer);
	m_pVSplitter->addWidget(w3);

	//信号槽
	connect(imageResource, &ImageResource::signal_imageLooking, this, &MainWindow::slot_imageLooking);
}

MainWindow::~MainWindow()
{

}

void MainWindow::showEvent(QShowEvent* event)
{
	m_pHSplitter->setSizes(QList<int>() << width()*0.3 << width()*0.7);
	m_pVSplitter->setSizes(QList<int>() << height()*0.6 << height()*0.4);

	QWidget::showEvent(event);
}

void MainWindow::slot_imageLooking(QString path)
{
	m_pImageViewer->setImage(path);
}
