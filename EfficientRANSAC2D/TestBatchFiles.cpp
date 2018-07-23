#include "TestBatchFiles.h"
#include <QFileDialog>

TestBatchFiles::TestBatchFiles(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEditCurveNumIterations->setText("200000");
	ui.lineEditCurveMinPoints->setText("200");
	ui.lineEditCurveMaxErrorRatioToRadius->setText("0.02");
	ui.lineEditCurveClusterEpsilon->setText("30");
	ui.lineEditCurveMinAngle->setText("90");
	ui.lineEditCurveMinRadius->setText("80");
	ui.lineEditCurveMaxRadius->setText("400");

	ui.lineEditLineNumIterations->setText("20000");
	ui.lineEditLineMinPoints->setText("30");
	ui.lineEditLineMaxError->setText("5");
	ui.lineEditLineClusterEpsilon->setText("20");
	ui.lineEditLineMinLength->setText("30");
	ui.lineEditLineAngleThreshold->setText("15");
	ui.checkBoxUseRA->setChecked(false);
	ui.lineEditRAMaxError->setText("20");
	ui.lineEditRAClusterEpsilon->setText("20");
	ui.checkBoxRAOptimization->setChecked(true);

	ui.lineEditContourMaxError->setText("20");
	ui.lineEditContourAngleThreshold->setText("10");
	ui.checkBoxSymmetryLine->setChecked(false);
	ui.lineEditIOUThreshold->setText("90");

	ui.checkBoxRA->setChecked(false);
	ui.lineEditRAthreshold->setText("10");

	ui.checkBoxParallel->setChecked(false);
	ui.lineEditParallelThreshold->setText("10");

	connect(ui.checkBoxUseRA, SIGNAL(clicked()), this, SLOT(onUseRA()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.checkBoxSymmetryLine, SIGNAL(clicked()), this, SLOT(onUseSymmetryLine()));
	connect(ui.checkBoxRA, SIGNAL(clicked()), this, SLOT(onUseRaOpt()));
	connect(ui.checkBoxParallel, SIGNAL(clicked()), this, SLOT(onUseParallelOpt()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(ui.pushButtonInput, SIGNAL(clicked()), this, SLOT(onGetInputPath()));
	connect(ui.pushButtonOutput, SIGNAL(clicked()), this, SLOT(onGetOutputPath()));

	onUseRA();
	onUseSymmetryLine();
	onUseRaOpt();
	onUseParallelOpt();
}

TestBatchFiles::~TestBatchFiles()
{
}

int TestBatchFiles::getCurveNumIterations() {
	return ui.lineEditCurveNumIterations->text().toInt();
}

int TestBatchFiles::getCurveMinPoints() {
	return ui.lineEditCurveMinPoints->text().toInt();
}

float TestBatchFiles::getCurveMaxErrorRatioToRadius() {
	return ui.lineEditCurveMaxErrorRatioToRadius->text().toFloat();
}

float TestBatchFiles::getCurveClusterEpsilon() {
	return ui.lineEditCurveClusterEpsilon->text().toFloat();
}

float TestBatchFiles::getCurveMinAngle() {
	return ui.lineEditCurveMinAngle->text().toFloat();
}

float TestBatchFiles::getCurveMinRadius() {
	return ui.lineEditCurveMinRadius->text().toFloat();
}

float TestBatchFiles::getCurveMaxRadius() {
	return ui.lineEditCurveMaxRadius->text().toFloat();
}

int TestBatchFiles::getLineNumIterations() {
	return ui.lineEditLineNumIterations->text().toInt();
}

int TestBatchFiles::getLineMinPoints() {
	return ui.lineEditLineMinPoints->text().toInt();
}

float TestBatchFiles::getLineMaxError() {
	return ui.lineEditLineMaxError->text().toFloat();
}

float TestBatchFiles::getLineClusterEpsilon() {
	return ui.lineEditLineClusterEpsilon->text().toFloat();
}

float TestBatchFiles::getLineMinLength() {
	return ui.lineEditLineMinLength->text().toFloat();
}

float TestBatchFiles::getLineAngleThreshold() {
	return ui.lineEditLineAngleThreshold->text().toFloat();
}

bool TestBatchFiles::getUseRA() {
	return ui.checkBoxUseRA->isChecked();
}

float TestBatchFiles::getRAMaxError() {
	return ui.lineEditRAMaxError->text().toFloat();
}

float TestBatchFiles::getRAClusterEpsilon() {
	return ui.lineEditLineClusterEpsilon->text().toFloat();
}

bool TestBatchFiles::getRAOptimization() {
	return ui.checkBoxRAOptimization->isChecked();
}

float TestBatchFiles::getContourMaxError() {
	return ui.lineEditContourMaxError->text().toFloat();
}

float TestBatchFiles::getContourAngleThreshold() {
	return ui.lineEditContourAngleThreshold->text().toFloat();
}

float TestBatchFiles::getIOUThreshold(){
	return ui.lineEditIOUThreshold->text().toFloat();
}

bool TestBatchFiles::getUseSymmetryLine(){
	return ui.checkBoxSymmetryLine->isChecked();
}

bool TestBatchFiles::getUseRaOpt(){
	return ui.checkBoxRA->isChecked();
}

float TestBatchFiles::getRaThreshold(){
	return ui.lineEditRAthreshold->text().toFloat();
}

bool TestBatchFiles::getUseParallelOpt(){
	return ui.checkBoxParallel->isChecked();
}

float TestBatchFiles::getParalleThreshold(){
	return ui.lineEditParallelThreshold->text().toFloat();
}

void TestBatchFiles::onUseRA() {
	ui.lineEditRAMaxError->setEnabled(ui.checkBoxUseRA->isChecked());
	ui.lineEditRAClusterEpsilon->setEnabled(ui.checkBoxUseRA->isChecked());
	ui.checkBoxRAOptimization->setEnabled(ui.checkBoxUseRA->isChecked());
}

void TestBatchFiles::onGetInputPath() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditInput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditInput->setText(dir);
	}
}

void TestBatchFiles::onGetOutputPath(){
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutput->setText(dir);
	}
}

void TestBatchFiles::onUseSymmetryLine() {
	ui.lineEditIOUThreshold->setEnabled(ui.checkBoxSymmetryLine->isChecked());
}

void TestBatchFiles::onUseRaOpt(){
	ui.lineEditRAthreshold->setEnabled(ui.checkBoxRA->isChecked());
}

void TestBatchFiles::onUseParallelOpt(){
	ui.lineEditParallelThreshold->setEnabled(ui.checkBoxParallel->isChecked());
}

void TestBatchFiles::onOK() {
	accept();
}

void TestBatchFiles::onCancel() {
	reject();
}
