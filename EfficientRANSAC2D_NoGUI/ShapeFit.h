#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <dlib/optimization.h>
#include "Util.h"

class ShapeFit {
		
	typedef dlib::matrix<double, 0, 1> column_vector;

	class BFGSSolver {
	private:
		std::vector<cv::Point2f> target_polygon;
		std::vector<cv::Point2f> init_polygon;
		bool bUseRaOpt;
		float angle_threshold_RA;
		bool bUseParallelOpt;
		float angle_threshold_parallel;
		bool bValidSymmetryLine;
		std::vector<cv::Point2f> symmetry_line;

	public:
		BFGSSolver(const std::vector<cv::Point2f>& target_polygon, const std::vector<cv::Point2f>& init_polygon, bool bUseRaOpt, float angle_threshold_RA, bool bUseParallelOpt, float angle_threshold_parallel, bool bValidSymmetryLine, const std::vector<cv::Point2f>& symmetry_line) {
			this->target_polygon = target_polygon;
			this->init_polygon = init_polygon;
			this->bUseRaOpt = bUseRaOpt;
			this->angle_threshold_RA = angle_threshold_RA;
			this->bUseParallelOpt = bUseParallelOpt;
			this->angle_threshold_parallel = angle_threshold_parallel;
			this->bValidSymmetryLine = bValidSymmetryLine;
			this->symmetry_line = symmetry_line;
			
		}

		double operator() (const column_vector& arg) const {
			std::vector<cv::Point2f> polygon;
			for (int i = 0; i < arg.size() / 2; i++) {
				polygon.push_back(cv::Point2f(arg(i * 2), arg(i * 2 + 1)));
			}

			try {			
				// RA opt function
				if (bUseRaOpt){
					std::cout << "use RA opt and threshold is " << angle_threshold_RA << std::endl;
					return util::calculateScore(polygon, init_polygon, angle_threshold_RA);
					//return 0.5 * util::calculateScore(polygon, init_polygon, angle_threshold_RA) + 0.5 * util::calculateIOU(polygon, target_polygon);
				}
				// parallel opt function
				else if (bUseParallelOpt){
					std::cout << "use Parallel opt and threshold is " << angle_threshold_parallel << std::endl;
					return util::calculateAllScore(polygon, init_polygon, angle_threshold_parallel);
				}

				// symmetry opt function
				else if (bValidSymmetryLine){
					std::vector<cv::Point2f> polygon_symmetry;
					cv::Point2f a = symmetry_line[0];
					cv::Point2f b = symmetry_line[1];
					for (int i = 0; i < polygon.size(); i++) {
						polygon_symmetry.push_back(util::mirrorPoint(a, b, polygon[i]));
					}
					float iou = 0.0f;
					if (!util::isSimple(polygon) || !util::isSimple(polygon_symmetry)){
						std::cout << "image method" << std::endl;
						iou = util::calculateIOUbyImage(polygon, polygon_symmetry, 1000);
					}
					else{
						iou = util::calculateIOU(polygon, polygon_symmetry);
						std::cout << "cgal method" << std::endl;
					}
					std::cout << "During OPT, IOU is " << iou << std::endl;
					return iou;

					/*float distance = util::calculatePoLIS(polygon, target_polygon);
					std::cout << "distance is " << distance << std::endl;
					return distance;*/
				}
				// accuracy function
				else{
					if (!util::isSimple(polygon) || !util::isSimple(target_polygon)){
						std::cout << "image method" << std::endl;
						return util::calculateIOUbyImage(polygon, target_polygon, 1000);
					}
					else{
						std::cout << "cgal method" << std::endl;
						return util::calculateIOU(polygon, target_polygon);
					}
					//return  util::calculateIOU(polygon, target_polygon);
					//return util::calculatePoLIS(polygon, target_polygon);
				}
			}
			catch (...) {
				std::cout << "exception" << std::endl;
				return 0;
			}
		}
	};

protected:
	ShapeFit();
	~ShapeFit();

public:
	static std::vector<cv::Point2f> fit(const std::vector<cv::Point2f>& target_polygon, const std::vector<cv::Point2f>& ini_points, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bValidSymmetryLine, const std::vector<cv::Point2f>& symmetry_line, float symmetryWeight, bool bUseAccuracyOpt, float accuracyWeight);
	static bool validRAorParallel(const std::vector<cv::Point2f>& polygon, bool bUseRaOpt, int ra_angle_threshold, bool bUseParallelOpt, int parallel_angle_threshold);
};

