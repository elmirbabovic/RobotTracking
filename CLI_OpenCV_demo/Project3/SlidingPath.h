#pragma once
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
struct MotionStep
{
	cv::Point item;
	int versionNumber;

	MotionStep(int versionNumber, cv::Point item)
	{
		this->item = item;
		this->versionNumber = versionNumber;
	}
};


class SlidingPath
{
private:
	int max;
	int brojac;
	int kraj;
	MotionStep** N;

public:
	int getVelicina()
	{
		return brojac;
	}
	MotionStep* getOlderVersion(int p)
	{
		if (brojac < p)
			return nullptr;

		int fizicikaPozicija = (kraj - p + max) % max;
		return N[fizicikaPozicija];
	}

	SlidingPath(int max = 10)
	{
		this->max = max;
		this->brojac = 0;
		this->kraj = 0;
		this->N = new MotionStep*[max];
		for (int i = 0; i < max; ++i)
		{
			N[i] = nullptr;
		}
	}

	MotionStep* GetNajnovija()
	{
		if (this->brojac == 0)
			return nullptr;
		return getOlderVersion(0);
	}

	void dodaj(int versionNumber, cv::Point v)
	{
		kraj++;

		if (kraj == max)
			kraj = 0;
		N[kraj] = new MotionStep(versionNumber, v);


		brojac++;
		if (brojac > max)
			brojac = max;
	}


	bool isPrazan()
	{
		return brojac == 0;
	}

	Lista<MotionStep*>* ToLista()
	{
		Lista<MotionStep*>* result = new ListaPov<MotionStep*>;
		for (int i = 0; i < brojac; ++i)
		{
			result->dodaj(getOlderVersion(0));
		}
		return result;
	}


};
