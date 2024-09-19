#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>

class Label;
class LabelEditor:public QWidget
{
	Q_OBJECT
public:
	LabelEditor(QWidget* parent = nullptr);
	virtual ~LabelEditor();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void slot_killLabel(Label* label);

	QLineEdit* m_pLineEdit = nullptr;
	QHBoxLayout* m_pContainerLayout = nullptr;
};
