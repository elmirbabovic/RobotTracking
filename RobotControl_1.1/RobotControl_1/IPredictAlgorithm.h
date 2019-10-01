#pragma once
#include <core/mat.hpp>
#include "ATP/Lista.h"

public class IPredictAlgorithm
{

public: virtual Lista<cv::Point_<int>>* PredictPath(MotionHistory* motion_history, int numOfPredictPoints);
};
