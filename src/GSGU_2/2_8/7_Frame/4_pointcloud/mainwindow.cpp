#include "mainwindow.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>
#include <QProgressBar>

#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>

#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>

#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	auto bar = menuBar();
	auto menuFile = bar->addMenu("文件");
	auto actOpenFile = menuFile->addAction("打开文件");

	auto vtkWidget = new QVTKOpenGLNativeWidget(this);
	auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	auto render = vtkSmartPointer<vtkRenderer>::New();
	render->SetBackground(0.3,0.3,0.3);
	renderWindow->AddRenderer(render);
	vtkWidget->setRenderWindow(renderWindow);
	setCentralWidget(vtkWidget);

	statusBar();
	m_pProgressBar = new QProgressBar;
	m_pProgressBar->setRange(0, 100);

	//信号槽
	connect(actOpenFile, &QAction::triggered, this, &MainWindow::slot_openFile);
	connect(this, &MainWindow::signal_loadProgress, this, &MainWindow::slot_loadProgress);
	connect(this, &MainWindow::signal_setGlobalEnable, this, &MainWindow::slot_setGlobalEnable);

	m_pViewer = std::make_shared<pcl::visualization::PCLVisualizer>(render, renderWindow, "Visualizer", false);
	m_pViewer->addCoordinateSystem(1000);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_openFile()
{
	statusBar()->addWidget(m_pProgressBar);

	auto filePath = QFileDialog::getOpenFileName(this, "请选择点云文件", ".", "点云文件(*.ply *.pcd)");
	auto fileExtension = QFileInfo(filePath).suffix();

	// 加载点云数据
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

	auto future = QtConcurrent::run([=](){
		emit signal_setGlobalEnable(false);
		emit signal_loadProgress(25);
		if (fileExtension == "ply")
		{
			if (pcl::io::loadPLYFile(filePath.toStdString(), *cloud) == -1)
			{
				qDebug() << "Couldn't read the PLY file.";
				return;
			}
		}
		else if (fileExtension == "pcd")
		{
			if (pcl::io::loadPCDFile(filePath.toStdString(), *cloud) == -1)
			{
				qDebug() << "Couldn't read the PCD file.";
				return;
			}
		}
		else
		{
			qDebug() << "Unsupported file format.";
			return;
		}
		emit signal_loadProgress(50);

		// 确保点云有颜色
		pcl::PointXYZRGB point = cloud->points.front();
		if (point.r == 0 && point.g == 0 && point.b == 0)
		{
			for (size_t i = 0; i < cloud->points.size(); ++i)
			{
				cloud->points[i].r = 255;
				cloud->points[i].g = 0;
				cloud->points[i].b = 0;
			}
		}
		emit signal_loadProgress(100);
		emit signal_setGlobalEnable(true);
	});

	auto watcher = new QFutureWatcher<void>;
	watcher->setFuture(future);
	connect(watcher, &QFutureWatcher<void>::finished, [=]() {
		statusBar()->removeWidget(m_pProgressBar);

		m_pViewer->addPointCloud(cloud, "id");
		m_pViewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "id");
		m_pViewer->resetCamera();
		m_pViewer->getRenderWindow()->Render();
	});
}

void MainWindow::slot_loadProgress(int percent)
{
	m_pProgressBar->setValue(percent);
}

void MainWindow::slot_setGlobalEnable(bool enable)
{
	setEnabled(enable);

	auto interactor = m_pViewer->getRenderWindow()->GetInteractor();
	if (enable)
	{
		interactor->Enable();
	}
	else
	{
		interactor->Disable();
	}
}
