#include <QWidget>
#include <QLayout>
#include <QStyle>

class FlowLayout : public QLayout
{
	Q_OBJECT

public:

	/** 显式构造 */
	explicit FlowLayout(QWidget* parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
	explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
	~FlowLayout();

	/** 向布局中添加项 */
	void addItem(QLayoutItem* item) override;

	/** 获取控件水平间距 */
	int getHorizontalSpacing() const;

	/** 获取控件垂直间隙 */
	int getVerticalSpacing() const;

	/** 获取控件数量 */
	int count() const override;

	/** 获取布局中某一项 */
	QLayoutItem* itemAt(int index) const override;

	/** 从布局中删除某一项并返回该项 */
	QLayoutItem* takeAt(int index) override;

	/** 设置布局矩形尺寸 */
	void setGeometry(const QRect& rect) override;

	/** 获取布局首选尺寸 */
	QSize sizeHint() const override;

	/** 获取布局最小尺寸 */
	QSize minimumSize() const override;

	/** 删除某一控件 */
	void removeItem(QLayoutItem* item);

private:

	class Impl;
	Impl* impl_;
};
