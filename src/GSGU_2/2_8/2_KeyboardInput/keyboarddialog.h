#include <QDialog>
#include <QMenuBar>

#include <QVector>
#include <QPair>

class QTreeWidget;
class QKeySequenceEdit;
class KeyboardDialog:public QDialog
{
	Q_OBJECT
public:
	KeyboardDialog(QWidget* parent = nullptr);
	virtual ~KeyboardDialog();


private:
	void setupKeyboardShortcut(QMenuBar* menuBar);

	QTreeWidget*		m_pKeyBoardTree;
	QVector<QPair<QAction*, QKeySequenceEdit*>> m_vAction2Keyedit;
};

