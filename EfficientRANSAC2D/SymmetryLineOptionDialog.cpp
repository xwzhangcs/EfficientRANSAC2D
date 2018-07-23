#include "SymmetryLineOptionDialog.h"

SymmetryLineOptionDialog::SymmetryLineOptionDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEditMaxError->setText("90");

	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

SymmetryLineOptionDialog::~SymmetryLineOptionDialog()
{
}

float SymmetryLineOptionDialog::getIOUThreshold() {
	return ui.lineEditMaxError->text().toFloat();
}


void SymmetryLineOptionDialog::onOK() {
	accept();
}

void SymmetryLineOptionDialog::onCancel() {
	reject();
}
