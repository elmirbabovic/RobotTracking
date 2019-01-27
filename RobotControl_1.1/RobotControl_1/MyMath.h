#pragma once
#include <cmath>
#include <core/mat.hpp>
#include <string>

class MyMath
{
public:
	static int GetMaxIndex(double array[], int arraySize, int tolerance)
	{
		double maxV = array[0];
		int maxI = 0;
		for (int i = 1; i < arraySize; i++)
		{
			if (array[i] > maxV )
			{
				maxV = array[i];
				maxI = i;
			}
		}

		if (maxV >= tolerance)
			return maxI;
		return -1;
	}



		static float Udaljenost_DvijeTacke(cv::Point a, cv::Point b)
		{
			float d = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
			return d;
		}
		static float GetC(float a, float b)
		{
			return sqrt(a*a + b*b);
		}

		static int DeltaX(const cv::Point& p1, const cv::Point& p2)
		{
			return p2.x - p1.x;
		}

		static int DeltaY(const cv::Point& p1, const cv::Point& p2)
		{
			return p2.y - p1.y;
		}

		static float IzracunajUgao(float dx, float dy)
		{
			float PI = 3.14159265;
			float alpha = atan2(dy, dx) * 180 / PI;
			return alpha;
		}

		static float IzracunajOdnos(float alpha)
		{
			float PI = 3.14159265;
			float xy = tan(alpha*PI / 180);
			return xy;
		}
};

static std::string intToString(int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}