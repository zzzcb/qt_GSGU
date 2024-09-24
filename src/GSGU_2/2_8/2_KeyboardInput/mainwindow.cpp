#include "mainwindow.h"

#include <QMenuBar>
#include <QStandardPaths>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

MainWindow* g_mainWindow;

QAction* newMenuAction(const QString& text,const QKeySequence& shortcut,const QString& id)
{
	auto act = new QAction(text);
	act->setShortcut(shortcut);
	act->setProperty("id", id);
	
	return act;
}

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
	:QMainWindow(parent)
{
	g_mainWindow = this;

	//新建配置文件夹
	QDir confDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
	if (!confDir.exists())
	{
		confDir.mkdir(".");
	}
	m_sShortCutConf = confDir.absoluteFilePath("shortcut.json");

	QMenu* fileMenu = menuBar()->addMenu("文件");

	fileMenu->addAction(newMenuAction("打开项目", QKeySequence("Ctrl+O"), "Project.Open"));
	fileMenu->addAction(newMenuAction("保存项目", QKeySequence("Ctrl+S"), "Project.Save"));
	fileMenu->addAction(newMenuAction("另存项目", QKeySequence("Ctrl+Shift+S"), "Project.SaveAs"));

	menuBar()->addMenu("编辑");
	menuBar()->addMenu("视图");
	menuBar()->addMenu("Git");
	menuBar()->addMenu("工具");
	menuBar()->addMenu("帮助");

	setupShortCut();
	loadShortCut();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
	saveShortCut();
	QMainWindow::closeEvent(event);
}

void MainWindow::setupShortCut()
{
	for (auto& menu_ : menuBar()->actions())
	{
		QMenu* menu = menu_->menu();
		for (auto& action_ : menu->actions())
		{
			action_->setProperty("default", action_->shortcut().toString());
			m_vAllAction.push_back(action_);
		}
	}
}

void MainWindow::saveShortCut()
{
	QJsonArray jArr;

	for(auto& action: m_vAllAction)
	{
		auto shortCut = action->shortcut().toString();
		auto defaultShortCut = action->property("default").toString();
		//只保存用户自定义的快捷键
		if (shortCut != defaultShortCut)
		{
			QJsonObject jObj;
			jObj["id"] = action->property("id").toString();
			jObj["shortcut"] = shortCut;
			jArr.push_back(jObj);
		}
	}

	QFile f(m_sShortCutConf);
	if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		if (!jArr.isEmpty())
		{
			QJsonDocument jDoc;
			jDoc.setArray(jArr);
			f.write(jDoc.toJson());
		}
	}
	f.close();
}

void MainWindow::loadShortCut()
{
	QFile f(m_sShortCutConf);
	if (f.open(QIODevice::ReadOnly))
	{
		QJsonParseError jErr;
		QJsonDocument jDoc = QJsonDocument::fromJson(f.readAll(), &jErr);
		if (jErr.error == QJsonParseError::NoError && jDoc.isArray())
		{
			QJsonArray jArr = jDoc.array();
			for (auto jObj_ : jArr)
			{
				QJsonObject jObj = jObj_.toObject();
				QString id = jObj.value("id").toString();

				//根据文件更新最新的快捷键
				for (auto& action : m_vAllAction)
				{
					if (action->property("id").toString() == id)
					{
						action->setShortcut(QKeySequence(jObj.value("shortcut").toString()));
					}
				}
			}
		}
	}
	f.close();
}

