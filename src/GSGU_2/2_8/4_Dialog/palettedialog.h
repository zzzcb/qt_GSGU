#ifndef PALETTE_DIALOG_H
#define PALETTE_DIALOG_H

#include <QDialog>

class QTableWidget;
class QPushButton;
class PaletteDialog :public QDialog
{
	Q_OBJECT
public:
	PaletteDialog(QWidget* parent = nullptr);
	virtual ~PaletteDialog();

private:
	void setupTable();
	void colorClicked(QPushButton* btn);
	void resetRow(QPushButton* btn);
	void resetAll();

	QTableWidget* m_pTable = nullptr;
};


#endif 
