#include <QLabel>

class Label:public QLabel
{
	Q_OBJECT
public:
	Label(QString text,QWidget* parent = nullptr);
	virtual ~Label();

protected:
	void showEvent(QShowEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

signals:
	void killed(Label* label);


private:
	QString m_strLabel;
	QFont   m_tTxtFont;
	QColor	m_tBgClr;
};
