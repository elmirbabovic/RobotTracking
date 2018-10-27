#pragma once

template<typename Tip>
void f_snimi(ofstream& f, Tip &tip)
{
	int v = sizeof(Tip);
	f.write((char*)&tip, v);
}


template<typename Tip>
void f_ucitaj(ifstream& f, Tip &tip)
{
	int v = sizeof(Tip);
	f.read((char*)&tip, v);
}
