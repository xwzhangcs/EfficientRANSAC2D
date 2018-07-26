#include "Regularizer.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFit.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFitLayer.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFitLayers.h"

Regularizer::Regularizer(){

}

void Regularizer::regularizerForLayer(QString fileName, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight){
	Layer input;
	createLayer(fileName, input, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
	generateContoursLayer(input, bUseSymmetryLineOpt, symmetryWeight, bUseRaOpt, raThreahold, raWeight, bUseParallelOpt, papallelThreahold, parallelWeight, bUseAccuracyOpt, accuracyWeight);
	saveImage(input, 0);
}

void Regularizer::regularizerForLayers(std::vector<QString> fileNameList, std::vector<std::pair<float, float>> height_infoint, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight){
	std::vector<Layer> input_layers;
	createLayers(fileNameList, height_infoint, input_layers, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
	generateContoursLayers(input_layers, bUseSymmetryLineOpt, symmetryWeight, bUseRaOpt, raThreahold, raWeight, bUseParallelOpt, papallelThreahold, parallelWeight, bUseAccuracyOpt, accuracyWeight);
	//for (int i = 0; i < input_layers.size(); i++){
	//	saveImage(input_layers[i], i);
	//	std::cout << "layer " << i << " top height is " << input_layers[i].top_height << " bot height is " << input_layers[i].bottom_height << std::endl;
	//}
}

void Regularizer::createLayer(QString fileName, Layer & layer, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold){
	layer.generateLayer(fileName, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
}

void Regularizer::createLayers(std::vector<QString> fileNameList, std::vector<std::pair<float, float>> height_info, std::vector<Layer>& layers, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold){
	int num_layers = fileNameList.size();
	layers.resize(num_layers);
	for (int i = 0; i < num_layers; i++){
		createLayer(fileNameList[i], layers[i], curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, contour_max_error, contour_angle_threshold, bUseSymmetryLineOpt, iouThreahold);
		layers[i].top_height = height_info[i].first;
		layers[i].bottom_height = height_info[i].second;
	}
}


void Regularizer::generateContoursLayer(Layer& input_layer, bool bUseSymmetryLineOpt, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight){

	// if all contours sizes are 0
	bool bValidLayer = false;
	for (int i = 0; i < input_layer.contours_pre.size(); i++){
		if (input_layer.contours_pre[i].size() != 0){
			bValidLayer = true;
			break;
		}
	}
	if (!bValidLayer)
		return;
	// Here we have all original polygons, all initial points and all symmetry lines
	// We call optimization below
	input_layer.contours = ShapeFitLayer::fit(input_layer.sparse_contours, input_layer.contours_pre, bUseRaOpt, raThreahold, raWeight, bUseParallelOpt, papallelThreahold, parallelWeight, bUseSymmetryLineOpt, input_layer.symmetry_lines, symmetryWeight, bUseAccuracyOpt, accuracyWeight);
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

void Regularizer::generateContoursLayers(std::vector<Layer>& input_layers, bool bUseSymmetryLineOpt, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight){
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
	ShapeFitLayers::fit(input_layers, bUseRaOpt, raThreahold, raWeight, bUseParallelOpt, papallelThreahold, parallelWeight, bUseSymmetryLineOpt, symmetryWeight, bUseAccuracyOpt, accuracyWeight);
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
