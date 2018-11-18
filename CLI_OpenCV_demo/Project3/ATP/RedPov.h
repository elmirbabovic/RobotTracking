#pragma once

#include "Red.h"
#include "UsporedbaGeneric.h"

template <class Tip>
class RedPov : public Red<Tip>
{
private:
	Cvor<Tip>* pocetak;
	Cvor<Tip>* kraj;
	int brojac=0;
public:

	int getVelicina()
	{
		return brojac;
	}
	Tip getSaPozicije(int p)
	{
		if (brojac < p)
			throw exception("brojac < p");

		auto t = pocetak;
		for (int i = 0; i < brojac-1; ++i)
		{
			t = t->next;
		}
		return t->info;
	}

	RedPov()
	{
		pocetak = nullptr;
		kraj = nullptr;
	
	}
	void dodaj(Tip v)
	{
		Cvor<Tip>* t = new Cvor<Tip>(v, nullptr);
		if (!isPrazan())
		{
			kraj->next = t;
			kraj = t;
		}
		else
		{
			kraj = t;
			pocetak = t;
		}
		brojac++;
	}

	Tip ukloni()
	{
		if (isPrazan())
			throw exception("Greska. Nije moguce ukloniti elemenat iz praznog reda.");

		Cvor<Tip>* t= pocetak;
		pocetak = pocetak->next;

		Tip x = t->info;
		delete t;


		if (pocetak == nullptr)
			kraj = nullptr;
		brojac--;
		return x;

	}

	bool isPrazan()
	{
		return pocetak == nullptr;
	}

	void print(string pre = "", string post = ", ")
	{
		Cvor<Tip>* t = pocetak;
		while (t != nullptr)
		{
			cout << pre << t->info << post;
			t = t->next;
		}
	}

	bool sadrzi(Tip v)
	{
		Cvor<Tip>* t = pocetak;
		while (t != nullptr)
		{
			if (IsJednako(t->info, v))
				return true;
			t = t->next;
		}
		return false;
	}
};


