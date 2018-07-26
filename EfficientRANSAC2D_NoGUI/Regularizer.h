#include <vector>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include "../EfficientRANSAC2D_NoGUI/Layer.h"

class Regularizer{

public:
	Regularizer();
	void regularizerForLayer(QString fileName, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight);
	void regularizerForLayers(std::vector<QString> fileNameList, std::vector<std::pair<float, float>> height_infoint, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight);
	void createLayer(QString fileName, Layer & layer, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold);
	void createLayers(std::vector<QString> fileNameList, std::vector<std::pair<float, float>> height_info, std::vector<Layer>& layers, int curve_num_iterations, int curve_min_points, float curve_max_error_ratio_to_radius, float curve_cluster_epsilon, float curve_min_angle, float curve_min_radius, float curve_max_radius, int line_num_iterations, int line_min_points, float line_max_error, float line_cluster_epsilon, float line_min_length, float line_angle_threshold, float contour_max_error, float contour_angle_threshold, bool bUseSymmetryLineOpt, float iouThreahold);
	void generateContoursLayer(Layer& input_layer, bool bUseSymmetryLineOpt, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight);
	void generateContoursLayers(std::vector<Layer>& input_layers, bool bUseSymmetryLine, float symmetryWeight, bool bUseRaOpt, float raThreahold, float raWeight, bool bUseParallelOpt, float papallelThreahold, float parallelWeight, bool bUseAccuracyOpt, float accuracyWeight);
	void saveImage(Layer & layer, int index);
	//void saveImages();
};
