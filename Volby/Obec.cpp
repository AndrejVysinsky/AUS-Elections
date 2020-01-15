#include "Obec.h"
#include <iostream>


Obec::Obec(string nazov, unsigned int kod, Oblast * patriDoKraja, Oblast * patriDoOkresu) : Oblast(nazov, kod, patriDoKraja, patriDoOkresu)
{
}

Obec::~Obec()
{
}

void Obec::pripocitajVolicov(unsigned int pocet, unsigned int kolo)
{
	Oblast::pripocitajVolicov(pocet, kolo);
	patriDoKraja()->pripocitajVolicov(pocet, kolo);
	patriDoOkresu()->pripocitajVolicov(pocet, kolo);
}

void Obec::pripocitajVydaneObalky(unsigned int pocet, unsigned int kolo)
{
	Oblast::pripocitajVydaneObalky(pocet, kolo);
	patriDoKraja()->pripocitajVydaneObalky(pocet, kolo);
	patriDoOkresu()->pripocitajVydaneObalky(pocet, kolo);
}

void Obec::pripocitajOdovzdaneObalky(unsigned int pocet, unsigned int kolo)
{
	Oblast::pripocitajOdovzdaneObalky(pocet, kolo);
	patriDoKraja()->pripocitajOdovzdaneObalky(pocet, kolo);
	patriDoOkresu()->pripocitajOdovzdaneObalky(pocet, kolo);
}

void Obec::pripocitajPlatneHlasy(unsigned int pocet, unsigned int kolo)
{
	Oblast::pripocitajPlatneHlasy(pocet, kolo);
	patriDoKraja()->pripocitajPlatneHlasy(pocet, kolo);
	patriDoOkresu()->pripocitajPlatneHlasy(pocet, kolo);
}

void Obec::pripocitajHlasyKandidatov(unsigned int pocet, unsigned int cisloKandidata, unsigned int kolo)
{
	Oblast::pripocitajHlasyKandidatov(pocet, cisloKandidata, kolo);
	patriDoKraja()->pripocitajHlasyKandidatov(pocet, cisloKandidata, kolo);
	patriDoOkresu()->pripocitajHlasyKandidatov(pocet, cisloKandidata, kolo);
}
