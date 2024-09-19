#include "flowlayout.h"

class FlowLayout::Impl
{
public:
	int					m_hSpace;			///< 水平间距    
	int					m_vSpace;			///< 垂直间距
	QList<QLayoutItem*> m_itemList;			///< 控件列表
	FlowLayout*		m_flowLayout;			///< 主流式布局类

	Impl(FlowLayout* parent, int margin, int hSpacing, int vSpacing) : m_flowLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing) {}
	
	/** 布局布置 */
	int doLayout(const QRect& rect, bool testOnly) const;

	/** 组件之间间距计算 */
	int calSmartSpacing(QStyle::PixelMetric pm) const;
};

/** *******************************************************************
* @brief  	   构造
* @param[in]   parent ———— 父窗体
* @param[in]   margin ———— 外边距
* @param[in]   hSpacing ———— 水平间距
* @param[in]   vSpacing ———— 垂直边距
* @return      void
******************************************************************** */
FlowLayout::FlowLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
	: QLayout(parent), impl_(new Impl(this, margin, hSpacing, vSpacing))
{
	setContentsMargins(margin, margin, margin, margin);
}

/** *******************************************************************
* @brief  	   构造
* @param[in]   margin ———— 外边距
* @param[in]   hSpacing ———— 水平间距
* @param[in]   vSpacing ———— 垂直边距
* @return      void
******************************************************************** */
FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
	: impl_(new Impl(this, margin, hSpacing, vSpacing))
{
	setContentsMargins(margin, margin, margin, margin);
}

/** *******************************************************************
* @brief  	   析构
* @return      void
******************************************************************** */
FlowLayout::~FlowLayout()
{
	QLayoutItem* item;
	while ((item = takeAt(0)))
	{
		delete item;
	}
	delete impl_;
}

/** *******************************************************************
* @brief  	   向布局中添加项
* @param[in]   item ———— 项
* @return      void
******************************************************************** */
void FlowLayout::addItem(QLayoutItem* item)
{
	if (item == Q_NULLPTR)
	{
		return;
	}
	impl_->m_itemList.append(item);
}

/** *******************************************************************
* @brief  	   获取控件水平间距
* @return      void
******************************************************************** */
int FlowLayout::getHorizontalSpacing() const
{
	if (impl_->m_hSpace >= 0)
	{
		return impl_->m_hSpace;
	}

	return impl_->calSmartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

/** *******************************************************************
* @brief  	   获取控件垂直间距
* @return      void
******************************************************************** */
int FlowLayout::getVerticalSpacing() const
{
	if (impl_->m_vSpace >= 0)
	{
		return impl_->m_vSpace;
	}

	return impl_->calSmartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

/** *******************************************************************
* @brief  	   获取控件数量
* @return      int
******************************************************************** */
int FlowLayout::count() const
{
	return impl_->m_itemList.size();
}

/** *******************************************************************
* @brief  	   获取布局中某一项
* @param[in]   index ———— 索引
* @return      QLayoutItem
******************************************************************** */
QLayoutItem* FlowLayout::itemAt(int index) const
{
	if (index >= 0 && index < impl_->m_itemList.size())
	{
		return impl_->m_itemList.value(index);
	}
	return nullptr;
}

/** *******************************************************************
* @brief  	   从布局中删除某一项并返回该项
* @param[in]   index ———— 索引
* @return      QLayoutItem
******************************************************************** */
QLayoutItem* FlowLayout::takeAt(int index)
{
	if (index >= 0 && index < impl_->m_itemList.size())
	{
		return impl_->m_itemList.takeAt(index);
	}	
	return nullptr;
}

/** *******************************************************************
* @brief  	   设置布局矩形尺寸
* @param[in]   rect ———— 矩形尺寸
* @return      void
******************************************************************** */
void FlowLayout::setGeometry(const QRect& rect)
{
	QLayout::setGeometry(rect);
	impl_->doLayout(rect, false);
}

/** *******************************************************************
* @brief  	   获取布局首选尺寸
* @return      QSize
******************************************************************** */
QSize FlowLayout::sizeHint() const
{
	return minimumSize();
}

/** *******************************************************************
* @brief  	   获取布局最小尺寸
* @return      QSize
******************************************************************** */
QSize FlowLayout::minimumSize() const
{
	QSize size;
	for (const QLayoutItem* item : std::as_const(impl_->m_itemList))
	{
		size = size.expandedTo(item->minimumSize());
	}
		
	const QMargins margins = contentsMargins();
	size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
	return size;
}

/** *******************************************************************
* @brief  	   布局布置
* @param[in]   rect ———— 矩形尺寸
* @param[in]   testOnly ———— 是否是测试
* @return      int
******************************************************************** */
int FlowLayout::Impl::doLayout(const QRect& rect, bool testOnly) const
{
	int left, top, right, bottom;
	/** 获取布局中可用部分 */
	m_flowLayout->getContentsMargins(&left, &top, &right, &bottom);
	QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
	int x = effectiveRect.x();
	int y = effectiveRect.y();
	int lineHeight = 0;

	/** 根据当前布局内部件设置适当间隙 */
	for (QLayoutItem* item : std::as_const(m_itemList))
	{
		const QWidget* wid = item->widget();
		int spaceX = m_flowLayout->getHorizontalSpacing();
		if (spaceX == -1)
		{
			spaceX = wid->style()->layoutSpacing(
				QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
		}
			
		int spaceY = m_flowLayout->getVerticalSpacing();
		if (spaceY == -1)
		{
			spaceY = wid->style()->layoutSpacing(
				QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
		}
			
		/** 计算每个控件的位置 */
		int nextX = x + item->sizeHint().width() + spaceX;
		if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
		{
			x = effectiveRect.x();
			y = y + lineHeight + spaceY;
			nextX = x + item->sizeHint().width() + spaceX;
			lineHeight = 0;
		}

		if (!testOnly)
		{
			item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
		}
		x = nextX;
		lineHeight = qMax(lineHeight, item->sizeHint().height());
	}
	return y + lineHeight - rect.y() + bottom;
}

/** *******************************************************************
* @brief  	   组件之间距离计算
* @param[in]   pm ———— 间距样式
* @return      int
******************************************************************** */
int FlowLayout::Impl::calSmartSpacing(QStyle::PixelMetric pm) const
{
	QObject* parent = m_flowLayout->parent();
	if (!parent)
	{
		return -1;
	}
	else if (parent->isWidgetType()) 
	{
		QWidget* pw = static_cast<QWidget*>(parent);
		return pw->style()->pixelMetric(pm, nullptr, pw);
	}

	return static_cast<QLayout*>(parent)->spacing();
}

/** *******************************************************************
* @brief  	   删除某一控件
* @param[in]   item ———— 控件
* @return      int
******************************************************************** */
void FlowLayout::removeItem(QLayoutItem* item)
{
	if (item == Q_NULLPTR)
	{
		return;
	}
	impl_->m_itemList.removeOne(item);
	item->widget()->setParent(nullptr);
	delete item;
}