#pragma once
#include <vector>

class Model
{
private:
	const std::vector<double> smoothedData;
	const std::vector<double> trends;
	const std::vector<double> levels;
	const double sse;

public:
	Model(std::vector<double>& smoothedData, std::vector<double>& trends, std::vector<double>& levels, double sse) : smoothedData(smoothedData), trends(trends), levels(levels), sse(sse)
	{
	}

	/**
	 * Forecasts future values.
	 * * converted form Java
	 *https://geekprompt.github.io/Java-implementation-for-Double-Exponential-Smoothing-for-time-series-with-linear-trend/
	
	 * @param size no of future values that you need to forecast
	 * @return forecast data
	 */
	virtual std::vector<double> forecast(int size)
	{
		std::vector<double> forecastData(size);
		for (int i = 0; i < size; i++)
		{
			forecastData[i] = levels[levels.size() - 1] + (i + 1) * trends[trends.size() - 1];
		}
		return forecastData;
	}

	virtual std::vector<double> getSmoothedData()
	{
		return smoothedData;
	}

	virtual std::vector<double> getTrend()
	{
		return trends;
	}

	virtual std::vector<double> getLevel()
	{
		return levels;
	}

	virtual double getSSE()
	{
		return sse;
	}
};
