#pragma once
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
struct MotionStep
{
	cv::Point point;
	int versionNumber;

	MotionStep(int versionNumber, cv::Point item)
	{
		this->point = item;
		this->versionNumber = versionNumber;
	}

	MotionStep(int versionNumber, int x, int y)
	{
		this->point = cv::Point(x,y);
		this->versionNumber = versionNumber;
	}
};


class MotionHistory
{
private:
	int max_size;
	int counter;
	int endPosition;
	MotionStep** N;

public:
	int Count()
	{
		return counter;
	}
	MotionStep* GetOlderVersion(int p)
	{
		if (counter < p)
			return nullptr;

		int position = (endPosition - p + max_size) % max_size;
		return N[position];
	}

	MotionHistory(int max = 10)
	{
		this->max_size = max;
		this->counter = 0;
		this->endPosition = 0;
		this->N = new MotionStep*[max];
		for (int i = 0; i < max; ++i)
		{
			N[i] = nullptr;
		}
	}

	MotionStep* GetCurrent()
	{
		if (this->counter == 0)
			return nullptr;
		return GetOlderVersion(0);
	}

	void Add(int frameId, cv::Point point)
	{
		endPosition++;

		if (endPosition == max_size)
			endPosition = 0;
		N[endPosition] = new MotionStep(frameId, point);


		counter++;
		if (counter > max_size)
			counter = max_size;
	}


	bool IsEmpty()
	{
		return counter == 0;
	}

	Lista<MotionStep*>* ToMyList()
	{
		Lista<MotionStep*>* result = new ListaPov<MotionStep*>;
		for (int i = 0; i < counter; ++i)
		{
			result->Add(GetOlderVersion(0));
		}
		return result;
	}


};
