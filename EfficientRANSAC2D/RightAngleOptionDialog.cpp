#include "RightAngleOptionDialog.h"

RightAngleOptionDialog::RightAngleOptionDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.spinBoxResolution->setValue(20);
	ui.checkBoxOptimization->setChecked(false);

	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

RightAngleOptionDialog::~RightAngleOptionDialog() {
}

int RightAngleOptionDialog::getResolution() {
	return ui.spinBoxResolution->value();
}

bool RightAngleOptionDialog::getOptimization() {
	return ui.checkBoxOptimization->isChecked();
}

void RightAngleOptionDialog::onOK() {
	accept();
}

void RightAngleOptionDialog::onCancel() {
	reject();
}
