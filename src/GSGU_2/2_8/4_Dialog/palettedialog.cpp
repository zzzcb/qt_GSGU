#include "palettedialog.h"

#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPalette>
#include <QMetaEnum>
#include <QApplication>
#include <QPushButton>
#include <QColorDialog>
#include <QHBoxLayout>

PaletteDialog::PaletteDialog(QWidget* parent /*= nullptr*/)
	:QDialog(parent)
{
	auto mainLayout = new QVBoxLayout(this);

	//table widget 
	m_pTable = new QTableWidget;
	m_pTable->setColumnCount(5);
	m_pTable->setHorizontalHeaderLabels({ "ColorRole","Active","Inactive","Disabled","Reset" });
	
	m_pTable->verticalHeader()->setVisible(false);
	m_pTable->horizontalHeader()->setStretchLastSection(true);
	m_pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTable->setSelectionMode(QAbstractItemView::NoSelection);

	//bottom
	auto hLayout = new QHBoxLayout;
	auto resetBtn = new QPushButton("重置所有");
	auto exportBtn = new QPushButton("导出");
	auto importBtn = new QPushButton("导入");
	hLayout->addStretch();
	hLayout->addWidget(resetBtn);
	hLayout->addWidget(exportBtn);
	hLayout->addWidget(importBtn);
	
	mainLayout->addWidget(m_pTable);
	mainLayout->addLayout(hLayout);
	
	setupTable();
	resize(600, 300);

	//信号槽
	connect(resetBtn, &QPushButton::clicked, [=]() { resetAll(); });
}

PaletteDialog::~PaletteDialog()
{

}


void PaletteDialog::resetRow(QPushButton* btn)
{
	auto standardPalette = qApp->style()->standardPalette();
	QPalette::ColorRole role = QPalette::ColorRole(btn->property("ColorRole").toInt());
	auto clr1 = standardPalette.color(QPalette::Active, role);
	auto clr2 = standardPalette.color(QPalette::Inactive, role);
	auto clr3 = standardPalette.color(QPalette::Disabled, role);

	int row = btn->property("row").toInt();
	m_pTable->cellWidget(row, 1)->setStyleSheet(QString("background-color:%1;").arg(clr1.name()));
	m_pTable->cellWidget(row, 2)->setStyleSheet(QString("background-color:%1;").arg(clr2.name()));
	m_pTable->cellWidget(row, 3)->setStyleSheet(QString("background-color:%1;").arg(clr3.name()));

	auto curPalette = qApp->palette();
	curPalette.setColor(QPalette::Active, role, clr1);
	curPalette.setColor(QPalette::Inactive, role, clr2);
	curPalette.setColor(QPalette::Disabled, role, clr3);
	qApp->setPalette(curPalette);
}

void PaletteDialog::resetAll()
{
	qApp->setPalette(qApp->style()->standardPalette());

	for (int row = 0; row < m_pTable->rowCount(); ++row)
	{
		for (int col = 1; col < 4; ++col)
		{
			auto btn = (QPushButton*)(m_pTable->cellWidget(row, col));
			btn->property("ColorGroup").toInt();
			btn->property("ColorRole").toInt();

			QPalette::ColorGroup group = QPalette::ColorGroup(btn->property("ColorGroup").toInt());
			QPalette::ColorRole role = QPalette::ColorRole(btn->property("ColorRole").toInt());

			btn->setStyleSheet(QString("background-color:%1;").arg(qApp->palette().color(group, role).name()));
		}
	}
}

void PaletteDialog::setupTable()
{
	QPalette curPalette = qApp->palette();
	QMetaObject paletteMeta = QPalette::staticMetaObject;
	QMetaEnum colorRoleEnum = paletteMeta.enumerator(paletteMeta.indexOfEnumerator("ColorRole"));
	for (int i = 0; i < colorRoleEnum.keyCount() - 1; ++i) //最后一个剔除掉
	{
		QString role(colorRoleEnum.key(i));
		m_pTable->insertRow(i);
		m_pTable->setItem(i, 0, new QTableWidgetItem(role));

		auto color1 = curPalette.color(QPalette::Active, QPalette::ColorRole(colorRoleEnum.value(i)));
		auto btn1 = new QPushButton;
		btn1->setProperty("ColorGroup", QPalette::Active);
		btn1->setProperty("ColorRole", QPalette::ColorRole(colorRoleEnum.value(i)));
		btn1->setStyleSheet(QString("background-color:%1;").arg(color1.name()));
		m_pTable->setCellWidget(i, 1, btn1);

		auto color2 = curPalette.color(QPalette::Inactive, QPalette::ColorRole(colorRoleEnum.value(i)));
		auto btn2 = new QPushButton;
		btn2->setProperty("ColorGroup", QPalette::Inactive);
		btn2->setProperty("ColorRole", QPalette::ColorRole(colorRoleEnum.value(i)));
		btn2->setStyleSheet(QString("background-color:%1;").arg(color2.name()));
		m_pTable->setCellWidget(i, 2, btn2);

		auto color3 = curPalette.color(QPalette::Disabled, QPalette::ColorRole(colorRoleEnum.value(i)));
		auto btn3 = new QPushButton;
		btn3->setProperty("ColorGroup", QPalette::Disabled);
		btn3->setProperty("ColorRole", QPalette::ColorRole(colorRoleEnum.value(i)));
		btn3->setStyleSheet(QString("background-color:%1;").arg(color3.name()));
		m_pTable->setCellWidget(i, 3, btn3);

		auto reset = new QPushButton("重置");
		reset->setProperty("ColorRole", QPalette::ColorRole(colorRoleEnum.value(i)));
		reset->setProperty("row",i);
		m_pTable->setCellWidget(i, 4, reset);

		//信号槽
		connect(btn1, &QPushButton::clicked, [=]() {colorClicked(btn1); });
		connect(btn2, &QPushButton::clicked, [=]() {colorClicked(btn2); });
		connect(btn3, &QPushButton::clicked, [=]() {colorClicked(btn3); });
		connect(reset, &QPushButton::clicked, [=]() {resetRow(reset); });
	}
}

void PaletteDialog::colorClicked(QPushButton* btn)
{
	QColor clr = QColorDialog::getColor(Qt::white,this,"请选择颜色");
	if (!clr.isValid())
		return;

	QPalette::ColorGroup group = QPalette::ColorGroup(btn->property("ColorGroup").toInt());
	QPalette::ColorRole role = QPalette::ColorRole(btn->property("ColorRole").toInt());

	btn->setStyleSheet(QString("background-color:%1;").arg(clr.name()));

	auto palette = qApp->palette();
	palette.setColor(group, role, clr);
	qApp->setPalette(palette);
}
