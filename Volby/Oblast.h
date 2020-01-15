#pragma once
#include <string>
#include "Kolo.h"
#include "Kandidat.h"
#include "structures/array/array.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/array/matrix.h"

using namespace std;
using namespace structures;

class Oblast
{
public:
	Oblast(string nazov, unsigned int kod, Oblast* patriDoKraja = nullptr, Oblast* patriDoOkresu = nullptr);
	virtual ~Oblast() = default;

	virtual bool maNizsieCelky() const { return true; }

	unsigned int pocetZapisanychVolicovVKole(const Kolo& kolo) const;
	unsigned int pocetVydanychObalokVKole(const Kolo& kolo) const;
	double ucastVolicovVKole(const Kolo& kolo) const;
	unsigned int pocetOdovzdanychObalokVKole(const Kolo& kolo) const;

	unsigned int pocetOdovzdanychHlasov(const Kandidat& kandidat, const Kolo& kolo) const;
	unsigned int pocetZiskanychHlasov(const Kandidat& kandidat, const Kolo& kolo) const;

	string getNazov() const { return nazov_; }
	unsigned int getKodOblasti() const { return kodOblasti_; }

	virtual void pripocitajVolicov(unsigned int pocet, unsigned int kolo) { pocetZapisanychVolicov_[kolo - 1] += pocet; }
	virtual void pripocitajVydaneObalky(unsigned int pocet, unsigned int kolo) { pocetVydanychObalok_[kolo - 1] += pocet; }
	virtual void pripocitajOdovzdaneObalky(unsigned int pocet, unsigned int kolo) { pocetOdovzdanychObalok_[kolo - 1] += pocet; }
	virtual void pripocitajPlatneHlasy(unsigned int pocet, unsigned int kolo) { pocetPlatnychHlasov_[kolo - 1] += pocet; }
	virtual void pripocitajHlasyKandidatov(unsigned int pocet, unsigned int cisloKandidata, unsigned int kolo) { pocetHlasovKandidatov_.get(cisloKandidata - 1, kolo - 1) += pocet; }
	
	Oblast* patriDoKraja() const { return patriDoKraja_; }
	Oblast* patriDoOkresu() const { return patriDoOkresu_; }	

private:
	string nazov_;

	Array<unsigned int> pocetZapisanychVolicov_ = Array<unsigned int>(2);
	Array<unsigned int> pocetVydanychObalok_ = Array<unsigned int>(2);
	Array<unsigned int> pocetOdovzdanychObalok_ = Array<unsigned int>(2);
	Array<unsigned int> pocetPlatnychHlasov_ = Array<unsigned int>(2);

	Matrix<unsigned int> pocetHlasovKandidatov_ = Matrix<unsigned int>(15, 2);

	Oblast* patriDoKraja_ = nullptr;
	Oblast* patriDoOkresu_ = nullptr;

	unsigned int kodOblasti_;
};

