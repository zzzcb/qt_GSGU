#include "mainwindow.h"

#include "config.h"
#include "icon.h"
#include <QStandardPaths>
#include <QDir>
#include <QToolBar>
#include <QPushButton>
#include <QDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPalette>
#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget* parent /* = nullptr */)
	:QMainWindow(parent)
{
	auto confDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
	QDir dir(confDir);
	if (!dir.exists())
	{
		dir.mkdir(".");
	}
	m_sConfigPath = dir.absoluteFilePath("config.json");
	g_config.load(m_sConfigPath);

	initTheme();
	setupUi();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	g_config.save(m_sConfigPath);
	QMainWindow::closeEvent(event);
}

void MainWindow::initTheme()
{
	qApp->setStyle(QStyleFactory::create("Fusion"));

	QPalette palette;
	if (g_config.m_tTheme == Theme::LIGHT)
	{
		palette.setColor(QPalette::Window, QColor(208, 208, 208));
		palette.setColor(QPalette::WindowText, Qt::black);
		palette.setColor(QPalette::Base, QColor(240, 240, 240));
		palette.setColor(QPalette::AlternateBase, QColor(208, 208, 208));
		palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 255));
		palette.setColor(QPalette::ToolTipText, Qt::black);
		palette.setColor(QPalette::Text, Qt::black);
		palette.setColor(QPalette::Button, QColor(208, 208, 208));
		palette.setColor(QPalette::ButtonText, Qt::black);
		palette.setColor(QPalette::BrightText, Qt::red);
		palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(208, 208, 208));
		palette.setColor(QPalette::Link, QColor(42, 130, 218));
		palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
		palette.setColor(QPalette::HighlightedText, Qt::white);
	}
	else if (g_config.m_tTheme == Theme::DARK)
	{
		palette.setColor(QPalette::Window, QColor(53, 53, 53));
		palette.setColor(QPalette::WindowText, Qt::white);
		palette.setColor(QPalette::Base, QColor(25, 25, 25));
		palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
		palette.setColor(QPalette::ToolTipBase, QColor(25, 25, 25));
		palette.setColor(QPalette::ToolTipText, Qt::white);
		palette.setColor(QPalette::Text, Qt::white);
		palette.setColor(QPalette::Button, QColor(53, 53, 53));
		palette.setColor(QPalette::ButtonText, Qt::white);
		palette.setColor(QPalette::BrightText, Qt::red);
		palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(128, 128, 128));
		palette.setColor(QPalette::Link, QColor(42, 130, 218));
		palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
		palette.setColor(QPalette::HighlightedText, Qt::white);
	}
	qApp->setPalette(palette);
}

void MainWindow::setupUi()
{
	QToolBar* leftBar = new QToolBar(this);
	leftBar->addAction(createIconFromSVG(":/images/arrow.svg"), "arrow");
	leftBar->addAction(createIconFromSVG(":/images/audiosource.svg"), "audiosource");
	leftBar->addAction(createIconFromSVG(":/images/beam.svg"), "beam");
	leftBar->addAction(createIconFromSVG(":/images/clock.svg"), "clock");
	/*auto act =*/leftBar->addAction(createIconFromSVG(":/images/diamond.svg"), "diamond");
	//act->setEnabled(false);
	addToolBar(Qt::LeftToolBarArea,leftBar);


	auto btn = new QPushButton("点击我设置主题");
	setCentralWidget(btn);

	connect(btn, &QPushButton::clicked, [=]() {
		QDialog dlg;
		QFormLayout layout(&dlg);
		QComboBox cb;
		cb.addItem("Light", Theme::LIGHT);
		cb.addItem("Dark", Theme::DARK);
		layout.addRow("主题", &cb);
		cb.setCurrentIndex(g_config.m_tTheme);

		dlg.resize(200, 100);
		dlg.exec();

		int ret = QMessageBox::question(this,
			"Restart Required",
			"Some of the changed settings will require a restart of Olive. Would you like "
			"to restart now?",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (ret == QMessageBox::Yes)
		{
			g_config.m_tTheme = static_cast<Theme>(cb.currentData().toInt());

			close();
			QProcess::startDetached(QApplication::applicationFilePath());
		}
	});

	resize(1000, 500);
}

MainWindow::~MainWindow()
{

}



