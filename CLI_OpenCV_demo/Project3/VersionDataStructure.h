#pragma once
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
template <class Tip>
struct VersionItem
{
	Tip item;
	int versionNumber;

	VersionItem(int versionNumber, Tip item)
	{
		this->item = item;
		this->versionNumber = versionNumber;
	}
};

template <class Tip>
class VersionDataStructure
{
private:
	int max;
	int brojac;
	int kraj;
	VersionItem<Tip>** N;

public:
	int getVelicina()
	{
		return brojac;
	}
	VersionItem<Tip>* getOlderVersion(int p)
	{
		if (brojac < p)
			throw exception("brojac < p");

		int fizicikaPozicija = (kraj - p + max) % max;
		return N[fizicikaPozicija];
	}

	VersionDataStructure(int max = 10)
	{
		this->max = max;
		this->brojac = 0;
		this->kraj = 0;
		this->N = new VersionItem<Tip>*[max];
	}

	VersionItem<Tip>* GetNajnovija()
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
		N[kraj] = new VersionItem<Tip>(versionNumber, v);


		brojac++;
		if (brojac > max)
			brojac = max;
	}


	bool isPrazan()
	{
		return brojac == 0;
	}

	Lista<VersionItem<Tip>>* ToLista()
	{
		Lista<VersionItem<Tip>>* result = new ListaPov<VersionItem<Tip>>;
		for (int i = 0; i < brojac; ++i)
		{
			result->dodaj(getOlderVersion(0));
		}
		return result;
	}


};
