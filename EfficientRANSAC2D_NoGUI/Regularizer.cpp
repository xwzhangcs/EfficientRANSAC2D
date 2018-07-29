#include "Regularizer.h"
#include <QTextStream>
#include "../EfficientRANSAC2D_NoGUI/ShapeFit.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFitLayer.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFitLayers.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/document.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/writer.h"
#include "../EfficientRANSAC2D_NoGUI/rapidjson/stringbuffer.h"

Regularizer::Regularizer(){

}

void Regularizer::regularizerForLayer(QString fileName, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, QString config_file){
	Layer input;
	QFile file(config_file);
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "File was not readable: " << std::endl;
		return;
	}
	QTextStream in(&file);
	rapidjson::Document doc;
	doc.Parse(in.readAll().toUtf8().constData());
	bool bUseIntra = false;
	bool bUseSymmetryLineOpt = false;
	float iouThreahold = 0.0f;
	bUseIntra = doc["UseIntra"].GetBool();
	std::cout << "bUseIntra is " << bUseIntra << std::endl;
	if (bUseIntra){
		rapidjson::Value& algs = doc["IntraOpt"];
		rapidjson::Value& algs_subs = algs["Symmetry"];
		bUseSymmetryLineOpt = algs_subs["UseOpt"].GetBool();
		iouThreahold = algs_subs["IouThreshold"].GetFloat();
		file.close();
	}
	else{
		file.close();
		return;
	}
	createLayer(fileName, input, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
	generateContoursLayer(input, config_file);
	saveImage(input, 0);
}

void Regularizer::regularizerForLayers(const std::vector<QString> &fileNameList, const std::vector<std::pair<float, float>>& height_infoint, const std::vector<std::pair<std::vector<int>, std::vector<int>>>& tree_info, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, QString config_file){
	std::vector<Layer> input_layers;
	QFile file(config_file);
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "File was not readable: " << std::endl;
		return;
	}
	QTextStream in(&file);
	rapidjson::Document doc;
	doc.Parse(in.readAll().toUtf8().constData());
	bool bUseIntra = false;
	bool bUseSymmetryLineOpt = false;
	float iouThreahold = 0.0f;
	bUseIntra = doc["UseIntra"].GetBool();
	std::cout << "bUseIntra is " << bUseIntra << std::endl;
	if (bUseIntra){
		rapidjson::Value& algs = doc["IntraOpt"];
		rapidjson::Value& algs_subs = algs["Symmetry"];
		bUseSymmetryLineOpt = algs_subs["UseOpt"].GetBool();
		iouThreahold = algs_subs["IouThreshold"].GetFloat();
		file.close();
	}
	else{
		file.close();
		return;
	}
	createLayers(fileNameList, height_infoint, tree_info, input_layers, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
	generateContoursLayers(input_layers, config_file);
	for (int i = 0; i < input_layers.size(); i++){
		saveImage(input_layers[i], i);
		//std::cout << "layer " << i << " top height is " << input_layers[i].top_height << " bot height is " << input_layers[i].bottom_height << std::endl;
	}
}

void Regularizer::createLayer(QString fileName, Layer & layer, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold){
	layer.generateLayer(fileName, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
}

void Regularizer::createLayers(const std::vector<QString> &fileNameList, const std::vector<std::pair<float, float>>& height_info, const std::vector<std::pair<std::vector<int>, std::vector<int>>>& tree_info, std::vector<Layer>& layers, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold){
	int num_layers = fileNameList.size();
	layers.resize(num_layers);
	for (int i = 0; i < num_layers; i++){
		createLayer(fileNameList[i], layers[i], curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
		layers[i].top_height = height_info[i].first;
		layers[i].bottom_height = height_info[i].second;
		layers[i].parents = tree_info[i].first;
		layers[i].children = tree_info[i].second;
	}
}


void Regularizer::generateContoursLayer(Layer& input_layer, QString config_file){

	// if all contours sizes are 0
	bool bValidLayer = false;
	for (int i = 0; i < input_layer.contours_pre.size(); i++){
		if (input_layer.contours_pre[i].size() != 0){
			bValidLayer = true;
			break;
		}
	}
	if (!bValidLayer){
		std::cout << "no need to use optimization" << std::endl;
		return;
	}
	bool bUseRaOpt = false;
	bool bUseParallelOpt = false;
	bool bUseSymmetryLineOpt = false;
	bool bUseAccuracyOpt = false;
	float raThreahold = 0.0f;
	float raWeight = 0.0f;
	float parallelThreahold = 0.0f;
	float parallelWeight = 0.0f;
	float symmetryWeight = 0.0f;
	float accuracyWeight = 0.0f;
	QFile file(config_file);
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "File was not readable: " << std::endl;
		return;
	}
	QTextStream in(&file);
	rapidjson::Document doc;
	doc.Parse(in.readAll().toUtf8().constData());
	bool bUseIntra = doc["UseIntra"].GetBool();
	if (bUseIntra){
		rapidjson::Value& algs = doc["IntraOpt"];
		//ra
		rapidjson::Value& algs_ra = algs["RA"];
		bUseRaOpt = algs_ra["UseOpt"].GetBool();
		raThreahold = algs_ra["AngleThreshold"].GetFloat();
		raWeight = algs_ra["Weight"].GetFloat();
		//symmetry
		rapidjson::Value& algs_symmetry = algs["Symmetry"];
		bUseSymmetryLineOpt = algs_symmetry["UseOpt"].GetBool();
		symmetryWeight = algs_symmetry["Weight"].GetFloat();
		// parallel
		rapidjson::Value& algs_parallel = algs["Parallel"];
		bUseParallelOpt = algs_parallel["UseOpt"].GetBool();
		parallelThreahold = algs_parallel["AngleThreshold"].GetFloat();
		parallelWeight = algs_parallel["Weight"].GetFloat();
		// accuracy
		rapidjson::Value& algs_accuracy = algs["Accuracy"];
		bUseAccuracyOpt = algs_accuracy["UseOpt"].GetBool();
		accuracyWeight = algs_accuracy["Weight"].GetFloat();
		//{
		//	std::cout << "bUseRa " << bUseRaOpt << " ra angle is " << raThreahold << " ra weight is " << raWeight << std::endl;
		//	std::cout << "bUseParallel " << bUseParallelOpt << " Parallel angle is " << parallelThreahold << " Parallel weight is " << parallelWeight << std::endl;
		//	std::cout << "bUseSymmetry " << bUseSymmetryLineOpt << " Symmetry weight is " << symmetryWeight << std::endl;
		//	std::cout << "bUseAccuracy " << bUseAccuracyOpt << " Accuracy weight is " << accuracyWeight << std::endl;
		//}
		file.close();
	}
	else{
		file.close();
		return;
	}
	// Here we have all original polygons, all initial points and all symmetry lines
	// We call optimization below
	input_layer.contours = ShapeFitLayer::fit(input_layer.sparse_contours, input_layer.contours_pre, bUseRaOpt, raThreahold, raWeight, bUseParallelOpt, parallelThreahold, parallelWeight, bUseSymmetryLineOpt, input_layer.symmetry_lines, symmetryWeight, bUseAccuracyOpt, accuracyWeight);
	for (int i = 0; i < input_layer.contours.size(); i++){
		////////// DEBUG //////////
		// calculate IOU
		if (input_layer.contours[i].size() != 0){
			std::cout << "Polygon " << i << std::endl;
			std::cout << "contour size is " << input_layer.contours[i].size() << std::endl;
			if (util::isSimple(input_layer.polygons[i].contour) && util::isSimple(input_layer.contours[i]))
				std::cout << "IOU = " << util::calculateIOU(input_layer.polygons[i].contour, input_layer.contours[i]) << std::endl;
			else
				std::cout << "IOU = " << util::calculateIOUbyImage(input_layer.polygons[i].contour, input_layer.contours[i], 1000) << std::endl;
			std::cout << "#vertices = " << input_layer.contours[i].size() << std::endl;
			std::cout << "-----------------------" << std::endl;
		}
	}
}

void Regularizer::generateContoursLayers(std::vector<Layer>& input_layers, QString config_file){
	// if all contours sizes are 0
	bool bValidLayer = false;
	for (int i = 0; i < input_layers.size(); i++){
		for (int j = 0; j < input_layers[i].contours_pre.size(); j++){
			if (input_layers[i].contours_pre[j].size() != 0){
				bValidLayer = true;
				break;
			}
		}
		if (bValidLayer)
			break;
	}
	if (!bValidLayer)
		return;
	// Here we have all original polygons, all initial points and all symmetry lines
	// We call optimization below
	ShapeFitLayers::fit(input_layers, config_file);
	for (int i = 0; i < input_layers.size(); i++){
		for (int j = 0; j < input_layers[i].contours.size(); j++){
			////////// DEBUG //////////
			// calculate IOU
			if (input_layers[i].contours[j].size() != 0){
				std::cout << "Layer " << i <<" Polygon " << j << std::endl;
				std::cout << "contour size is " << input_layers[i].contours[j].size() << std::endl;
				if (util::isSimple(input_layers[i].polygons[j].contour) && util::isSimple(input_layers[i].contours[j]))
					std::cout << "IOU = " << util::calculateIOU(input_layers[i].polygons[j].contour, input_layers[i].contours[j]) << std::endl;
				else
					std::cout << "IOU = " << util::calculateIOUbyImage(input_layers[i].polygons[j].contour, input_layers[i].contours[j], 1000) << std::endl;
				std::cout << "#vertices = " << input_layers[i].contours[j].size() << std::endl;
				std::cout << "-----------------------" << std::endl;
			}
		}
	}
}

void Regularizer::saveImage(Layer & layer, int index){
	QImage src = layer.orig_image;
	QImage image(QSize(src.width(), src.height()), QImage::Format_RGB32);
	QPixmap pixmap;
	QPainter painter(&image);
	painter.setBrush(QBrush(Qt::white));
	painter.fillRect(QRectF(0, 0, src.width(), src.height()), Qt::white);
	painter.setPen(QPen(QColor(0, 0, 0), 1));
	for (auto& polygon : layer.polygons) {
		QPolygon pgon;
		for (auto& p : polygon.contour) {
			pgon.push_back(QPoint(p.x, p.y));
		}
		painter.drawPolygon(pgon);
		for (auto& hole : polygon.holes) {
			QPolygon pgon;
			for (auto& p : hole) {
				pgon.push_back(QPoint(p.x, p.y));
			}
			painter.drawPolygon(pgon);
		}
	}
	painter.setPen(QPen(QColor(0, 0, 255), 3));
	for (auto& contour : layer.contours) {
		//painter.setPen(QPen(QColor(0, 0, 255), 3));
		QPolygon pol;
		for (int i = 0; i < contour.size(); i++) {
			pol.push_back(QPoint(contour[i].x , contour[i].y));
		}
		painter.drawPolygon(pol);
	}
	painter.end();
	image.save("../test/output_" + QString::number(index) + ".png");
}
