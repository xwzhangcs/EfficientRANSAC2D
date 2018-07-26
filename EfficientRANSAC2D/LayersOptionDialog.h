#pragma once

#include <QDialog>
#include "ui_LayersOptionDialog.h"

class LayersOptionDialog : public QDialog
{
	Q_OBJECT

public:
	LayersOptionDialog(QWidget *parent = Q_NULLPTR);
	~LayersOptionDialog();
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

public:
	Ui::LayersOptionDialog ui;

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
