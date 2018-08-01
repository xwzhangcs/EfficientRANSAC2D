#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Canvas.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	Ui::MainWindowClass ui;
	Canvas canvas;

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void onOpen();
	void onSave();
	void onDetectCurves();
	void onDetectLines();
	void onRightAngle();
	void onDetectSymmetryLine();
	void onDetectCurvesLines();
	void onGenerateContours();
	void onTestBatchFiles();
	void onTestReflection();
	void onTestUseLayers();
	void onCombineImages();
	void onMultipleRuns();
};
