#include "ShapeFitLayers.h"

ShapeFitLayers::ShapeFitLayers() {
}

ShapeFitLayers::~ShapeFitLayers() {
}

void ShapeFitLayers::fit(std::vector<Layer>& layers, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bUseSymmetryLineOpt, float symmetryWeight, bool bUseAccuracyOpt, float accuracyWeight)
{
	//{
	//	std::cout << "bUseRa " << bUseRaOpt << " ra angle is " << angle_threshold_RA << " ra weight is " << raWeight << std::endl;
	//	std::cout << "bUseParallel " << bUseParallelOpt << " Parallel angle is " << angle_threshold_parallel << " Parallel weight is " << parallelWeight << std::endl;
	//	std::cout << "bUseSymmetry " << bUseSymmetryLineOpt << " Symmetry weight is " << symmetryWeight << std::endl;
	//	std::cout << "bUseAccuracy " << bUseAccuracyOpt << " Accuracy weight is " << accuracyWeight << std::endl;
	//}
	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	float max_x = -std::numeric_limits<float>::max();
	float max_y = -std::numeric_limits<float>::max();
	for (int k = 0; k < layers.size(); k++){
		for (int i = 0; i < layers[k].sparse_contours.size(); i++) {
			for (int j = 0; j < layers[k].sparse_contours[i].size(); j++){
				min_x = std::min(min_x, layers[k].sparse_contours[i][j].x);
				min_y = std::min(min_y, layers[k].sparse_contours[i][j].y);
				max_x = std::max(max_x, layers[k].sparse_contours[i][j].x);
				max_y = std::max(max_y, layers[k].sparse_contours[i][j].y);
			}
		}
	}
	for (int k = 0; k < layers.size(); k++){
		for (int i = 0; i < layers[k].contours_pre.size(); i++) {
			for (int j = 0; j < layers[k].contours_pre[i].size(); j++){
				min_x = std::min(min_x, layers[k].contours_pre[i][j].x);
				min_y = std::min(min_y, layers[k].contours_pre[i][j].y);
				max_x = std::max(max_x, layers[k].contours_pre[i][j].x);
				max_y = std::max(max_y, layers[k].contours_pre[i][j].y);
			}
		}
	}
	if (bUseSymmetryLineOpt){
		for (int k = 0; k < layers.size(); k++){
			for (int i = 0; i < layers[k].symmetry_lines.size(); i++){
				for (int j = 0; j < layers[k].symmetry_lines[i].size(); j++){
					min_x = std::min(min_x, layers[k].symmetry_lines[i][j].x);
					min_y = std::min(min_y, layers[k].symmetry_lines[i][j].y);
					max_x = std::max(max_x, layers[k].symmetry_lines[i][j].x);
					max_y = std::max(max_y, layers[k].symmetry_lines[i][j].y);
				}
			}
		}
	}
	float max_unit = std::max(max_x - min_x, max_y - min_y);
	std::vector<layer_polygons> normalized_polygons(layers.size());
	for (int k = 0; k < layers.size(); k++){
		normalized_polygons[k].resize(layers[k].sparse_contours.size());
		for (int i = 0; i < layers[k].sparse_contours.size(); i++) {
			normalized_polygons[k][i].resize(layers[k].sparse_contours[i].size());
			for (int j = 0; j < layers[k].sparse_contours[i].size(); j++){
				normalized_polygons[k][i][j] = cv::Point2f((layers[k].sparse_contours[i][j].x - min_x) / max_unit, (layers[k].sparse_contours[i][j].y - min_y) / max_unit);
			}
		}
	}

	// normalized_symmetry_line
	std::vector<layer_polygons> normalized_symmetry_lines;

	if (bUseSymmetryLineOpt){
		normalized_symmetry_lines.resize(layers.size());
		for (int k = 0; k < layers.size(); k++){
			normalized_symmetry_lines[k].resize(layers[k].symmetry_lines.size());
			for (int i = 0; i < layers[k].symmetry_lines.size(); i++) {
				normalized_symmetry_lines[k][i].resize(layers[k].symmetry_lines[i].size());
				for (int j = 0; j < layers[k].symmetry_lines[i].size(); j++){
					normalized_symmetry_lines[k][i][j] = cv::Point2f((layers[k].symmetry_lines[i][j].x - min_x) / max_unit, (layers[k].symmetry_lines[i][j].y - min_y) / max_unit);
				}
			}
		}
	}

	int total_points = 0;
	std::vector<layer_polygons> normalized_polygons_init(layers.size());
	for (int k = 0; k < layers.size(); k++){
		normalized_polygons_init[k].resize(layers[k].contours_pre.size());
		for (int i = 0; i < layers[k].contours_pre.size(); i++) {
			normalized_polygons_init[k][i].resize(layers[k].contours_pre[i].size());
			total_points += layers[k].contours_pre[i].size();
			for (int j = 0; j < layers[k].contours_pre[i].size(); j++){
				normalized_polygons_init[k][i][j] = cv::Point2f((layers[k].contours_pre[i][j].x - min_x) / max_unit, (layers[k].contours_pre[i][j].y - min_y) / max_unit);
			}
		}
	}

	// we need to check whether there are valid angles
	if (bUseRaOpt || bUseParallelOpt){
		bool bValid = false;
		for (int k = 0; k < layers.size(); k++){
			for (int i = 0; i < layers[k].contours_pre.size(); i++){
				if (layers[k].contours_pre[i].size() != 0){
					if (validRAorParallel(layers[k].contours_pre[i], bUseRaOpt, angle_threshold_RA, bUseParallelOpt, angle_threshold_parallel)){
						bValid = true;
						break;
					}
				}
			}
			if (bValid)
				break;
		}
		if (!bValid){
			std::cout << "no need to do optimizaiton for RA and parallel" << std::endl;
		}
	}
	std::vector<std::pair<float, float>> layers_height;
	layers_height.resize(layers.size());
	for (int k = 0; k < layers.size(); k++){
		layers_height[k] = std::make_pair(layers[k].top_height, layers[k].bottom_height);
	}
	try {
		std::cout << "total points is " << total_points << std::endl;
		column_vector starting_point(total_points * 2);
		int start_index = 0;
		for (int k = 0; k < normalized_polygons_init.size(); k++){
			for (int i = 0; i < normalized_polygons_init[k].size(); i++){
				for (int j = 0; j < normalized_polygons_init[k][i].size(); j++){
					starting_point((j + start_index) * 2) = normalized_polygons_init[k][i][j].x;
					starting_point((j + start_index) * 2 + 1) = normalized_polygons_init[k][i][j].y;
				}
				start_index += normalized_polygons_init[k][i].size();
			}
		}
		BFGSSolver solver(normalized_polygons, normalized_polygons_init, layers_height, bUseRaOpt, angle_threshold_RA, raWeight, bUseParallelOpt, angle_threshold_parallel, parallelWeight, bUseSymmetryLineOpt, normalized_symmetry_lines, symmetryWeight, bUseAccuracyOpt, accuracyWeight);
		if (true)
			find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(), dlib::objective_delta_stop_strategy(1e-7), solver, starting_point, 1, 0.0001);
		else
			find_min_using_approximate_derivatives(dlib::bfgs_search_strategy(), dlib::objective_delta_stop_strategy(1e-7), solver, starting_point, 0, 0.0001);
		start_index = 0;
		for (int k = 0; k < layers.size(); k++){
			layers[k].contours.resize(layers[k].contours_pre.size());
			for (int i = 0; i < layers[k].contours_pre.size(); i++) {
				layers[k].contours[i].resize(layers[k].contours_pre[i].size());
				for (int j = 0; j < layers[k].contours_pre[i].size(); j++){
					layers[k].contours[i][j].x = starting_point((j + start_index) * 2) * max_unit + min_x;
					layers[k].contours[i][j].y = starting_point((j + start_index) * 2 + 1) * max_unit + min_y;
				}
				start_index += layers[k].contours_pre[i].size();
			}
		}
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

}

bool ShapeFitLayers::validRAorParallel(const std::vector<cv::Point2f>& polygon, bool bUseRaOpt, int ra_angle_threshold, bool bUseParallelOpt, int parallel_angle_threshold){
	int total_segments = polygon.size();
	if (bUseRaOpt){
		for (int i = 0; i < total_segments; i++){
			int first_start = i;
			int first_end = (i + 1) % total_segments;
			int second_start = (i + 1) % total_segments;
			int second_end = (i + 2) % total_segments;

			// init angles
			cv::Point2f a_init = cv::Point2f(polygon[first_start].x, polygon[first_start].y);
			cv::Point2f b_init = cv::Point2f(polygon[first_end].x, polygon[first_end].y);
			cv::Point2f c_init = cv::Point2f(polygon[second_start].x, polygon[second_start].y);;
			cv::Point2f d_init = cv::Point2f(polygon[second_end].x, polygon[second_end].y);
			float angle_init = util::lineLineAngle(a_init, b_init, c_init, d_init);
			std::cout << i << " angle is " << angle_init << std::endl;
			// check
			if (abs(angle_init - 45) <= ra_angle_threshold || abs(angle_init - 90) <= ra_angle_threshold || abs(angle_init - 135) <= ra_angle_threshold){
				return true;
			}
		}
		return false;
	}
	if (bUseParallelOpt){
		for (int i = 0; i < total_segments - 1; i++){
			for (int j = i + 1; j < total_segments; j++){
				int first_start = i;
				int first_end = (i + 1) % total_segments;
				int second_start = j;
				int second_end = (j + 1) % total_segments;

				// init angles
				cv::Point2f a_init = cv::Point2f(polygon[first_start].x, polygon[first_start].y);
				cv::Point2f b_init = cv::Point2f(polygon[first_end].x, polygon[first_end].y);
				cv::Point2f c_init = cv::Point2f(polygon[second_start].x, polygon[second_start].y);;
				cv::Point2f d_init = cv::Point2f(polygon[second_end].x, polygon[second_end].y);
				float angle_init = util::lineLineAngle(a_init, b_init, c_init, d_init);
				std::cout << i <<" to "<<j <<" angle is " << angle_init << std::endl;
				// check
				if (abs(angle_init) <= parallel_angle_threshold || abs(angle_init - 180) <= parallel_angle_threshold)
					return true;
			}
		}
		return false;
	}
}