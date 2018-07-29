#include "LayersOptionDialog.h"
#include <QFileDialog>

LayersOptionDialog::LayersOptionDialog(QWidget *parent)
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
	ui.lineEditSymmetryWeight->setText("0.25");

	ui.checkBoxRA->setChecked(false);
	ui.lineEditRAthreshold->setText("10");
	ui.lineEditRaWeight->setText("0.25");

	ui.checkBoxParallel->setChecked(false);
	ui.lineEditParallelThreshold->setText("10");
	ui.lineEditParallelWeight->setText("0.25");

	ui.checkBoxAccuracy->setChecked(false);
	ui.lineEditAccuracyWeight->setText("0.25");

	ui.checkBoxUseIntra->setChecked(true);
	ui.checkBoxUseIntra->setChecked(false);
	ui.lineEditIntraWeight->setText("0.5");
	ui.lineEditInterWeight->setText("0.5");

	ui.checkBoxPointSnap->setChecked(false);
	ui.lineEditPointDisThreshold->setText("5");
	ui.lineEditPointWeight->setText("0.5");
	ui.checkBoxSegSnap->setChecked(false);
	ui.lineEditSegDisThreshold->setText("5");
	ui.lineEditSegAngleThreshold->setText("10");
	ui.lineEditSegWeight->setText("0.5");

	connect(ui.checkBoxUseRA, SIGNAL(clicked()), this, SLOT(onUseRA()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.checkBoxSymmetryLine, SIGNAL(clicked()), this, SLOT(onUseSymmetryLineOpt()));
	connect(ui.checkBoxRA, SIGNAL(clicked()), this, SLOT(onUseRaOpt()));
	connect(ui.checkBoxParallel, SIGNAL(clicked()), this, SLOT(onUseParallelOpt()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(ui.pushButtonInput, SIGNAL(clicked()), this, SLOT(onGetInputPath()));
	connect(ui.pushButtonOutput, SIGNAL(clicked()), this, SLOT(onGetOutputPath()));
	connect(ui.checkBoxAccuracy, SIGNAL(clicked()), this, SLOT(onUseAccuracyOpt()));
	connect(ui.checkBoxUseIntra, SIGNAL(clicked()), this, SLOT(onUseIntraOpt()));
	connect(ui.checkBoxUseInter, SIGNAL(clicked()), this, SLOT(onUseInterOpt()));
	connect(ui.checkBoxPointSnap, SIGNAL(clicked()), this, SLOT(onUsePointSnapOpt()));
	connect(ui.checkBoxSegSnap, SIGNAL(clicked()), this, SLOT(onUseSegSnapOpt()));

	onUseRA();
	onUseSymmetryLineOpt();
	onUseRaOpt();
	onUseParallelOpt();
	onUseAccuracyOpt();
	onUseIntraOpt();
	onUseInterOpt();
	onUsePointSnapOpt();
	onUseSegSnapOpt();
}

LayersOptionDialog::~LayersOptionDialog()
{
}

int LayersOptionDialog::getCurveNumIterations() {
	return ui.lineEditCurveNumIterations->text().toInt();
}

int LayersOptionDialog::getCurveMinPoints() {
	return ui.lineEditCurveMinPoints->text().toInt();
}

float LayersOptionDialog::getCurveMaxErrorRatioToRadius() {
	return ui.lineEditCurveMaxErrorRatioToRadius->text().toFloat();
}

float LayersOptionDialog::getCurveClusterEpsilon() {
	return ui.lineEditCurveClusterEpsilon->text().toFloat();
}

float LayersOptionDialog::getCurveMinAngle() {
	return ui.lineEditCurveMinAngle->text().toFloat();
}

float LayersOptionDialog::getCurveMinRadius() {
	return ui.lineEditCurveMinRadius->text().toFloat();
}

float LayersOptionDialog::getCurveMaxRadius() {
	return ui.lineEditCurveMaxRadius->text().toFloat();
}

int LayersOptionDialog::getLineNumIterations() {
	return ui.lineEditLineNumIterations->text().toInt();
}

int LayersOptionDialog::getLineMinPoints() {
	return ui.lineEditLineMinPoints->text().toInt();
}

float LayersOptionDialog::getLineMaxError() {
	return ui.lineEditLineMaxError->text().toFloat();
}

float LayersOptionDialog::getLineClusterEpsilon() {
	return ui.lineEditLineClusterEpsilon->text().toFloat();
}

float LayersOptionDialog::getLineMinLength() {
	return ui.lineEditLineMinLength->text().toFloat();
}

float LayersOptionDialog::getLineAngleThreshold() {
	return ui.lineEditLineAngleThreshold->text().toFloat();
}

bool LayersOptionDialog::getUseRA() {
	return ui.checkBoxUseRA->isChecked();
}

float LayersOptionDialog::getRAMaxError() {
	return ui.lineEditRAMaxError->text().toFloat();
}

float LayersOptionDialog::getRAClusterEpsilon() {
	return ui.lineEditLineClusterEpsilon->text().toFloat();
}

bool LayersOptionDialog::getRAOptimization() {
	return ui.checkBoxRAOptimization->isChecked();
}

float LayersOptionDialog::getContourMaxError() {
	return ui.lineEditContourMaxError->text().toFloat();
}

float LayersOptionDialog::getContourAngleThreshold() {
	return ui.lineEditContourAngleThreshold->text().toFloat();
}

float LayersOptionDialog::getIOUThreshold(){
	return ui.lineEditIOUThreshold->text().toFloat();
}

bool LayersOptionDialog::getUseSymmetryLineOpt(){
	return ui.checkBoxSymmetryLine->isChecked();
}

float LayersOptionDialog::getSymmetryWeight(){
	return ui.lineEditSymmetryWeight->text().toFloat();
}

bool LayersOptionDialog::getUseRaOpt(){
	return ui.checkBoxRA->isChecked();
}

float LayersOptionDialog::getRaThreshold(){
	return ui.lineEditRAthreshold->text().toFloat();
}

float LayersOptionDialog::getRaWeight(){
	return ui.lineEditRaWeight->text().toFloat();
}

bool LayersOptionDialog::getUseParallelOpt(){
	return ui.checkBoxParallel->isChecked();
}

float LayersOptionDialog::getParallelThreshold(){
	return ui.lineEditParallelThreshold->text().toFloat();
}

float LayersOptionDialog::getParallelWeight(){
	return ui.lineEditParallelWeight->text().toFloat();
}

bool LayersOptionDialog::getUseAccuracyOpt(){
	return ui.checkBoxAccuracy->isChecked();
}

float LayersOptionDialog::getAccuracyWeight(){
	return ui.lineEditAccuracyWeight->text().toFloat();
}

bool LayersOptionDialog::getUseIntraOpt(){
	return ui.checkBoxUseIntra->isChecked();
}

bool LayersOptionDialog::getUseInterOpt(){
	return ui.checkBoxUseInter->isChecked();
}

float LayersOptionDialog::getIntraWeight(){
	return ui.lineEditIntraWeight->text().toFloat();
}
float LayersOptionDialog::getInterWeight(){
	return ui.lineEditInterWeight->text().toFloat();
}

bool LayersOptionDialog::getUsePointSnapOpt(){
	return ui.checkBoxPointSnap->isChecked();
}

float LayersOptionDialog::getPointDisThreshold(){
	return ui.lineEditPointDisThreshold->text().toFloat();
}

float LayersOptionDialog::getPointWeight(){
	return ui.lineEditPointWeight->text().toFloat();
}

bool LayersOptionDialog::getUseSegSnapOpt(){
	return ui.checkBoxSegSnap->isChecked();
}

float LayersOptionDialog::getSegDisThreshold(){
	return ui.lineEditSegDisThreshold->text().toFloat();
}

float LayersOptionDialog::getSegAngleThreshold(){
	return ui.lineEditSegAngleThreshold->text().toFloat();
}

float LayersOptionDialog::getSegWeight(){
	return ui.lineEditSegWeight->text().toFloat();
}

void LayersOptionDialog::onUseRA() {
	ui.lineEditRAMaxError->setEnabled(ui.checkBoxUseRA->isChecked());
	ui.lineEditRAClusterEpsilon->setEnabled(ui.checkBoxUseRA->isChecked());
	ui.checkBoxRAOptimization->setEnabled(ui.checkBoxUseRA->isChecked());
}

void LayersOptionDialog::onGetInputPath() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditInput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditInput->setText(dir);
	}
}

void LayersOptionDialog::onGetOutputPath(){
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutput->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutput->setText(dir);
	}
}

void LayersOptionDialog::onUseSymmetryLineOpt() {
	ui.lineEditIOUThreshold->setEnabled(ui.checkBoxSymmetryLine->isChecked());
	ui.lineEditSymmetryWeight->setEnabled(ui.checkBoxSymmetryLine->isChecked());
}

void LayersOptionDialog::onUseRaOpt(){
	ui.lineEditRAthreshold->setEnabled(ui.checkBoxRA->isChecked());
	ui.lineEditRaWeight->setEnabled(ui.checkBoxRA->isChecked());
}

void LayersOptionDialog::onUseParallelOpt(){
	ui.lineEditParallelThreshold->setEnabled(ui.checkBoxParallel->isChecked());
	ui.lineEditParallelWeight->setEnabled(ui.checkBoxParallel->isChecked());
}

void LayersOptionDialog::onUseAccuracyOpt(){
	ui.lineEditAccuracyWeight->setEnabled(ui.checkBoxAccuracy->isChecked());
}

// new functions
void LayersOptionDialog::onUseIntraOpt(){
	ui.lineEditIntraWeight->setEnabled(ui.checkBoxUseIntra->isChecked());
	ui.checkBoxRA->setEnabled(ui.checkBoxUseIntra->isChecked());
	if (!ui.checkBoxUseIntra->isChecked()){
		ui.checkBoxRA->setChecked(false);
		onUseRaOpt();
	}
	ui.checkBoxParallel->setEnabled(ui.checkBoxUseIntra->isChecked());
	if (!ui.checkBoxUseIntra->isChecked()){
		ui.checkBoxParallel->setChecked(false);
		onUseParallelOpt();
	}
	ui.checkBoxSymmetryLine->setEnabled(ui.checkBoxUseIntra->isChecked());
	if (!ui.checkBoxUseIntra->isChecked()){
		ui.checkBoxSymmetryLine->setChecked(false);
		onUseSymmetryLineOpt();
	}
	ui.checkBoxAccuracy->setEnabled(ui.checkBoxUseIntra->isChecked());
	if (!ui.checkBoxUseIntra->isChecked()){
		ui.checkBoxAccuracy->setChecked(false);
		onUseAccuracyOpt();
	}
}

void LayersOptionDialog::onUseInterOpt(){
	ui.lineEditInterWeight->setEnabled(ui.checkBoxUseInter->isChecked());
	ui.checkBoxPointSnap->setEnabled(ui.checkBoxUseInter->isChecked());
	if (!ui.checkBoxUseInter->isChecked()){
		ui.checkBoxPointSnap->setChecked(false);
		onUsePointSnapOpt();
	}
	ui.checkBoxSegSnap->setEnabled(ui.checkBoxUseInter->isChecked());
	if (!ui.checkBoxUseInter->isChecked()){
		ui.checkBoxSegSnap->setChecked(false);
		onUseSegSnapOpt();
	}
}

void LayersOptionDialog::onUsePointSnapOpt(){
	ui.lineEditPointDisThreshold->setEnabled(ui.checkBoxPointSnap->isChecked());
	ui.lineEditPointWeight->setEnabled(ui.checkBoxPointSnap->isChecked());
}

void LayersOptionDialog::onUseSegSnapOpt(){
	ui.lineEditSegDisThreshold->setEnabled(ui.checkBoxSegSnap->isChecked());
	ui.lineEditSegAngleThreshold->setEnabled(ui.checkBoxSegSnap->isChecked());
	ui.lineEditSegWeight->setEnabled(ui.checkBoxSegSnap->isChecked());
}

void LayersOptionDialog::onOK() {
	accept();
}

void LayersOptionDialog::onCancel() {
	reject();
}