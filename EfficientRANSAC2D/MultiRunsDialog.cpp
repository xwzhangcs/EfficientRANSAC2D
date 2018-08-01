#include "MultiRunsDialog.h"
#include <QFileDialog>

MultiRunsDialog::MultiRunsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(ui.pushButtonInput, SIGNAL(clicked()), this, SLOT(onGetInputPath())); 
	connect(ui.pushButtonOutput, SIGNAL(clicked()), this, SLOT(onGetOutputPath()));
	connect(ui.pushButtonInputConfig, SIGNAL(clicked()), this, SLOT(onGetConfigFile()));
}

MultiRunsDialog::~MultiRunsDialog()
{
}

void MultiRunsDialog::onGetInputPath() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditInput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditInput->setText(dir);
	}
}

void MultiRunsDialog::onGetOutputPath(){
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutput->setText(dir);
	}
}

void MultiRunsDialog::onGetConfigFile(){
	QString dir = QFileDialog::getOpenFileName(this, tr("Load config file..."), ui.lineEditInputConfig->text(), tr("Config file (*.json)"));
	if (!dir.isEmpty()) {
		ui.lineEditInputConfig->setText(dir);
	}
}

void MultiRunsDialog::onOK() {
	accept();
}

void MultiRunsDialog::onCancel() {
	reject();
}
