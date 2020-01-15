#pragma once
#include <string>
#include <utility>
#include "Kolo.h"

class Oblast;
using namespace std;

class Kandidat
{
public:
	Kandidat(string meno, unsigned int cisloKandidata) : meno_(std::move(meno)), cisloKandidata_(cisloKandidata) {}
	string getMeno() const { return meno_; }
	unsigned int getCislo() const { return cisloKandidata_; }
private:
	string meno_;
	unsigned int cisloKandidata_;
};