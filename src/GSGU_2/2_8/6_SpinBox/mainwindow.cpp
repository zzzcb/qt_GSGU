#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QSpinBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QStandardPaths>
#include <QLabel>

#include <QPdfView>
#include <QPdfDocument>
#include <QPdfPageNavigator>

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	auto bar = menuBar();
	auto fileMenu = bar->addMenu("文件");
	auto fileOpenAct = fileMenu->addAction("打开文件");

	auto centerWidget = new QWidget;
	setCentralWidget(centerWidget);

	auto mainLayout = new QVBoxLayout(centerWidget);

	auto headerLayout = new QHBoxLayout;
	auto zoomOutBtn = new QToolButton; zoomOutBtn->setStyleSheet("background-color:transparent;");
	zoomOutBtn->setIcon(QIcon(":/images/zoomout.svg"));
	auto zoomInBtn = new QToolButton; zoomInBtn->setStyleSheet("background-color:transparent;");
	zoomInBtn->setIcon(QIcon(":/images/zoomin.svg"));
	m_pPageSpin = new QSpinBox;  m_pPageSpin->setMinimumWidth(50);
	m_pPageSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
	m_pPageCount = new QLabel(" / ");
	headerLayout->addWidget(zoomOutBtn);
	headerLayout->addWidget(zoomInBtn);
	headerLayout->addWidget(m_pPageSpin);
	headerLayout->addWidget(m_pPageCount);
	headerLayout->setAlignment(Qt::AlignHCenter);
	
	m_pPdfView = new QPdfView;
	m_pPdfView->setPageMode(QPdfView::PageMode::MultiPage);

	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(m_pPdfView);

	// 信号槽
	connect(fileOpenAct, &QAction::triggered, this, &MainWindow::slot_fileOpen);
	connect(m_pPageSpin, &QSpinBox::valueChanged, this, &MainWindow::slot_changePage);
	connect(m_pPdfView->pageNavigator(), &QPdfPageNavigator::currentPageChanged, this, &MainWindow::slot_setPageLabel);
	connect(zoomOutBtn, &QToolButton::clicked, [=]() {slot_zoomPage(m_pPdfView->zoomFactor()* 0.9); });
	connect(zoomInBtn, &QToolButton::clicked, [=]() {slot_zoomPage(m_pPdfView->zoomFactor() * 1.1); });

	m_pPdfDocument = new QPdfDocument(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_fileOpen()
{
	QString documentsDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

	auto filePath = QFileDialog::getOpenFileName(this, "选择要打开的文件", documentsDir,"pdf doc (*.pdf)");
	m_pPdfDocument->load(filePath);

	if (m_pPdfDocument->status() == QPdfDocument::Status::Ready)
	{
		m_pPdfView->setDocument(m_pPdfDocument);
		m_pPageCount->setText(QString(" /%1").arg(m_pPdfDocument->pageCount()));
		m_pPageSpin->setRange(1, m_pPdfDocument->pageCount());
	}
}

void MainWindow::slot_changePage(int page)
{
	m_pPdfView->pageNavigator()->jump(page-1,QPointF(0,0));
}

void MainWindow::slot_setPageLabel(int page)
{
	m_pPageSpin->blockSignals(true);
	m_pPageSpin->setValue(page + 1);
	m_pPageSpin->blockSignals(false);
}

void MainWindow::slot_zoomPage(qreal factor)
{
	m_pPdfView->setZoomFactor(factor);
}
