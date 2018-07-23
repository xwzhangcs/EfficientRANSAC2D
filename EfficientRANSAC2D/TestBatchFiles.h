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
	bool getUseSymmetryLine();

	bool getUseRaOpt();
	float getRaThreshold();

	bool getUseParallelOpt();
	float getParalleThreshold();

public:
	Ui::TestBatchFiles ui;

public slots:
	void onUseRA();
	void onGetInputPath();
	void onGetOutputPath();
	void onUseSymmetryLine();
	void onUseRaOpt();
	void onUseParallelOpt();
	void onOK();
	void onCancel();
};
