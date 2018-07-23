#include "ShapeFit.h"

ShapeFit::ShapeFit() {
}

ShapeFit::~ShapeFit() {
}

std::vector<cv::Point2f> ShapeFit::fit(const std::vector<cv::Point2f>& polygon, const std::vector<cv::Point2f>& ini_points, bool bUseRaOpt, float angle_threshold_RA, bool bUseParallelOpt, float angle_threshold_parallel, bool bValidSymmetryLine, const std::vector<cv::Point2f>& symmetry_line) {
	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	float max_x = -std::numeric_limits<float>::max();
	float max_y = -std::numeric_limits<float>::max();
	std::cout << "polygon size is " << polygon.size() << std::endl;
	std::cout << "ini_points size is " << ini_points.size() << std::endl;
	for (int i = 0; i < polygon.size(); i++) {
		min_x = std::min(min_x, polygon[i].x);
		min_y = std::min(min_y, polygon[i].y);
		max_x = std::max(max_x, polygon[i].x);
		max_y = std::max(max_y, polygon[i].y);
	}
	for (int i = 0; i < ini_points.size(); i++) {
		min_x = std::min(min_x, ini_points[i].x);
		min_y = std::min(min_y, ini_points[i].y);
		max_x = std::max(max_x, ini_points[i].x);
		max_y = std::max(max_y, ini_points[i].y);
	}
	if (bValidSymmetryLine)
		for (int i = 0; i < symmetry_line.size(); i++){
			min_x = std::min(min_x, symmetry_line[i].x);
			min_y = std::min(min_y, symmetry_line[i].y);
			max_x = std::max(max_x, symmetry_line[i].x);
			max_y = std::max(max_y, symmetry_line[i].y);
		}

	float max_unit = std::max(max_x - min_x, max_y - min_y);
	std::vector<cv::Point2f> normalized_polygon(polygon.size());
	for (int i = 0; i < polygon.size(); i++) {
		normalized_polygon[i] = cv::Point2f((polygon[i].x - min_x) / max_unit, (polygon[i].y - min_y) / max_unit);
	}

	// normalized_symmetry_line
	std::vector<cv::Point2f> normalized_symmetry_line;

	if (bValidSymmetryLine){
		normalized_symmetry_line.resize(symmetry_line.size());
		for (int i = 0; i < symmetry_line.size(); i++) {
			normalized_symmetry_line[i] = cv::Point2f((symmetry_line[i].x - min_x) / max_unit, (symmetry_line[i].y - min_y) / max_unit);
		}
	}

	std::vector<cv::Point2f> normalized_polygon_init(ini_points.size());
	for (int i = 0; i < ini_points.size(); i++) {
		normalized_polygon_init[i] = cv::Point2f((ini_points[i].x - min_x) / max_unit, (ini_points[i].y - min_y) / max_unit);
	}

	try {
		column_vector starting_point(normalized_polygon_init.size() * 2);
		for (int i = 0; i < normalized_polygon_init.size(); i++){
			starting_point(i * 2) = normalized_polygon_init[i].x;
			starting_point(i * 2 + 1) = normalized_polygon_init[i].y;
		}

		BFGSSolver solver(normalized_polygon, normalized_polygon_init, bUseRaOpt, angle_threshold_RA, bUseParallelOpt, angle_threshold_parallel, bValidSymmetryLine, normalized_symmetry_line);
		if (true)
			find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(), dlib::objective_delta_stop_strategy(1e-7),	solver, starting_point, 1, 0.0001);
		else
			find_min_using_approximate_derivatives(dlib::bfgs_search_strategy(), dlib::objective_delta_stop_strategy(1e-7), solver, starting_point, 0, 0.0001);
		std::vector<cv::Point2f> ans(starting_point.size() / 2);
		for (int i = 0; i < starting_point.size() / 2; i++) {
			ans[i].x = starting_point(i * 2) * max_unit + min_x;
			ans[i].y = starting_point(i * 2 + 1) * max_unit + min_y;
		}

		return ans;
	}
	catch (char* ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "BFGS optimization failure." << std::endl;
	}

	return{};
}