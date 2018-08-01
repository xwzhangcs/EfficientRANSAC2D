#pragma once

#include <QDialog>
#include "ui_MultiRunsDialog.h"

class MultiRunsDialog : public QDialog
{
	Q_OBJECT

public:
	MultiRunsDialog(QWidget *parent = Q_NULLPTR);
	~MultiRunsDialog();

public:
	Ui::MultiRunsDialog ui;
	
public slots:
	void onGetInputPath();
	void onGetOutputPath();
	void onGetConfigFile();
	void onGetDetectFile();
	void onOK();
	void onCancel();
};
