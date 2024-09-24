#include <QApplication>

#include <QWidget>
#include <QVBoxLayout>

#include <QLineEdit>
#include <QFileDialog>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QKeySequenceEdit>

#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>

class MyWidget :public QWidget 
{
	Q_OBJECT
public:
	MyWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		initUi();
	}
	void initUi()
	{
		auto mainLayout = new QVBoxLayout(this);

		//QLineEdit
		m_pLe = new QLineEdit;
		m_pLe->setPlaceholderText("请输入解释器的路径(双击选择路径)");
		m_pLe->installEventFilter(this);
		mainLayout->addWidget(m_pLe);

		//QTextEdit
		mainLayout->addWidget(new QTextEdit("text edit"));

		//QPlainTextEdit 
		mainLayout->addWidget(new QPlainTextEdit("plain text edit"));

		//QKeySequenceEdit
		auto keyEdit = new QKeySequenceEdit;
		keyEdit->setMaximumSequenceLength(2);
		mainLayout->addWidget(keyEdit);
	}
	bool eventFilter(QObject *watched, QEvent *event) override
	{
		if (watched == m_pLe)
		{
			if (event->type() == QEvent::MouseButtonDblClick)
			{
				QString exePath = QFileDialog::getOpenFileName(nullptr, "请选择exe文件路径", "D:", "(*.exe)");
				m_pLe->setText(exePath);

				return true;
			}
		}
		return QWidget::eventFilter(watched, event);
	}

private:
	QLineEdit* m_pLe;
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyWidget w;
	w.resize(600, 400);
	w.show();

	return a.exec();
}

#include "main.moc"