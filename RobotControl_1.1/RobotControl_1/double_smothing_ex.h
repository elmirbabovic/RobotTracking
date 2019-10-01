#pragma once
#include "IPredictAlgorithm.h"
#include "DoubleExponentialSmoothingForLinearSeries.h"


public class double_smothing_ex
{
public: virtual Lista<cv::Point_<int>>* PredictPath(MotionHistory* motion_history, int numOfPredictPoints)
	{
	Lista<cv::Point>* forecastPoints = new  ListaSekv<cv::Point>(numOfPredictPoints);

		int historySize = motion_history->Count();
		if (historySize < 55)
			return forecastPoints;

	double alpha = 0.3;
	double beta = 0.6;
	vector<double> historyX;
	vector<double> historyY;
		for(int i= numOfPredictPoints -1; i>=0;i--)
		{
			cv::Point p = motion_history->GetOlderVersion(i)->point;
			
			historyX.push_back(p.x);
			historyY.push_back(p.y);
		}

	Model* modelX = DoubleExponentialSmoothingForLinearSeries::fit(historyX, alpha, beta);
	Model* modelY = DoubleExponentialSmoothingForLinearSeries::fit(historyY, alpha, beta);


	std::vector<double> forecastX = modelX->forecast(numOfPredictPoints);
	std::vector<double> forecastY = modelY->forecast(numOfPredictPoints);

	
	for (int i=0;i< forecastX.size();i++)
	{
		forecastPoints->Add(cv::Point(forecastX[i], forecastY[i]));
	}

	return forecastPoints;
	}
};
