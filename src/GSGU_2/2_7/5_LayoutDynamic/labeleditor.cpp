#include "labeleditor.h"
#include "label.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>


LabelEditor::LabelEditor(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout* topLayout = new QHBoxLayout;
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setPlaceholderText("按回车键Enter创建标签");
	m_pLineEdit->installEventFilter(this);
	topLayout->addWidget(m_pLineEdit);
	topLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding));

	QWidget* container = new QWidget;
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(container);

	m_pContainerLayout = new QHBoxLayout(container);
	m_pContainerLayout->setAlignment(Qt::AlignLeft);
}

LabelEditor::~LabelEditor()
{

}

bool LabelEditor::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_pLineEdit)
	{
		if (event->type() == QEvent::KeyPress)
		{
			auto keyEvent = (QKeyEvent*)event;
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				auto text = m_pLineEdit->text();
				if (text.isEmpty())
				{
					return true;
				}

				auto label = new Label(m_pLineEdit->text());
				connect(label, &Label::killed, this, &LabelEditor::slot_killLabel);
				m_pContainerLayout->addWidget(label);
				m_pLineEdit->clear();

				return true;
			}
		}
	}

	return QWidget::eventFilter(watched, event);
}

void LabelEditor::slot_killLabel(Label* label)
{
	disconnect(label, &Label::killed, this, &LabelEditor::slot_killLabel);

	m_pContainerLayout->removeWidget(label);
	label->deleteLater();
}
