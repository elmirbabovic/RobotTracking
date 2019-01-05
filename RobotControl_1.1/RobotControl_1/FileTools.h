#pragma once
#include <fstream>

template<typename Tip>
void f_snimi(std::ofstream& f, Tip &tip)
{
	int v = sizeof(Tip);
	f.write((char*)&tip, v);
}


template<typename Tip>
void f_ucitaj(std::ifstream& f, Tip &tip)
{
	int v = sizeof(Tip);
	f.read((char*)&tip, v);
}
