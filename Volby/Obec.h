#pragma once
#include "Oblast.h"

class Obec : public Oblast
{
public:
	Obec(string nazov, unsigned int kod, Oblast* patriDoKraja, Oblast* patriDoOkresu);
	~Obec();
	
	bool patriDo(Oblast* oblast) const { return patriDoOkresu() == oblast || patriDoKraja() == oblast; }

	void pripocitajVolicov(unsigned int pocet, unsigned int kolo) override;
	void pripocitajVydaneObalky(unsigned int pocet, unsigned int kolo) override;
	void pripocitajOdovzdaneObalky(unsigned int pocet, unsigned int kolo) override;
	void pripocitajPlatneHlasy(unsigned int pocet, unsigned int kolo) override;	
	void pripocitajHlasyKandidatov(unsigned int pocet, unsigned int cisloKandidata, unsigned int kolo) override;
};

