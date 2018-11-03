#pragma once
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
template <class Tip>
struct MotionStep
{
	Tip item;
	int versionNumber;

	MotionStep(int versionNumber, Tip item)
	{
		this->item = item;
		this->versionNumber = versionNumber;
	}
};

template <class Tip>
class SlidingPath
{
private:
	int max;
	int brojac;
	int kraj;
	MotionStep<Tip>** N;

public:
	int getVelicina()
	{
		return brojac;
	}
	MotionStep<Tip>* getOlderVersion(int p)
	{
		if (brojac < p)
			throw exception("brojac < p");

		int fizicikaPozicija = (kraj - p + max) % max;
		return N[fizicikaPozicija];
	}

	SlidingPath(int max = 10)
	{
		this->max = max;
		this->brojac = 0;
		this->kraj = 0;
		this->N = new MotionStep<Tip>*[max];
	}

	MotionStep<Tip>* GetNajnovija()
	{
		if (this->brojac == 0)
			return nullptr;
		return getOlderVersion(0);
	}

	void dodaj(int versionNumber, Tip v)
	{
		kraj++;

		if (kraj == max)
			kraj = 0;
		N[kraj] = new MotionStep<Tip>(versionNumber, v);


		brojac++;
		if (brojac > max)
			brojac = max;
	}


	bool isPrazan()
	{
		return brojac == 0;
	}

	Lista<MotionStep<Tip>>* ToLista()
	{
		Lista<MotionStep<Tip>>* result = new ListaPov<MotionStep<Tip>>;
		for (int i = 0; i < brojac; ++i)
		{
			result->dodaj(getOlderVersion(0));
		}
		return result;
	}


};
