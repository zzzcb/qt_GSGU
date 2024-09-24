#include <QPushButton>
#include <QPainterPath>

class CustomButton:public QPushButton
{
public:
	CustomButton(QWidget* parent=nullptr);
	CustomButton(const QString& text, QWidget* parent = nullptr);

	virtual ~CustomButton();

protected:
	void paintEvent(QPaintEvent* e) override;

private:
	QPainterPath processRect2ChamferRect(QRect rect, qreal xGap = 10, qreal yGap = 10);
};



