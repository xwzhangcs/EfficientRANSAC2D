#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <dlib/optimization.h>
#include "Util.h"

class ShapeFitLayer {
		
	typedef dlib::matrix<double, 0, 1> column_vector;

	class BFGSSolver {
	private:
		std::vector<std::vector<cv::Point2f>> target_polygons;
		std::vector<std::vector<cv::Point2f>> init_polygons;
		bool bUseRaOpt;
		float angle_threshold_RA;
		float raWeight;
		bool bUseParallelOpt;
		float angle_threshold_parallel;
		float parallelWeight;
		bool bUseSymmetryLineOpt;
		std::vector<std::vector<cv::Point2f>> symmetry_lines;
		float symmetryWeight;
		bool bUseAccuracy;
		float accuracyWeight;

	public:
		BFGSSolver(const std::vector<std::vector<cv::Point2f>>& target_polygons, const std::vector<std::vector<cv::Point2f>>& init_polygons, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bUseSymmetryLineOpt, const std::vector<std::vector<cv::Point2f>>& symmetry_lines, float symmetryWeight, bool bUseAccuracy, float accuracyWeight) {
			this->target_polygons = target_polygons;
			this->init_polygons = init_polygons;
			this->bUseRaOpt = bUseRaOpt;
			this->angle_threshold_RA = angle_threshold_RA;
			this->raWeight = raWeight;
			this->bUseParallelOpt = bUseParallelOpt;
			this->angle_threshold_parallel = angle_threshold_parallel;
			this->parallelWeight = parallelWeight;
			this->bUseSymmetryLineOpt = bUseSymmetryLineOpt;
			this->symmetry_lines = symmetry_lines;
			this->symmetryWeight = symmetryWeight;
			this->bUseAccuracy = bUseAccuracy;
			this->accuracyWeight = accuracyWeight;		
		}

		double operator() (const column_vector& arg) const {
			std::vector<std::vector<cv::Point2f>> polygons;
			polygons.resize(init_polygons.size());
			int start_index = 0;
			for (int i = 0; i < init_polygons.size(); i++){
				for (int j = 0; j < init_polygons[i].size(); j++) {
					polygons[i].push_back(cv::Point2f(arg((j + start_index) * 2), arg((j + start_index) * 2 + 1)));
				}
				start_index += init_polygons[i].size();
			}
			try {
				float score = 0.0f;
				int valid_polygons = 0;
				for (int i= 0; i < init_polygons.size(); i++){
					if (init_polygons[i].size() != 0){
						// optimization score for one polygon
						// RA opt function
						if (bUseRaOpt){
							std::cout << "use RA opt" << std::endl;
							score += util::calculateScore(polygons[i], init_polygons[i], angle_threshold_RA) * raWeight;
						}
						// parallel opt function
						if (bUseParallelOpt){
							std::cout << "use Parallel opt"<< std::endl;
							score += util::calculateAllScore(polygons[i], init_polygons[i], angle_threshold_parallel) * parallelWeight;
						}

						// symmetry opt function
						if (bUseSymmetryLineOpt){
							if (symmetry_lines[i].size() != 0){
								std::vector<cv::Point2f> polygon_symmetry;
								cv::Point2f a = symmetry_lines[i][0];
								cv::Point2f b = symmetry_lines[i][1];
								for (int j = 0; j < polygons[i].size(); j++) {
									polygon_symmetry.push_back(util::mirrorPoint(a, b, polygons[i][j]));
								}
								float iou = 0.0f;
								if (!util::isSimple(polygons[i]) || !util::isSimple(polygon_symmetry)){
									std::cout << "image method" << std::endl;
									iou = util::calculateIOUbyImage(polygons[i], polygon_symmetry, 1000);
								}
								else{
									iou = util::calculateIOU(polygons[i], polygon_symmetry);
									std::cout << "cgal method" << std::endl;
								}
								std::cout << "During OPT, IOU is " << iou << std::endl;
								score += iou * symmetryWeight;
							}
							else{
								// no symmetry line for this polygon
							}
						}
						if (bUseAccuracy)
						{
							if (!util::isSimple(polygons[i]) || !util::isSimple(target_polygons[i])){
								std::cout << "image method" << std::endl;
								score += util::calculateIOUbyImage(polygons[i], target_polygons[i], 1000) * accuracyWeight;
							}
							else{
								std::cout << "cgal method" << std::endl;
								score += util::calculateIOU(polygons[i], target_polygons[i]) * accuracyWeight;
							}
						}

						valid_polygons++;
					}
				}
				score = score / valid_polygons;
				return score;
			}
			catch (...) {
				std::cout << "exception" << std::endl;
				return 0;
			}
		}
	};

protected:
	ShapeFitLayer();
	~ShapeFitLayer();

public:
	static std::vector<std::vector<cv::Point2f>> fit(const std::vector<std::vector<cv::Point2f>>& target_polygon, const std::vector<std::vector<cv::Point2f>>& ini_points, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bUseSymmetryLineOpt, const std::vector<std::vector<cv::Point2f>>& symmetry_lines, float symmetryWeight, bool bUseAccuracyOpt, float accuracyWeight);
	static bool validRAorParallel(const std::vector<cv::Point2f>& polygon, bool bUseRaOpt, int ra_angle_threshold, bool bUseParallelOpt, int parallel_angle_threshold);
};
