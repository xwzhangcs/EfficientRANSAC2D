#include "Canvas.h"
#include <QPainter>
#include <iostream>
#include <QFileInfoList>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QResizeEvent>
#include "../EfficientRANSAC2D_NoGUI/RightAngleSimplification.h"
#include "../EfficientRANSAC2D_NoGUI/ShapeFit.h"
#include "../EfficientRANSAC2D_NoGUI/SymmetryLineDetector.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
	ctrlPressed = false;
	shiftPressed = false;
}

void Canvas::loadImage(const QString& filename) {
	orig_image = QImage(filename).convertToFormat(QImage::Format_Grayscale8);
	std::cout << "width() is " << width() << std::endl;
	std::cout << "height() is " << height() << std::endl;
	std::cout << "orig_image.width() is " << orig_image.width() << std::endl;
	std::cout << "orig_image.height() is " << orig_image.height() << std::endl;

	image_scale = std::min((float)width() / orig_image.width(), (float)height() / orig_image.height());
	image = orig_image.scaled(orig_image.width() * image_scale, orig_image.height() * image_scale);
	polygons.clear();
	shapes.clear();
	contours.clear();
	symmetry_lines.clear();
	symmetry_polygons.clear();
	symmetry_lines_signal.clear();
	update();
}

void Canvas::saveImage(const QString& filename) {
	grab().save(filename);
}

void Canvas::detectContours() {
	polygons.clear();
	shapes.clear();
	contours.clear();
	symmetry_lines.clear();
	symmetry_polygons.clear();
	symmetry_lines_signal.clear();

	if (orig_image.isNull()) return;

	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	polygons = util::findContours(mat, 40, false, true, false);
}

void Canvas::detectCurves(int num_iterations, int min_points, float max_error_ratio_to_radius, float cluster_epsilon, float min_angle, float min_radius, float max_radius) {
	detectContours();

	// detect circles
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			shapes[i] = er.detectCircles(polygons[i].contour, num_iterations, min_points, max_error_ratio_to_radius, cluster_epsilon, min_angle, min_radius, max_radius);
		}
	}
}

void Canvas::detectLines(int num_iterations, int min_points, float max_error, float cluster_epsilon, float min_length, float angle_threshold) {
	detectContours();

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	// use the principal orientation, +45, +90, +135 degrees as principal orientations
	std::vector<float> principal_orientations;
	for (int i = 0; i < 4; i++) {
		principal_orientations.push_back(principal_orientation + CV_PI * i / 4);
	}

	// detect lines based on the principal orientations
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			shapes[i] = er.detectLines(polygons[i].contour, num_iterations, min_points, max_error, cluster_epsilon, min_length, angle_threshold, principal_orientations, {});
		}
	}
}

void Canvas::detectSymmetryLine(float iouThreahold){
	detectContours();
	std::cout << "iouThreahold is " << iouThreahold << std::endl;
	// find sparse contours
	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	std::vector<util::Polygon> sparse_polygons = util::findContours(mat, 40, true, false, true);
	symmetry_lines.resize(sparse_polygons.size());
	symmetry_polygons.resize(sparse_polygons.size());
	symmetry_lines_signal.resize(sparse_polygons.size());

	for (int i = 0; i < sparse_polygons.size(); i++){
		if (sparse_polygons[i].contour.size() >= 100){
			std::vector<cv::Point2f> sparse_contour = util::simplifyContour(sparse_polygons[i].contour, 2);
			if (sparse_contour.size() < 10) continue;
			symmetry_lines[i] = SymmetryLineDetector::fitSymmetryLine(sparse_contour);
			for (int j = 0; j < sparse_contour.size(); j++) {
				symmetry_polygons[i].push_back(util::mirrorPoint(symmetry_lines[i][0], symmetry_lines[i][1], sparse_contour[j]));
			}	
			// calculate IOU
			if (util::isSimple(sparse_contour) && util::isSimple(symmetry_polygons[i])){
				if (util::calculateIOU(sparse_contour, symmetry_polygons[i]) >= iouThreahold * 0.01){
					symmetry_lines_signal[i] = true;
					std::cout << i << " is here" << std::endl;
				}
				else{
					symmetry_lines_signal[i] = false;
				}
			}
			else{
				if (util::calculateIOUbyImage(sparse_contour, symmetry_polygons[i], 1000) >= iouThreahold * 0.01){
					symmetry_lines_signal[i] = true;
					std::cout << i << " is here" << std::endl;
				}
				else{
					symmetry_lines_signal[i] = false;
				}
			}
			// calculate distance
			/*float distance = util::calculatePoLIS(sparse_contour, symmetry_polygons[i]);
			std::cout << "final distance is " << distance << std::endl;
			if (distance <= 5){
				symmetry_lines_signal[i] = true;
			}
			else{
				symmetry_lines_signal[i] = false;
			}*/
		}
	}

}

void Canvas::rightAngle(int resolution, bool optimization) {
	detectContours();

	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	std::vector<util::Polygon> sparse_polygons = util::findContours(mat, 40, true, false, true);

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	shapes.resize(sparse_polygons.size());
	for (int i = 0; i < sparse_polygons.size(); i++) {
		if (sparse_polygons[i].contour.size() >= 4 && util::area(sparse_polygons[i].contour) > 100) {
			try {
				util::Polygon res = RightAngleSimplification::simplify(sparse_polygons[i], resolution, principal_orientation, 0.02, optimization);
				for (int j = 0; j < res.contour.size(); j++) {
					int j2 = (j + 1) % res.contour.size();

					efficient_ransac::Line* line = new efficient_ransac::Line(j, (res.contour[j] + res.contour[j2]) * 0.5, res.contour[j2] - res.contour[j]);
					line->setSupportingPoints({ res.contour[j], res.contour[j2] }, { j, j2 });
					shapes[i].push_back({ j, std::shared_ptr<efficient_ransac::PrimitiveShape>(line) });
				}

				////////// DEBUG //////////
				// calculate IOU
				std::cout << "IOU = " << util::calculateIOU(sparse_polygons[i].contour, res.contour) << std::endl;
				std::cout << "#vertices = " << contours[i].size() << std::endl;
			}
			catch (...) {}
		}
	}
}

void Canvas::detectCurvesLines(int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold) {
	detectContours();

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	// use the principal orientation, +45, +90, +135 degrees as principal orientations
	std::vector<float> principal_orientations;
	for (int i = 0; i < 4; i++) {
		principal_orientations.push_back(principal_orientation + CV_PI * i / 4);
	}

	// detect circles and lines
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			shapes[i] = er.detect(polygons[i].contour, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, principal_orientations);
		}
	}
}

void Canvas::detectCurvesLinesWithRA(int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float ra_max_error, float ra_cluster_epsilon, bool ra_optimization) {
	detectContours();

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	// use the principal orientation, +45, +90, +135 degrees as principal orientations
	std::vector<float> principal_orientations;
	for (int i = 0; i < 4; i++) {
		principal_orientations.push_back(principal_orientation + CV_PI * i / 4);
	}

	// find sparse contours
	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	std::vector<util::Polygon> sparse_polygons = util::findContours(mat, 40, true, false, true);

	// detect circles and lines
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			util::Polygon ra_polygon;
			try {
				// detect right angle edges
				ra_polygon = RightAngleSimplification::simplify(sparse_polygons[i], ra_max_error, principal_orientation, 0.02, ra_optimization);
			}
			catch (...) {}

			shapes[i] = er.detectWithRA(polygons[i].contour, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, principal_orientations, ra_polygon.contour, ra_max_error, ra_cluster_epsilon);
		}
	}
}

void Canvas::generateContours(int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLine, float iouThreahold, bool bUseRaOpt, float raThreahold, bool bUseParallelOpt, float papallelThreahold) {
	detectContours();

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	// use the principal orientation, +45, +90, +135 degrees as principal orientations
	std::vector<float> principal_orientations;
	for (int i = 0; i < 4; i++) {
		principal_orientations.push_back(principal_orientation + CV_PI * i / 4);
	}

	// detect circles and lines
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			shapes[i] = er.detect(polygons[i].contour, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, principal_orientations);
		}
	}

	// generate contours
	std::vector<std::vector<cv::Point2f>> contours_pre;
	contours.resize(shapes.size());
	contours_pre.resize(shapes.size());
	symmetry_lines.resize(shapes.size());
	symmetry_lines_signal.resize(shapes.size());
	for (int i = 0; i < shapes.size(); i++)
		symmetry_lines_signal[i] = false;
	// find sparse contours
	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	std::vector<util::Polygon> sparse_polygons = util::findContours(mat, 40, true, false, true);
	sparse_polygons_test = util::findContours(mat, 40, true, false, true);
	std::cout << "sparse_polygons.size() is " << sparse_polygons.size() << std::endl;
	std::cout << "polygons.size() is " << polygons.size() << std::endl;
	for (int i = 0; i < shapes.size(); i++) {
		//std::cout << "shape size is " << shapes[i].size() << std::endl;
		if (shapes[i].size() == 0)
			continue;
		std::sort(shapes[i].begin(), shapes[i].end());
		//ContourGenerator::generate(polygons[i], shapes[i], contours[i], contour_max_error, contour_angle_threshold);
		ContourGenerator::generate(polygons[i], shapes[i], contours_pre[i], contour_max_error, contour_angle_threshold);
		if (contours_pre[i].size() == 0)
			continue;

		// shapefit
		std::vector<cv::Point2f> sparse_contour;
		if (polygons.size() == sparse_polygons.size())
			sparse_contour = util::simplifyContour(sparse_polygons[i].contour, 2);
		else{
			// find corresponding polygon
			float min_x = std::numeric_limits<float>::max();
			int index = 0;
			for (int j = 0; j < sparse_polygons.size(); j++)
			{
				float distance = util::calculatePoLIS(sparse_polygons[j].contour, polygons[i].contour);
				if (distance < min_x){
					min_x = distance;
					index = j;
				}
			}
			std::cout << i << " is corresponding to "<<index << std::endl;
			sparse_contour = util::simplifyContour(sparse_polygons[index].contour, 2);
		}

		// symmetry line
		bool bvalid_symmetry_line = false;
		if (bUseSymmetryLine){
			symmetry_lines[i] = SymmetryLineDetector::fitSymmetryLine(sparse_contour);
			std::vector<cv::Point2f> symmetry_polygon;
			for (int j = 0; j < sparse_contour.size(); j++) {
				symmetry_polygon.push_back(util::mirrorPoint(symmetry_lines[i][0], symmetry_lines[i][1], sparse_contour[j]));
			}

			// calculate IOU between mirror polygon and original polygon
			float similarity_iou = util::calculateIOU(sparse_contour, symmetry_polygon);
			if (similarity_iou >= iouThreahold * 0.01){
				std::cout << i <<" is here" << std::endl;
				bvalid_symmetry_line = true;
				symmetry_lines_signal[i] = true;
			}
			else{
				bvalid_symmetry_line = false;
				symmetry_lines_signal[i] = false;
			}
			//compute distance
			//float distance = util::calculatePoLIS(sparse_contour, symmetry_polygon);
			//std::cout << "final distance is " << distance << std::endl;
			//if (distance <= 5){
			//	bvalid_symmetry_line = true;
			//	symmetry_lines_signal[i] = true;
			//}
			//else{
			//	bvalid_symmetry_line = false;
			//	symmetry_lines_signal[i] = false;
			//}
		}
		contours[i] = ShapeFit::fit(polygons[i].contour, contours_pre[i], bUseRaOpt, raThreahold, bUseParallelOpt, papallelThreahold, bvalid_symmetry_line, symmetry_lines[i]);
		////////// DEBUG //////////
		// output angles
		//{
		//	std::vector<cv::Point2f> polygon_symmetry;
		//	cv::Point2f a = symmetry_lines[i][0];
		//	cv::Point2f b = symmetry_lines[i][1];
		//	for (int j = 0; j < contours[i].size(); j++) {
		//		polygon_symmetry.push_back(util::mirrorPoint(a, b, contours[i][j]));
		//	}
		//	std::cout << "debug iou is " <<util::calculateIOU(contours[i], polygon_symmetry)<<std::endl;
		//}
		// calculate IOU
		if (util::isSimple(polygons[i].contour) && util::isSimple(contours[i]))
			std::cout << "IOU = " << util::calculateIOU(polygons[i].contour, contours[i]) << std::endl;
		else
			std::cout << "IOU = " << util::calculateIOUbyImage(polygons[i].contour, contours[i], 1000) << std::endl;
		std::cout << "#vertices = " << contours[i].size() << std::endl;
	}
}

void Canvas::generateContoursWithRA(int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, float ra_max_error, float ra_cluster_epsilon, bool ra_optimization) {
	detectContours();

	// detect principal orientation
	float principal_orientation = OrientationEstimator::estimate(polygons);

	// use the principal orientation, +45, +90, +135 degrees as principal orientations
	std::vector<float> principal_orientations;
	for (int i = 0; i < 4; i++) {
		principal_orientations.push_back(principal_orientation + CV_PI * i / 4);
	}

	// find sparse contours
	cv::Mat_<uchar> mat = cv::Mat(orig_image.height(), orig_image.width(), CV_8UC1, orig_image.bits(), orig_image.bytesPerLine()).clone();
	std::vector<util::Polygon> sparse_polygons = util::findContours(mat, 40, true, false, true);

	// detect circles and lines
	efficient_ransac::EfficientRANSAC er;
	shapes.resize(polygons.size());
	for (int i = 0; i < polygons.size(); i++) {
		if (polygons[i].contour.size() >= 100) {
			util::Polygon ra_polygon;
			try {
				// detect right angle edges
				ra_polygon = RightAngleSimplification::simplify(sparse_polygons[i], ra_max_error, principal_orientation, 0.02, ra_optimization);
			}
			catch (...) {}

			shapes[i] = er.detectWithRA(polygons[i].contour, curve_num_iterations, curve_min_points, curve_max_error_ratio_to_radius, curve_cluster_epsilon, curve_min_angle, curve_min_radius, curve_max_radius, line_num_iterations, line_min_points, line_max_error, line_cluster_epsilon, line_min_length, line_angle_threshold, principal_orientations, ra_polygon.contour, ra_max_error, ra_cluster_epsilon);
		}
	}

	// generate contours
	contours.resize(shapes.size());
	for (int i = 0; i < shapes.size(); i++) {
		std::sort(shapes[i].begin(), shapes[i].end());
		ContourGenerator::generate(polygons[i], shapes[i], contours[i], contour_max_error, contour_angle_threshold);

		////////// DEBUG //////////
		// calculate IOU
		std::cout << "IOU = " << util::calculateIOUbyImage(polygons[i].contour, contours[i]) << std::endl;
		std::cout << "#vertices = " << contours[i].size() << std::endl;
	}
}

void Canvas::keyPressEvent(QKeyEvent* e) {
	ctrlPressed = false;
	shiftPressed = false;

	if (e->modifiers() & Qt::ControlModifier) {
		ctrlPressed = true;
	}
	if (e->modifiers() & Qt::ShiftModifier) {
		shiftPressed = true;
	}

	switch (e->key()) {
	case Qt::Key_Space:
		break;
	}

	update();
}

void Canvas::keyReleaseEvent(QKeyEvent* e) {
	switch (e->key()) {
	case Qt::Key_Control:
		ctrlPressed = false;
		break;
	case Qt::Key_Shift:
		shiftPressed = false;
		break;
	default:
		break;
	}
}

void Canvas::paintEvent(QPaintEvent *event) {
	if (!image.isNull()) {
		QPainter painter(this);

		if (polygons.size() == 0) {
			painter.drawImage(0, 0, image);
		}
		else if (contours.size() == 0) {
			painter.fillRect(0, 0, width(), height(), QColor(255, 255, 255));

			painter.setPen(QPen(QColor(0, 0, 0), 1));
			for (auto& polygon : polygons) {
				QPolygon pgon;
				for (auto& p : polygon.contour) {
					pgon.push_back(QPoint(p.x * image_scale, p.y * image_scale));
				}
				painter.drawPolygon(pgon);
				for (auto& hole : polygon.holes) {
					QPolygon pgon;
					for (auto& p : hole) {
						pgon.push_back(QPoint(p.x * image_scale, p.y * image_scale));
					}
					painter.drawPolygon(pgon);
				}
			}

			for (auto& list : shapes) {
				for (auto& shape : list) {
					if (efficient_ransac::Circle* circle = dynamic_cast<efficient_ransac::Circle*>(shape.second.get())) {
						painter.setPen(QPen(QColor(255, 192, 192), 1));
						for (int i = 0; i < circle->points().size(); i++) {
							painter.drawRect(circle->points()[i].x * image_scale - 1, circle->points()[i].y * image_scale - 1, 2, 2);
						}

						painter.setPen(QPen(QColor(255, 0, 0), 3));
						float start_angle = std::min(circle->startAngle(), circle->endAngle());
						painter.drawArc((circle->center().x - circle->radius()) * image_scale, (circle->center().y - circle->radius()) * image_scale, circle->radius() * 2 * image_scale, circle->radius() * 2 * image_scale, -start_angle / CV_PI * 180 * 16, -circle->angleRange() / CV_PI * 180 * 16);
					}
					else if (efficient_ransac::Line* line = dynamic_cast<efficient_ransac::Line*>(shape.second.get())) {
						painter.setPen(QPen(QColor(192, 192, 255), 1));
						for (int i = 0; i < line->points().size(); i++) {
							painter.drawRect(line->points()[i].x * image_scale - 1, line->points()[i].y * image_scale - 1, 2, 2);
						}

						if (line->isRightAngle()) {
							painter.setPen(QPen(QColor(0, 192, 0), 3));
						}
						else {
							painter.setPen(QPen(QColor(0, 0, 255), 3));
						}
						cv::Point2f p1 = line->startPoint();
						cv::Point2f p2 = line->endPoint();
						painter.drawLine(p1.x * image_scale, p1.y * image_scale, p2.x * image_scale, p2.y * image_scale);
					}
				}
			}
		}
		else {
			painter.fillRect(0, 0, width(), height(), QColor(255, 255, 255));

			painter.setPen(QPen(QColor(0, 0, 0), 1));
			for (auto& polygon : polygons) {
				QPolygon pgon;
				for (auto& p : polygon.contour) {
					pgon.push_back(QPoint(p.x * image_scale, p.y * image_scale));
				}
				painter.drawPolygon(pgon);
				for (auto& hole : polygon.holes) {
					QPolygon pgon;
					for (auto& p : hole) {
						pgon.push_back(QPoint(p.x * image_scale, p.y * image_scale));
					}
					painter.drawPolygon(pgon);
				}
			}

			for (auto& contour : contours) {
				painter.setPen(QPen(QColor(0, 0, 255), 3));
				QPolygon pol;
				for (int i = 0; i < contour.size(); i++) {
					pol.push_back(QPoint(contour[i].x * image_scale, contour[i].y * image_scale));
				}
				painter.drawPolygon(pol);
			}

			//// test sparse polygon
			//{
			//	painter.setPen(QPen(QColor(255, 0, 0), 3));
			//	QPolygon pol;
			//	for (int i = 0; i < sparse_polygons_test[7].contour.size(); i++) {
			//		pol.push_back(QPoint(sparse_polygons_test[7].contour[i].x * image_scale, sparse_polygons_test[7].contour[i].y * image_scale));
			//	}
			//	painter.drawPolygon(pol);
			//}

			//// test polygon
			//{
			//	painter.setPen(QPen(QColor(0, 255, 0), 3));
			//	QPolygon pol;
			//	for (int i = 0; i < polygons[5].contour.size(); i++) {
			//		pol.push_back(QPoint(polygons[5].contour[i].x * image_scale, polygons[5].contour[i].y * image_scale));
			//	}
			//	painter.drawPolygon(pol);
			//}
		}

		// draw symmetry line
		if (symmetry_lines.size() != 0){
			for (int i = 0; i < symmetry_lines.size(); i++){
				if (symmetry_lines[i].size() == 0 || !symmetry_lines_signal[i]) continue;
				//std::cout << "paint symmetry line" << std::endl;
				painter.setPen(QPen(QColor(255, 0, 0), 3));
				cv::Point2f p1 = symmetry_lines[i][0];
				cv::Point2f p2 = symmetry_lines[i][1];
				painter.drawLine(p1.x * image_scale, p1.y * image_scale, p2.x * image_scale, p2.y * image_scale);
			}
			// draw symmetry polygons
			for (int i = 0; i < symmetry_polygons.size(); i++){
				painter.setPen(QPen(QColor(0, 0, 255), 3));
				if (symmetry_polygons[i].size() == 0 || !symmetry_lines_signal[i]) continue;
				QPolygon pol;
				for (int j = 0; j < symmetry_polygons[i].size(); j++) {
					pol.push_back(QPoint(symmetry_polygons[i][j].x * image_scale, symmetry_polygons[i][j].y * image_scale));
				}
				painter.drawPolygon(pol);
			}
		}
	}
}

void Canvas::mousePressEvent(QMouseEvent* e) {
	update();
}

void Canvas::resizeEvent(QResizeEvent *e) {
	if (!orig_image.isNull()) {
		image_scale = std::min((float)width() / orig_image.width(), (float)height() / orig_image.height());
		image = orig_image.scaled(orig_image.width() * image_scale, orig_image.height() * image_scale);
	}
}

