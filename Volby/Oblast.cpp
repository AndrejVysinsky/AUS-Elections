#include "Oblast.h"
#include <utility>
#include <iostream>

Oblast::Oblast(string nazov, unsigned int kod, Oblast* patriDoKraja, Oblast* patriDoOkresu)
	: nazov_(std::move(nazov)), kodOblasti_(kod), patriDoKraja_(patriDoKraja), patriDoOkresu_(patriDoOkresu)
{
}

unsigned int Oblast::pocetZapisanychVolicovVKole(const Kolo & kolo) const
{
	switch (kolo) {
	case prve:
		return pocetZapisanychVolicov_[0];
	case druhe:
		return pocetZapisanychVolicov_[1];
	case obidve:
		return pocetZapisanychVolicov_[0] + pocetZapisanychVolicov_[1];
	default:
		return 0;	
	}
}

unsigned int Oblast::pocetVydanychObalokVKole(const Kolo & kolo) const
{
	switch (kolo) {
	case prve:
		return pocetVydanychObalok_[0];
	case druhe:
		return pocetVydanychObalok_[1];
	case obidve:
		return pocetVydanychObalok_[0] + pocetVydanychObalok_[1];
	default:
		return 0;
	}
}

double Oblast::ucastVolicovVKole(const Kolo & kolo) const
{
	//pocetVydanychObalok * 100 / pocetZapisanychVolicov

	unsigned int pocetVydanychObalok = pocetVydanychObalokVKole(kolo);
	unsigned int pocetZapisanychVolicov = pocetZapisanychVolicovVKole(kolo);

	return static_cast<double>(pocetVydanychObalok) * 100 / pocetZapisanychVolicov;
}

unsigned int Oblast::pocetOdovzdanychObalokVKole(const Kolo & kolo) const
{
	switch (kolo) {
	case prve:
		return pocetOdovzdanychObalok_[0];
	case druhe:
		return pocetOdovzdanychObalok_[1];
	case obidve:
		return pocetOdovzdanychObalok_[0] + pocetOdovzdanychObalok_[1];
	default:
		return 0;
	}
}

unsigned int Oblast::pocetOdovzdanychHlasov(const Kandidat & kandidat, const Kolo & kolo) const
{
	int index = kandidat.getCislo() - 1;
	switch (kolo) {
	case prve:
		return pocetHlasovKandidatov_.get(index, 0);
	case druhe:
		return pocetHlasovKandidatov_.get(index, 1);
	case obidve:
		return pocetHlasovKandidatov_.get(index, 0) + pocetHlasovKandidatov_.get(index, 1);
	default:
		return 0;
	}
}

unsigned int Oblast::pocetZiskanychHlasov(const Kandidat & kandidat, const Kolo & kolo) const
{
	int riadok = kandidat.getCislo() - 1;
	int stlpec = kolo == prve ? 0 : 1;

	return pocetHlasovKandidatov_.get(riadok, stlpec);
}
