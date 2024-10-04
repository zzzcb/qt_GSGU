#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	auto center = new QWidget;
	setCentralWidget(center);

	auto mainLayout = new QVBoxLayout(center);
	
	auto hSplitter = new QSplitter(Qt::Horizontal);
	mainLayout->addWidget(hSplitter);

	auto w1 = new QWidget; w1->setStyleSheet("background-color:red;");
	auto w2 = new QWidget; w2->setStyleSheet("background-color:green;");
	auto w3 = new QWidget; w3->setStyleSheet("background-color:blue;");

	hSplitter->addWidget(w1);
	hSplitter->addWidget(w2);
	hSplitter->addWidget(w3);
}

MainWindow::~MainWindow()
{

}
