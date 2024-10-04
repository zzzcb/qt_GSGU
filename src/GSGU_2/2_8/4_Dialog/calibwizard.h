#ifndef CALIBWIZARD_H
#define CALIBWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QRadioButton>

enum PageId
{
	INTR_PAGE,
	CALIBTYPE_PAGE,
	ONLINE_PAGE,
	OFFLINE_PAGE,
	FINISH_PAGE
};
class CalibTypeWizardPage :public QWizardPage
{
	Q_OBJECT
public:
	CalibTypeWizardPage(QWidget* parent = nullptr);

	int nextId() const override;

private:
	QRadioButton* m_pOnline = nullptr;
	QRadioButton* m_pOffline = nullptr;
};

class OnlineWizardPage :public QWizardPage
{
	Q_OBJECT
public:
	OnlineWizardPage(QWidget* parent = nullptr);

	int nextId() const override;
};

class CalibWizard :public QWizard
{
	Q_OBJECT
public:
	CalibWizard(QWidget* parent = nullptr);
	virtual ~CalibWizard();

private:
	QWizardPage* createIntroductionPage();
	QWizardPage* createCalibTypePage();
	QWizardPage* createOnlinePage();
	QWizardPage* createOfflinePage();
	QWizardPage* createFinishPage();
};

#endif 

