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
#include "MultiRunsDialog.h"
#include <QTextStream>
#include "../EfficientRANSAC2D_NoGUI/Regularizer.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/document.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/writer.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/stringbuffer.h"

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
	connect(ui.actionCombineImages, SIGNAL(triggered()), this, SLOT(onCombineImages()));
	connect(ui.actionMulti_Runs, SIGNAL(triggered()), this, SLOT(onMultipleRuns()));
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

QString readStringValue(const rapidjson::Value& node, const char* key) {
	if (node.HasMember(key) && node[key].IsString()) {
		return QString(node[key].GetString());
	}
	else {
		throw "Could not read string from node";
	}
}

void MainWindow::onTestUseLayers(){
	LayersOptionDialog dlg;
	if (dlg.exec()) {
		// first check the sum of interWeight and intraWeight
		float weight = 0.0f;
		/*if (dlg.getUseIntraOpt())
			weight += dlg.getIntraWeight();
		if (dlg.getUseInterOpt())
			weight += dlg.getInterWeight();
		if (abs(weight - 1.0f) < 0.0001)
		{
			std::cout << "Success in Intra and Inter!!" << std::endl;
		}
		else{
			std::cout << "Please check weights for Intra and Inter!!!" << std::endl;
			return;
		}*/

		// second check the sum of sub terms in InterWeight
		weight = 0.0f;
		if (dlg.getUseIntraOpt()){
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
				std::cout << "Success in intra weight assignment!!" << std::endl;
			}
			else{
				std::cout << "Please check intra weight assignment!!!" << std::endl;
				return;
			}
		}
		// third check the sum of sub terms in IntraWeight
		weight = 0.0f;
		if (dlg.getUseInterOpt()){
			if (dlg.getUsePointSnapOpt())
				weight += dlg.getPointWeight();
			if (dlg.getUseSegSnapOpt())
				weight += dlg.getSegWeight();
			if (abs(weight - 1.0f) < 0.0001)
			{
				std::cout << "Success in inter weight assignment!!" << std::endl;
			}
			else{
				std::cout << "Please check inter weight assignment!!!" << std::endl;
			}

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
			//std::cout << "mother is " << fields.at(0).toInt() << ", child is " << fields.at(1).toInt() << std::endl;
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

		// generate the config file
		rapidjson::Document document;
		document.SetObject();
		// must pass an allocator when the object may need to allocate memory
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
		
		// add member UseIntra
		document.AddMember("UseIntra", dlg.getUseIntraOpt(), allocator);
		document.AddMember("UseInter", dlg.getUseInterOpt(), allocator);

		// add Intra sub terms
		if (dlg.getUseIntraOpt()){
			// create a rapidjson object type
			rapidjson::Value object(rapidjson::kObjectType);

			rapidjson::Value objectRa(rapidjson::kObjectType);
			// RA term
			objectRa.AddMember("UseOpt", dlg.getUseRaOpt(), allocator);
			objectRa.AddMember("AngleThreshold", dlg.getRaThreshold(), allocator);
			objectRa.AddMember("Weight", dlg.getRaWeight(), allocator);
			object.AddMember("RA", objectRa, allocator);
			// Parallel term
			rapidjson::Value objectParallel(rapidjson::kObjectType);
			objectParallel.AddMember("UseOpt", dlg.getUseParallelOpt(), allocator);
			objectParallel.AddMember("AngleThreshold", dlg.getParallelThreshold(), allocator);
			objectParallel.AddMember("Weight", dlg.getParallelWeight(), allocator);
			object.AddMember("Parallel", objectParallel, allocator);
			// Symmetry term
			rapidjson::Value objectSymmetry(rapidjson::kObjectType);
			objectSymmetry.AddMember("UseOpt", dlg.getUseSymmetryLineOpt(), allocator);
			objectSymmetry.AddMember("IouThreshold", dlg.getIOUThreshold(), allocator);
			objectSymmetry.AddMember("Weight", dlg.getSymmetryWeight(), allocator);
			object.AddMember("Symmetry", objectSymmetry, allocator);
			// Accuracy term
			rapidjson::Value objectAccuracy(rapidjson::kObjectType);
			objectAccuracy.AddMember("UseOpt", dlg.getUseAccuracyOpt(), allocator);
			objectAccuracy.AddMember("Weight", dlg.getAccuracyWeight(), allocator);
			object.AddMember("Accuracy", objectAccuracy, allocator);

			document.AddMember("IntraOpt", object, allocator);
		}

		// add Inter sub terms
		if (dlg.getUseInterOpt()){
			// create a rapidjson object type
			rapidjson::Value object(rapidjson::kObjectType);
			// Point term
			rapidjson::Value objectPoint(rapidjson::kObjectType);
			objectPoint.AddMember("UseOpt", dlg.getUsePointSnapOpt(), allocator);
			objectPoint.AddMember("DisThreshold", dlg.getPointDisThreshold(), allocator);
			objectPoint.AddMember("Weight", dlg.getPointWeight(), allocator);
			object.AddMember("PointSnap", objectPoint, allocator);
			// Seg term
			rapidjson::Value objectSeg(rapidjson::kObjectType);
			objectSeg.AddMember("UseOpt", dlg.getUseSegSnapOpt(), allocator);
			objectSeg.AddMember("DisThreshold", dlg.getSegDisThreshold(), allocator);
			objectSeg.AddMember("AngleThreshold", dlg.getSegAngleThreshold(), allocator);
			objectSeg.AddMember("Weight", dlg.getSegWeight(), allocator);
			object.AddMember("SegSnap", objectSeg, allocator);
			document.AddMember("InterOpt", object, allocator);
		}

		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		document.Accept(writer);

		std::cout << strbuf.GetString() << std::endl;

		QString filename_new = "../test/config_solo.json"; 
		{
			QFile file(filename_new);
			file.remove();
		}
		QFile file_new(filename_new);
		if (file_new.open(QIODevice::ReadWrite))
		{
			QTextStream stream(&file_new);
			stream << strbuf.GetString();
		}
		file_new.close();
		// read json file
		/*{
			QFile file("../test/config.json");
			if (!file.open(QIODevice::ReadOnly)) {
				std::cerr << "File was not readable: " << std::endl;
				return ;
			}
			QTextStream in(&file);
			rapidjson::Document doc;
			doc.Parse(in.readAll().toUtf8().constData());
			bool test = readBoolValue(doc, "t", false);
			std::cout << "test is " << test << std::endl;
			float test_f = 0.0f;
			if (doc.HasMember("pi")) {
				test_f =  doc["pi"].GetFloat();
				std::cout << "test_f is " << test_f << std::endl;
			}
		}*/
		// test layer
		{
			Regularizer reg;
			//reg.regularizerForLayers(fileNameList, height_info, tree_info, dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, "../test/config_solo.json");
			reg.regularizerForLayer("../test/038/1.png", dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, "../test/config_solo.json");
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

void MainWindow::onCombineImages(){
	QImage overlay;
	overlay.load("../test/run_1_contours_1.png");
	QPixmap base;
	base.load("../test/run_1_contours_0.png");
	QPainter painter;
	painter.begin(&base);

	for (int i = 0; i < base.width(); i++){
		for (int j = 0; j < base.height(); j++){
			QColor clrCurrent(overlay.pixel(i, j));
			if (clrCurrent.red() == 0 && clrCurrent.green() != 0 && clrCurrent.blue() != 0){
			//if (clrCurrent.red() == 255 && clrCurrent.green() == 0 && clrCurrent.blue() == 0){
				painter.setPen(clrCurrent);
				painter.drawPoint(i, j);
			}
			else{

			}
		}
	}
	painter.end();
	base.save("../test/result.png");
}

void MainWindow::onMultipleRuns(){
	MultiRunsDialog dlg;
	if (dlg.exec()) {
		// read files one by one
		QString input_dir_all = dlg.ui.lineEditInput->text();
		QString output_dir_all = dlg.ui.lineEditOutput->text();
		if (output_dir_all.isEmpty() || input_dir_all.isEmpty()){
			std::cout << "The path is empty!!" << std::endl;
			return;
		}
		QDir dir_all(input_dir_all);
		foreach(QFileInfo item, dir_all.entryInfoList())
		{
			if (item.isDir()){
				// sub dir input
				//std::cout << "Input dir File: " << item.absoluteFilePath().toUtf8().constData() << std::endl;
				if (item.fileName() == "." || item.fileName() == "..") continue;
				QString input_dir = input_dir_all + "/" + item.fileName();
				QDir dir(input_dir);
				std::cout << "Input sub dir File: " << input_dir.toUtf8().constData() << std::endl;
				int index = 0;
				int num_files = 0;
				QString file_path;
				foreach(QFileInfo item, dir.entryInfoList())
				{
					if (item.isFile()){
						num_files++;
					}
				}
				int num_others = 2;
				if (num_files - 2 > 0)
					num_others = 2;// height_info and tree_info
				else
					num_others = 1;// only height_info
				if (num_files - num_others >= 4)
					continue;
				QString output_dir = output_dir_all + "/" + item.fileName();
				if (!QDir(output_dir).exists()){
					QDir().mkdir(output_dir);
				}
				// read layer images
				std::vector<QString> fileNameList;
				fileNameList.resize(num_files - num_others);
				for (int i = 0; i < num_files - num_others; i++){
					QString filename = input_dir + "/" + QString::number(i) + ".png";
					fileNameList[i] = filename;
				}
				std::vector<std::pair<float, float>> height_info;
				height_info.resize(num_files - num_others);
				// read height info
				QFile height_info_file = input_dir + "/info_height.txt";
				if (!height_info_file.open(QIODevice::ReadOnly)) {
					std::cout << "read height info file error" << std::endl;
					return;
				}
				QTextStream in(&height_info_file);
				for (int i = 0; i < num_files - num_others; i++){
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
					//std::cout << "mother is " << fields.at(0).toInt() << ", child is " << fields.at(1).toInt() << std::endl;
					tree_info_tmp.push_back(std::make_pair(fields.at(0).toInt(), fields.at(1).toInt()));
				}
				tree_info_file.close();
				std::vector<std::pair<std::vector<int>, std::vector<int>>> tree_info;
				tree_info.resize(num_files - num_others);
				for (int node = 0; node < num_files - num_others; node++){
					for (int i = 0; i < tree_info_tmp.size(); i++){
						if (tree_info_tmp[i].first == node){
							tree_info[node].second.push_back(tree_info_tmp[i].second);
						}
						if (tree_info_tmp[i].second == node){
							tree_info[node].first.push_back(tree_info_tmp[i].first);
						}
					}
				}

				// call regularizer
				Regularizer reg;
				//reg.regularizerForLayers(fileNameList, height_info, tree_info, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle / 180.0 * CV_PI, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, "../test/config.json");
				//reg.regularizerForLayer("../test/1.png", dlg.getCurveNumIterations(), dlg.getCurveMinPoints(), dlg.getCurveMaxErrorRatioToRadius(), dlg.getCurveClusterEpsilon(), dlg.getCurveMinAngle() / 180.0 * CV_PI, dlg.getCurveMinRadius(), dlg.getCurveMaxRadius(), dlg.getLineNumIterations(), dlg.getLineMinPoints(), dlg.getLineMaxError(), dlg.getLineClusterEpsilon(), dlg.getLineMinLength(), dlg.getLineAngleThreshold() / 180.0 * CV_PI, dlg.getContourMaxError(), dlg.getContourAngleThreshold() / 180.0 * CV_PI, "../test/config.json");
				//reg.regularizerMultiRunsForLayers(fileNameList, height_info, tree_info, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle / 180.0 * CV_PI, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold / 180.0 * CV_PI, contour_max_error, contour_angle_threshold / 180.0 * CV_PI, dlg.ui.lineEditInputConfig->text());
				//reg.regularizerMultiRunsForLayers(fileNameList, height_info, tree_info, dlg.ui.lineEditInputDetect->text(), dlg.ui.lineEditInputConfig->text());
				reg.regularizerAll(output_dir, fileNameList, height_info, tree_info, dlg.ui.lineEditInputDetect->text(), dlg.ui.lineEditInputConfig->text());
			}

		}
	}

}

void MainWindow::onDetectSymmetryLine(){
	SymmetryLineOptionDialog dlg;
	if (dlg.exec()) {
		canvas.detectSymmetryLine(dlg.getIOUThreshold());
		canvas.update();
	}
}