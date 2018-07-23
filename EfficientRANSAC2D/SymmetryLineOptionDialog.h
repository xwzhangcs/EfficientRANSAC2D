#pragma once

#include <QDialog>
#include "ui_SymmetryLineOptionDialog.h"

class SymmetryLineOptionDialog : public QDialog
{
	Q_OBJECT

public:
	SymmetryLineOptionDialog(QWidget *parent = Q_NULLPTR);
	~SymmetryLineOptionDialog();
	float getIOUThreshold();

private:
	Ui::SymmetryLineOptionDialog ui;

public slots:
	void onOK();
	void onCancel();
};
