#include <QtWidgets/QApplication>

#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);


	QWidget* mw = new QWidget;
	auto mainLayout = new QVBoxLayout(mw);

	//QDateTimeEdit
	QDateTimeEdit* dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), mw);
	dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
	//dateTimeEdit->setDisplayFormat("yyyy.MM.dd");
	mainLayout->addWidget(dateTimeEdit);

	//QDateEdit
	QDateEdit* dateEdit = new QDateEdit(QDate::currentDate());
	mainLayout->addWidget(dateEdit);

	//QTimeEdit
	QTimeEdit* timeEdit = new QTimeEdit(QTime::currentTime());
	mainLayout->addWidget(timeEdit);

	//QDoubleSpinBox
	QDoubleSpinBox* dsb = new QDoubleSpinBox;
	mainLayout->addWidget(dsb);

	//QSpinBox
	QSpinBox* sb = new QSpinBox(mw);
	mainLayout->addWidget(sb);
	mainLayout->addStretch();
	mw->show();
	mw->resize(500, 200);

	return a.exec();
}
