#include <QApplication>
#include <QFormLayout>

#include <QLineEdit>
#include <QComboBox>
#include "labeleditor.h"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);

	QWidget w;
	auto layout = new QFormLayout(&w);

	LabelEditor* le = new LabelEditor;
	layout->addRow("标题", new QLineEdit);
	layout->addRow("标签", le);

	auto cb = new QComboBox;
	cb->addItems({"科技->计算机技术"});
	layout->addRow("分区", cb);

	w.resize(500, 200);
	w.show();

	return app.exec();
}
