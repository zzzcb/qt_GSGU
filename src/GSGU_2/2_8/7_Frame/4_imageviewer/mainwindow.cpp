#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "imageviewer.h"

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	auto center = new QWidget;
	setCentralWidget(center);

	auto mainLayout = new QVBoxLayout(center);
	
	auto vSplitter = new QSplitter(Qt::Vertical);
	mainLayout->addWidget(vSplitter);

	auto hSplitter = new QSplitter(Qt::Horizontal);
	vSplitter->addWidget(hSplitter);

	setStyleSheet("background-color:#525252;");
	auto w1 = new ImageViewer; w1->setStyleSheet("background-color:#353535;color:white;");
	auto w2 = new QWidget; w2->setStyleSheet("background-color:#353535;");
	auto w3 = new QWidget; w3->setStyleSheet("background-color:#353535;");

	hSplitter->addWidget(w1);
	hSplitter->addWidget(w2);
	vSplitter->addWidget(w3);

	vSplitter->setSizes(QList<int>() << 30 << 70);
}

MainWindow::~MainWindow()
{

}
