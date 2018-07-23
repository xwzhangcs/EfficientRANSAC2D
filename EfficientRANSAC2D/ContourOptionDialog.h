#pragma once

#include <QDialog>
#include "ui_ContourOptionDialog.h"

class ContourOptionDialog : public QDialog {
	Q_OBJECT

private:
	Ui::ContourOptionDialog ui;

public:
	ContourOptionDialog(QWidget *parent = Q_NULLPTR);
	~ContourOptionDialog();

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

public slots:
	void onUseRA();
	void onOK();
	void onCancel();
	void onUseSymmetryLine();
	void onUseRaOpt();
	void onUseParallelOpt();
};
