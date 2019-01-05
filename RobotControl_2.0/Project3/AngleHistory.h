#pragma once
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
struct AngleRecord
{
	float point;
	int versionNumber;

	AngleRecord(int versionNumber, float item)
	{
		this->point = item;
		this->versionNumber = versionNumber;
	}
};


class AngleHistory
{
private:
	int max_size;
	int counter;
	int endPosition;
	AngleRecord** N;

public:
	int Count()
	{
		return counter;
	}
	AngleRecord* GetOlderVersion(int p)
	{
		if (counter < p)
			return nullptr;

		int position = (endPosition - p + max_size) % max_size;
		return N[position];
	}

	AngleHistory(int max = 10)
	{
		this->max_size = max;
		this->counter = 0;
		this->endPosition = 0;
		this->N = new AngleRecord*[max];
		for (int i = 0; i < max; ++i)
		{
			N[i] = nullptr;
		}
	}

	AngleRecord* GetCurrent()
	{
		if (this->counter == 0)
			return nullptr;
		return GetOlderVersion(0);
	}

	void Add(int frameId, float angle)
	{
		endPosition++;

		if (endPosition == max_size)
			endPosition = 0;
		N[endPosition] = new AngleRecord(frameId, angle);


		counter++;
		if (counter > max_size)
			counter = max_size;
	}


	bool IsEmpty()
	{
		return counter == 0;
	}

	Lista<AngleRecord*>* ToMyList()
	{
		Lista<AngleRecord*>* result = new ListaPov<AngleRecord*>;
		for (int i = 0; i < counter; ++i)
		{
			result->Add(GetOlderVersion(0));
		}
		return result;
	}


};
