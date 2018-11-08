#pragma once
#include <cmath>
#include <core/mat.hpp>


static float Udaljenost_DvijeTacke(cv::Point a, cv::Point b)
{
	float d = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return d;
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
