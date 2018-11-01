#pragma once

template <class Tip>
struct VersionItem
{
	Tip item;
	int versionNumber;
	public VersionItem(int versionNumber, Tip item)
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
	VersionItem<Tip>* N;

public:
	int getVelicina()
	{
		return brojac;
	}
	VersionItem<Tip> getOlderVersion(int p)
	{
		if (brojac < p)
			throw exception("brojac < p");

		int fizicikaPozicija = (kraj-p + max) % max;
		return N[fizicikaPozicija];
	}

	VersionDataStructure(int max = 10)
	{
		this->max = max;
		brojac = 0;
		kraj = 0;
		N = new Tip[max];
	}

	VersionItem<Tip> GetNajnovija()
	{
		if (brojac == 0)
			return nullptr;
		return getOlderVersion(0);
	}

	void dodaj(int versionNumber, Tip v)
	{
		kraj++;
		
		if (kraj == max)
			kraj = 0;
		N[kraj] = v;
		
			
		brojac++;
		if (brojac == max)
			brojac = 0;
	}


	bool isPrazan()
	{
		return brojac == 0;
	}

	void print(string pre = "", string post = ", ")
	{
		/*int i = pocetak;
		int b = 0;
		while (b++ < brojac)
		{
		cout << pre << N[i++] << post;
		if (i == max)
		i = 0;
		}*/
	}

	bool sadrzi(Tip value)
	{
		for (int i = 0; i < brojac; i++)
		{
			if (IsJednako(N[i], value))
				return true;
		}
		return false;
	}
};


