#include "keyboarddialog.h"

#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QTreeWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QKeySequenceEdit>

KeyboardDialog::KeyboardDialog(QWidget* parent /*= nullptr*/)
	:QDialog(parent)
{
	auto mainLayout = new QVBoxLayout(this);

	auto keySearchLine = new QLineEdit;
	keySearchLine->setPlaceholderText(tr("Search for action or shortcut"));
	mainLayout->addWidget(keySearchLine);

	m_pKeyBoardTree = new QTreeWidget;
	m_pKeyBoardTree->setHeaderLabels(QStringList() << "菜单" << "快捷键");
	mainLayout->addWidget(m_pKeyBoardTree);

	auto hLayout = new QHBoxLayout;
	auto importBtn =  new QPushButton("导入");
	auto exportBtn = new QPushButton("导出");
	auto resetBtn = new QPushButton("全部重置");
	hLayout->addWidget(importBtn);
	hLayout->addWidget(exportBtn);
	hLayout->addStretch();
	hLayout->addWidget(resetBtn);
	mainLayout->addLayout(hLayout);

	//button box
	auto btnBox = new QDialogButtonBox;
	btnBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	mainLayout->addWidget(btnBox);

	//信号槽
	connect(btnBox, &QDialogButtonBox::accepted, [=]() {
		//更新快捷键
		for (auto pair : m_vAction2Keyedit)
		{
			pair.first->setShortcut(pair.second->keySequence());
		}
		this->accept();
	});
	connect(btnBox, &QDialogButtonBox::rejected, [=]() {
		this->reject();
	});
	connect(resetBtn, &QPushButton::clicked, [=]() {
		for (auto pair : m_vAction2Keyedit)
		{
			auto defaultKS = QKeySequence(pair.first->property("default").toString());

			pair.first->setShortcut(defaultKS);
			pair.second->setKeySequence(defaultKS);
		}
	});

	resize(500, 300);
	setupKeyboardShortcut(g_mainWindow->menuBar());
}

KeyboardDialog::~KeyboardDialog()
{

}

void KeyboardDialog::setupKeyboardShortcut(QMenuBar* menuBar)
{
	// menubar的所有 menu
	auto menus = menuBar->actions();

	QVector<QAction*> vActions;
	QVector<QTreeWidgetItem*> vItems;
	for (auto& menu_ : menus)
	{
		QMenu* menu = menu_->menu();

		auto menuItem = new QTreeWidgetItem;
		menuItem->setText(0, menu->title());
		m_pKeyBoardTree->addTopLevelItem(menuItem);

		// 获取当前menu下的所有action(为了简洁，这里假设没有二级menu,正常需要递归遍历)
		for (auto& action_ : menu->actions())
		{
			auto actionItem = new QTreeWidgetItem(menuItem);
			actionItem->setText(0, action_->text().replace("&", ""));

			vActions.push_back(action_);
			vItems.push_back(actionItem);
		}
	}

	for(int i=0;i< vItems.size();++i)
	{
		auto keyEdit = new QKeySequenceEdit(vActions[i]->shortcut());
		m_pKeyBoardTree->setItemWidget(vItems[i], 1, keyEdit);
		m_vAction2Keyedit.append(qMakePair(vActions[i],keyEdit));
	}
}
