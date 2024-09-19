#include <QWidget>

class VWidget :public QWidget
{
	Q_OBJECT
public:
	VWidget(QWidget* parent = nullptr);
	~VWidget();
};