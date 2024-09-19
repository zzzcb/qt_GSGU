#include <QWidget>

class StackWidget :public QWidget
{
	Q_OBJECT
public:
	StackWidget(QWidget* parent = nullptr);
	~StackWidget();
};