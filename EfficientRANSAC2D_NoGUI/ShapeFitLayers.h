#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <dlib/optimization.h>
#include "Util.h"
#include "Layer.h"

class ShapeFitLayers {
		
	typedef dlib::matrix<double, 0, 1> column_vector;
	typedef std::vector<std::vector<cv::Point2f>> layer_polygons;

	class BFGSSolver {
	private:
		std::vector<layer_polygons> target_layers_polygons;
		std::vector<layer_polygons> init_layers_polygons;
		bool bUseRaOpt;
		float angle_threshold_RA;
		float raWeight;
		bool bUseParallelOpt;
		float angle_threshold_parallel;
		float parallelWeight;
		bool bUseSymmetryLineOpt;
		std::vector<layer_polygons> layers_symmetry_lines;
		float symmetryWeight;
		bool bUseAccuracy;
		float accuracyWeight;
		std::vector<std::pair<float, float>> layers_height;

	public:
		BFGSSolver(const std::vector<layer_polygons>& target_layers_polygons, const std::vector<layer_polygons>& init_layers_polygons, const std::vector<std::pair<float, float>>& layers_height, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bUseSymmetryLineOpt, std::vector<layer_polygons> layers_symmetry_lines, float symmetryWeight, bool bUseAccuracy, float accuracyWeight) {
			this->target_layers_polygons = target_layers_polygons;
			this->init_layers_polygons = init_layers_polygons;
			this->layers_height = layers_height;
			this->bUseRaOpt = bUseRaOpt;
			this->angle_threshold_RA = angle_threshold_RA;
			this->raWeight = raWeight;
			this->bUseParallelOpt = bUseParallelOpt;
			this->angle_threshold_parallel = angle_threshold_parallel;
			this->parallelWeight = parallelWeight;
			this->bUseSymmetryLineOpt = bUseSymmetryLineOpt;
			this->layers_symmetry_lines = layers_symmetry_lines;
			this->symmetryWeight = symmetryWeight;
			this->bUseAccuracy = bUseAccuracy;
			this->accuracyWeight = accuracyWeight;		
		}

		double operator() (const column_vector& arg) const {
			std::vector<layer_polygons> polygons;
			polygons.resize(init_layers_polygons.size());
			int start_index = 0;
			for (int k = 0; k < init_layers_polygons.size(); k++){
				polygons[k].resize(init_layers_polygons[k].size());
				for (int i = 0; i < init_layers_polygons[k].size(); i++){
					for (int j = 0; j < init_layers_polygons[k][i].size(); j++) {
						polygons[k][i].push_back(cv::Point2f(arg((j + start_index) * 2), arg((j + start_index) * 2 + 1)));
					}
					start_index += init_layers_polygons[k][i].size();
				}
			}
			try {
				float score = 0.0f;
				int valid_polygons = 0;
				for (int k = 0; k < init_layers_polygons.size(); k++){
					for (int i = 0; i < init_layers_polygons[k].size(); i++){
						if (init_layers_polygons[k][i].size() != 0){
							// optimization score for one polygon
							// RA opt function
							if (bUseRaOpt){
								std::cout << "use RA opt" << std::endl;
								score += util::calculateScore(polygons[k][i], init_layers_polygons[k][i], angle_threshold_RA) * raWeight;
								//std::cout << "score is " << score <<std::endl;
							}
							// parallel opt function
							if (bUseParallelOpt){
								std::cout << "use Parallel opt" << std::endl;
								score += util::calculateAllScore(polygons[k][i], init_layers_polygons[k][i], angle_threshold_parallel) * parallelWeight;
							}

							// symmetry opt function
							if (bUseSymmetryLineOpt){
								if (layers_symmetry_lines[k][i].size() != 0){
									std::cout << "symmetry polygon is " << i << std::endl;
									std::vector<cv::Point2f> polygon_symmetry;
									cv::Point2f a = layers_symmetry_lines[k][i][0];
									cv::Point2f b = layers_symmetry_lines[k][i][1];
									for (int j = 0; j < polygons[i].size(); j++) {
										polygon_symmetry.push_back(util::mirrorPoint(a, b, polygons[k][i][j]));
									}
									float iou = 0.0f;
									if (!util::isSimple(polygons[k][i]) || !util::isSimple(polygon_symmetry)){
										std::cout << "image method" << std::endl;
										iou = util::calculateIOUbyImage(polygons[k][i], polygon_symmetry, 1000);
									}
									else{
										iou = util::calculateIOU(polygons[k][i], polygon_symmetry);
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
								if (!util::isSimple(polygons[k][i]) || !util::isSimple(target_layers_polygons[k][i])){
									std::cout << "image method" << std::endl;
									score += util::calculateIOUbyImage(polygons[k][i], target_layers_polygons[k][i], 1000) * accuracyWeight;
								}
								else{
									std::cout << "cgal method" << std::endl;
									score += util::calculateIOU(polygons[k][i], target_layers_polygons[k][i]) * accuracyWeight;
								}
							}
							if (bUseSymmetryLineOpt && !bUseRaOpt && !bUseParallelOpt && !bUseAccuracy){
								if (layers_symmetry_lines[k][i].size() != 0)
									valid_polygons++;
							}
							else
								valid_polygons++;
						}
					}
				}
				score = score / valid_polygons;
				std::cout << "valid_polygons is " << valid_polygons<<std::endl;
				std::cout << "---------------- " << std::endl;
				return score;
			}
			catch (...) {
				std::cout << "exception" << std::endl;
				return 0;
			}
		}
	};

protected:
	ShapeFitLayers();
	~ShapeFitLayers();

public:
	static void fit(std::vector<Layer>& layers, bool bUseRaOpt, float angle_threshold_RA, float raWeight, bool bUseParallelOpt, float angle_threshold_parallel, float parallelWeight, bool bUseSymmetryLineOpt, float symmetryWeight, bool bUseAccuracyOpt, float accuracyWeight);
	static bool validRAorParallel(const std::vector<cv::Point2f>& polygon, bool bUseRaOpt, int ra_angle_threshold, bool bUseParallelOpt, int parallel_angle_threshold);
};

