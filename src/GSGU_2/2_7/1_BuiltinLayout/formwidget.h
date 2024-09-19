#include <QWidget>

class FormWidget :public QWidget
{
	Q_OBJECT
public:
	FormWidget(QWidget* parent = nullptr);
	~FormWidget();
};