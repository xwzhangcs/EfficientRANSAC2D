#include "MainWindow.h"
#include <QFileDialog>
#include "CurveOptionDialog.h"
#include "LineOptionDialog.h"
#include "CurveLineOptionDialog.h"
#include "ContourOptionDialog.h"
#include "RightAngleOptionDialog.h"
#include "TestBatchFiles.h"
#include "SymmetryLineOptionDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	setCentralWidget(&canvas);
	
	// create tool bar for file menu
	ui.mainToolBar->addAction(ui.actionOpen);
	ui.mainToolBar->addAction(ui.actionSave);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(ui.actionGenerateContours);

	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionDetectCurves, SIGNAL(triggered()), this, SLOT(onDetectCurves()));
	connect(ui.actionDetectLines, SIGNAL(triggered()), this, SLOT(onDetectLines()));
	connect(ui.actionRightAngle, SIGNAL(triggered()), this, SLOT(onRightAngle()));
	connect(ui.actionDetectCurvesLines, SIGNAL(triggered()), this, SLOT(onDetectCurvesLines()));
	connect(ui.actionGenerateContours, SIGNAL(triggered()), this, SLOT(onGenerateContours()));
	connect(ui.actionBatchFiles, SIGNAL(triggered()), this, SLOT(onTestBatchFiles())); 
	connect(ui.actionReflection, SIGNAL(triggered()), this, SLOT(onTestReflection()));
	connect(ui.actionDetectSymmetryLine, SIGNAL(triggered()), this, SLOT(onDetectSymmetryLine()));
}

void MainWindow::onOpen() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load image..."), "", tr("Image files (*.png *.jpg *.bmp)"));
	if (filename.isEmpty()) return;

	setWindowTitle("Efficient RANSAC 2D - " + filename);
	
	canvas.loadImage(filename);
	canvas.update();
}

void MainWindow::onSave() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save image..."), "", tr("Image files (*.png *.jpg *.bmp)"));
	if (filename.isEmpty()) return;

	canvas.saveImage(filename);
	canvas.update();
}

void MainWindow::onDetectCurves() {
	CurveOptionDialog dlg;
	if (dlg.exec()) {
		canvas.detectCurves(dlg.getNumIterations(), dlg.getMinPoints(), dlg.getMaxErrorRatioToRadius(), dlg.getClusterEpsilon(), dlg.getMinAngle() / 180.0 * CV_PI, dlg.getMinRadius(), dlg.getMaxRadius());
		canvas.update();
	}
}

void MainWindow::onDetectLines() {
	LineOptionDialog dlg;
	if (dlg.exec()) {
		canvas.detectLines(dlg.getNumIterations(), dlg.getMinPoints(), dlg.getMaxError(), dlg.getClusterEpsilon(), dlg.getMinLength(), dlg.getAngleThreshold() / 180.0 * CV_PI);
		canvas.update();
	}
}

void MainWindow::onRightAngle() {
	RightAngleOptionDialog dlg;
	if (dlg.exec()) {
		canvas.rightAngle(dlg.getResolution(), dlg.getOptimization());
		canvas.update();
	}
}

void MainWindow::onDetectCurvesLines() {
	CurveLineOptionDialog dlg;
	if (dlg.exec()) {
		if (dlg.getUseRA()) {
			canvas.detectCurvesLinesWithRA(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getAngleThreshold() / 180.0 * CV_PI, dlg.getRAMaxError(), dlg.getRAClusterEpsilon(), dlg.getRAOptimization());
		}
		else {
			canvas.detectCurvesLines(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getAngleThreshold() / 180.0 * CV_PI);
		}
		canvas.update();
	}
}

void MainWindow::onGenerateContours() {
	ContourOptionDialog dlg;
	if (dlg.exec()) {
		if (dlg.getUseRA()) {
			canvas.generateContoursWithRA(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, dlg.getRAMaxError(), dlg.getRAClusterEpsilon(), dlg.getRAOptimization());
		}
		else {
			//check the sum weight equals 1
			float weight = 0.0f;
			if (dlg.getUseSymmetryLineOpt())
				weight += dlg.getSymmetryWeight();
			if (dlg.getUseRaOpt())
				weight += dlg.getRaWeight();
			if (dlg.getUseParallelOpt())
				weight += dlg.getParallelWeight();
			if (dlg.getUseAccuracyOpt())
				weight += dlg.getAccuracyWeight();
			if (abs(weight - 1.0f) < 0.0001)
			{
				std::cout << "Success!!" << std::endl;
			}
			else{
				std::cout << "Please check weight assignment!!!" << std::endl;
				return;
			}
			canvas.generateContours(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, dlg.getUseSymmetryLineOpt(), dlg.getIOUThreshold(), dlg.getSymmetryWeight(), dlg.getUseRaOpt(), dlg.getRaThreshold(), dlg.getRaWeight(), dlg.getUseParallelOpt(), dlg.getParallelThreshold(), dlg.getParallelWeight(), dlg.getUseAccuracyOpt(), dlg.getAccuracyWeight(), dlg.getUseOneLayer(), dlg.getUseLayers());
		}
		canvas.update();
	}
}

void MainWindow::onTestBatchFiles(){
	TestBatchFiles dlg;
	if (dlg.exec()) {
		//check the sum weight equals 1
		float weight = 0.0f;
		if (dlg.getUseSymmetryLineOpt())
			weight += dlg.getSymmetryWeight();
		if (dlg.getUseRaOpt())
			weight += dlg.getRaWeight();
		if (dlg.getUseParallelOpt())
			weight += dlg.getParallelWeight();
		if (dlg.getUseAccuracyOpt())
			weight += dlg.getAccuracyWeight();
		if (abs(weight - 1.0f) < 0.0001)
		{
			std::cout << "Success!!" << std::endl;
		}
		else{
			std::cout << "Please check weight assignment!!!" << std::endl;
			return;
		}
		return;
		// read files one by one
		QString input_dir = dlg.ui.lineEditInput->text();
		QString output_dir = dlg.ui.lineEditOutput->text();
		if (output_dir.isEmpty() || input_dir.isEmpty()){
			std::cout << "The path is empty!!" << std::endl;
			return;
		}
		QDir dir(input_dir);
		int index = 0;
		foreach(QFileInfo item, dir.entryInfoList())
		{
			if (item.isFile()){
				// input
				std::cout << "Input File: " << item.absoluteFilePath().toUtf8().constData() << std::endl;
				QString img_file = item.fileName();
				QString input_filename = item.absoluteFilePath();
				if (input_filename.isEmpty()) return;
				setWindowTitle("Efficient RANSAC 2D - " + input_filename);

				canvas.loadImage(input_filename);
				canvas.update();

				// detect symmetry lines
				/*if (dlg.getUseSymmetryLine()){
					canvas.detectSymmetryLine(dlg.getIOUThreshold());
				}*/

				// detect lines/curves and opt
				if (dlg.getUseRA()) {
					canvas.generateContoursWithRA(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, dlg.getRAMaxError(), dlg.getRAClusterEpsilon(), dlg.getRAOptimization());
				}
				else {
					canvas.generateContours(dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, dlg.getUseSymmetryLineOpt(), dlg.getIOUThreshold(), dlg.getSymmetryWeight(), dlg.getUseRaOpt(), dlg.getRaThreshold(), dlg.getRaWeight(), dlg.getUseParallelOpt(), dlg.getParallelThreshold(), dlg.getParallelWeight(), dlg.getUseAccuracyOpt(), dlg.getAccuracyWeight(), dlg.getUseOneLayer(), dlg.getUseLayers());
				}
				canvas.update();

				// output
				QString output_filename = output_dir + "/" + img_file;
				std::cout << "Output File: " << output_filename.toUtf8().constData() << std::endl;
				if (output_filename.isEmpty()) return;

				canvas.saveImage(output_filename);
				canvas.update();

			}
		}
	}
}

void MainWindow::onTestReflection(){
	// Given a point and one line, compute the mirror point
	cv::Point2f p = cv::Point2f(-3, 5);
	cv::Point2f a = cv::Point2f(0, 0);
	cv::Point2f b = cv::Point2f(1, 1);
	cv::Point2f result = util::mirrorPoint(a, b, p);
	std::cout << "mirror point is " << result << std::endl;
}

void MainWindow::onDetectSymmetryLine(){
	SymmetryLineOptionDialog dlg;
	if (dlg.exec()) {
		canvas.detectSymmetryLine(dlg.getIOUThreshold());
		canvas.update();
	}
}