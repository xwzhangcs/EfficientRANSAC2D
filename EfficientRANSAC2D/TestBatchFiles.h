#pragma once

#include <QDialog>
#include "ui_TestBatchFiles.h"

class TestBatchFiles : public QDialog
{
	Q_OBJECT

public:
	TestBatchFiles(QWidget *parent = Q_NULLPTR);
	~TestBatchFiles();
	int getCurveNumIterations();
	int getCurveMinPoints();
	float getCurveMaxErrorRatioToRadius();
	float getCurveClusterEpsilon();
	float getCurveMinAngle();
	float getCurveMinRadius();
	float getCurveMaxRadius();

	int getLineNumIterations();
	int getLineMinPoints();
	float getLineMaxError();
	float getLineClusterEpsilon();
	float getLineMinLength();
	float getLineAngleThreshold();
	bool getUseRA();
	float getRAMaxError();
	float getRAClusterEpsilon();
	bool getRAOptimization();

	float getContourMaxError();
	float getContourAngleThreshold();

	float getIOUThreshold();
	bool getUseSymmetryLineOpt();
	float getSymmetryWeight();

	bool getUseRaOpt();
	float getRaThreshold();
	float getRaWeight();

	bool getUseParallelOpt();
	float getParallelThreshold();
	float getParallelWeight();

	bool getUseAccuracyOpt();
	float getAccuracyWeight();

	bool getUseLayers();
	bool getUseOneLayer();

public:
	Ui::TestBatchFiles ui;

public slots:
	void onUseRA();
	void onGetInputPath();
	void onGetOutputPath();
	void onUseSymmetryLineOpt();
	void onUseRaOpt();
	void onUseParallelOpt();
	void onUseAccuracyOpt();
	void onOK();
	void onCancel();
};
