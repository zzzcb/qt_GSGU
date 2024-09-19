#include <QLayout>
#include <QLayoutItem>
#include <QList>

class MyHLayout:public QLayout
{
public:
	MyHLayout(QWidget* parent);
	virtual	~MyHLayout();

	void addItem(QLayoutItem* item) override;
	int	count() const override;
	QLayoutItem* itemAt(int index) const override;
	QLayoutItem* takeAt(int index) override;

	QSize	sizeHint() const override;

	void	setGeometry(const QRect& r) override;
	QSize minimumSize() const override;

private:
	QList<QLayoutItem*> m_lItems;
};

