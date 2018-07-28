#include "MainWindow.h"
#include <QFileDialog>
#include "CurveOptionDialog.h"
#include "LineOptionDialog.h"
#include "CurveLineOptionDialog.h"
#include "ContourOptionDialog.h"
#include "RightAngleOptionDialog.h"
#include "TestBatchFiles.h"
#include "SymmetryLineOptionDialog.h"
#include "LayersOptionDialog.h"
#include <QTextStream>
#include "../EfficientRANSAC2D_NoGUI/Regularizer.h"

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
	connect(ui.actionLayers, SIGNAL(triggered()), this, SLOT(onTestUseLayers()));
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

void MainWindow::onTestUseLayers(){
	LayersOptionDialog dlg;
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
		// read files one by one
		QString input_dir = dlg.ui.lineEditInput->text();
		QString output_dir = dlg.ui.lineEditOutput->text();
		if (output_dir.isEmpty() || input_dir.isEmpty()){
			std::cout << "The path is empty!!" << std::endl;
			return;
		}
		QDir dir(input_dir);
		int index = 0;
		int num_files = 0;
		QString file_path;
		foreach(QFileInfo item, dir.entryInfoList())
		{
			if (item.isFile()){
				num_files++;
			}
		}

		// read layer images
		std::vector<QString> fileNameList;
		fileNameList.resize(num_files - 2);
		for (int i = 0; i < num_files - 2; i++){
			QString filename = input_dir + "/" + QString::number(i) + ".png";
			fileNameList[i] = filename;
		}
		std::vector<std::pair<float, float>> height_info;
		height_info.resize(num_files - 2);
		// read height info
		QFile height_info_file = input_dir + "/info_height.txt";
		if (!height_info_file.open(QIODevice::ReadOnly)) {
			std::cout << "read height info file error" << std::endl;
			return;
		}
		QTextStream in(&height_info_file);
		for (int i = 0; i < num_files - 2; i++){
			QString line = in.readLine();
			QStringList fields = line.split(",");
			height_info[i] = std::make_pair(fields.at(0).toFloat(), fields.at(1).toFloat());
		}
		height_info_file.close();
		// read tree info
		std::vector<std::pair<int, int>> tree_info_tmp;
		QFile tree_info_file = input_dir + "/info_tree.txt";
		if (!tree_info_file.open(QIODevice::ReadOnly)) {
			std::cout << "read tree info file error" << std::endl;
			return;
		}
		QTextStream in_tree_info(&tree_info_file);
		while (!in_tree_info.atEnd()){
			QString line = in_tree_info.readLine();
			QStringList fields = line.split(",");
			std::cout << "mother is " << fields.at(0).toInt() << ", child is " << fields.at(1).toInt() << std::endl;
			tree_info_tmp.push_back(std::make_pair(fields.at(0).toInt(), fields.at(1).toInt()));
		}
		tree_info_file.close();
		std::vector<std::pair<std::vector<int>, std::vector<int>>> tree_info;
		tree_info.resize(num_files - 2);
		for (int node = 0; node < num_files - 2; node++){
			for (int i = 0; i < tree_info_tmp.size(); i++){
				if (tree_info_tmp[i].first == node){
					tree_info[node].second.push_back(tree_info_tmp[i].second);
				}
				if (tree_info_tmp[i].second == node){
					tree_info[node].first.push_back(tree_info_tmp[i].first);
				}
			}
		}
		for (int node = 0; node < num_files - 2; node++){
			std::cout << "node " << node << "'s mother nodes are as follows:" << std::endl;
			for (int j = 0; j < tree_info[node].first.size(); j++){
				std::cout << tree_info[node].first[j] << ",";
			}
			std::cout << std::endl;
			std::cout << "node " << node << "'s children nodes are as follows:" << std::endl;
			for (int j = 0; j < tree_info[node].second.size(); j++){
				std::cout << tree_info[node].second[j] << ",";
			}
			std::cout << std::endl;
		}
		// test layer
		{
			//Regularizer reg;
			//reg.regularizerForLayers(fileNameList, height_info, dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, dlg.getUseSymmetryLineOpt(), dlg.getIOUThreshold(), dlg.getSymmetryWeight(), dlg.getUseRaOpt(), dlg.getRaThreshold(), dlg.getRaWeight(), dlg.getUseParallelOpt(), dlg.getParallelThreshold(), dlg.getParallelWeight(), dlg.getUseAccuracyOpt(), dlg.getAccuracyWeight());
		}
		// test layers
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