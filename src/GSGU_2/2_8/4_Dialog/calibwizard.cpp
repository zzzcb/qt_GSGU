#include "calibwizard.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QRadioButton>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>


CalibWizard::CalibWizard(QWidget* parent /*= nullptr*/)
	:QWizard(parent)
{
	setWizardStyle(QWizard::ClassicStyle);
	setWindowTitle("相机内参标定");

	setPage(PageId::INTR_PAGE, createIntroductionPage());
	setPage(PageId::CALIBTYPE_PAGE, createCalibTypePage());
	setPage(PageId::ONLINE_PAGE, createOnlinePage());
	setPage(PageId::OFFLINE_PAGE, createOfflinePage());
	setPage(PageId::FINISH_PAGE, createFinishPage());
}

CalibWizard::~CalibWizard()
{

}

QWizardPage* CalibWizard::createIntroductionPage()
{
	auto page = new QWizardPage;
	page->setTitle("介绍");

	auto mainLayout = new QHBoxLayout(page);
	
	auto intro = new QTextEdit;
	intro->setReadOnly(true);

	QFile f(":/camera_intrparm.md");
	if (f.open(QIODevice::ReadOnly))
	{
		intro->setMarkdown(QString(f.readAll()));
	}
	f.close();

	mainLayout->addWidget(intro);

	return page;
}

QWizardPage* CalibWizard::createCalibTypePage()
{
	return new CalibTypeWizardPage;
}

QWizardPage* CalibWizard::createOnlinePage()
{
	return new OnlineWizardPage;
}


QWizardPage* CalibWizard::createOfflinePage()
{
	auto page = new QWizardPage;
	page->setTitle("离线标定");

	auto mainLayout =new QFormLayout(page);
	mainLayout->addRow("请选择本地图片文件夹", new QLineEdit);

	return page;
}

QWizardPage* CalibWizard::createFinishPage()
{
	auto page = new QWizardPage;
	page->setTitle("标定完成");

	auto hLayout = new QHBoxLayout(page);

	auto finishLabel = new QLabel;
	finishLabel->setPixmap(QPixmap(":/images/finish.svg"));
	hLayout->addWidget(finishLabel,0,Qt::AlignCenter);

	return page;
}

//CalibTypeWizardPage
CalibTypeWizardPage::CalibTypeWizardPage(QWidget* parent /* = nullptr */)
	:QWizardPage(parent)
{
	setTitle("请选择标定类型");

	auto vLayout = new QVBoxLayout(this);
	m_pOnline = new QRadioButton("在线,从相机获取图片");
	m_pOffline = new QRadioButton("离线,使用本地保存的历史图片");
	vLayout->addWidget(m_pOnline);
	vLayout->addWidget(m_pOffline);

	m_pOnline->setChecked(true);
}

int CalibTypeWizardPage::nextId() const
{
	if (m_pOnline->isChecked())
	{
		return PageId::ONLINE_PAGE;
	}
	else if (m_pOffline->isChecked())
	{
		return PageId::OFFLINE_PAGE;
	}
}

//OnlineWizardPage
OnlineWizardPage::OnlineWizardPage(QWidget* parent /*= nullptr*/)
	:QWizardPage(parent)
{
	setTitle("在线标定");

	auto mainLayout = new QVBoxLayout(this);
	
	auto cameraLayout = new QHBoxLayout;
	cameraLayout->addWidget(new QLabel("选择该电脑上的可用相机"));
	cameraLayout->addWidget(new QComboBox,1);
	cameraLayout->addWidget(new QPushButton("连接"));

	mainLayout->addLayout(cameraLayout);
}

int OnlineWizardPage::nextId() const
{
	return PageId::FINISH_PAGE;
}
