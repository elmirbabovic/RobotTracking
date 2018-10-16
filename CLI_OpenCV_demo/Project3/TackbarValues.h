#pragma once

ref struct TrackbarValues
{
	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;
	int V_DILATION_SIZE = 8;
	int V_EROSION_SIZE = 3;

	//minimum and maximum object area
	int MIN_OBJECT_AREA = 10;
	int MAX_OBJECT_AREA = 10;
};