#pragma once
#include <stdexcept>
#include "Model.h"

class DoubleExponentialSmoothingForLinearSeries
{

	/**
	 * converted form Java
	 *https://geekprompt.github.io/Java-implementation-for-Double-Exponential-Smoothing-for-time-series-with-linear-trend/
	 * Performs double exponential smoothing for given time series.
	 * <p/>
	 * This method is suitable for fitting series with linear trend.
	 *
	 * @param data  An array containing the recorded data of the time series
	 * @param alpha Smoothing factor for data (0 < alpha < 1)
	 * @param beta  Smoothing factor for trend (0 < beta < 1)
	 * @return Instance of model that can be used to forecast future values
	 */
public:
	static Model* fit(std::vector<double>& data, double alpha, double beta)
	{
		validateParams(alpha, beta); //validating values of alpha and beta

		std::vector<double> smoothedData(data.size()); //array to store smoothed values

		std::vector<double> trends(data.size() + 1);
		std::vector<double> levels(data.size() + 1);

		//initializing values of parameters
		smoothedData[0] = data[0];
		trends[0] = data[1] - data[0];
		levels[0] = data[0];

		for (int t = 0; t < data.size(); t++)
		{
			smoothedData[t] = trends[t] + levels[t];
			levels[t + 1] = alpha * data[t] + (1 - alpha) * (levels[t] + trends[t]);
			trends[t + 1] = beta * (levels[t + 1] - levels[t]) + (1 - beta) * trends[t];
		}
		return new Model(smoothedData, trends, levels, calculateSSE(data, smoothedData));
	}

private:
	static double calculateSSE(std::vector<double> & data, std::vector<double> & smoothedData)
	{
		double sse = 0;
		for (int i = 0; i < data.size(); i++)
		{
			sse += std::pow(smoothedData[i] - data[i], 2);
		}
		return sse;
	}

	static void validateParams(double alpha, double beta)
	{
		if (alpha < 0 || alpha > 1)
		{
			throw std::runtime_error("The value of alpha must be between 0 and 1");
		}

		if (beta < 0 || beta > 1)
		{
			throw std::runtime_error("The value of beta must be between 0 and 1");
		}
	}
};
