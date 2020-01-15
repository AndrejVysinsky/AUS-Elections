#pragma once
#include "Oblast.h"
#include "Kolo.h"
#include "Kandidat.h"
#include "Obec.h"
using namespace std;

template <typename T, typename O>
class Kriterium
{
public:
	virtual T ohodnot(const O& object) const = 0;
};

class KriteriumNazov : public Kriterium<string, Oblast> 
{
public:
	string ohodnot(const Oblast& oblast) const override { return oblast.getNazov(); }
};

class KriteriumPrislusnostObce : public Kriterium<bool, Obec> 
{
public:
	bool ohodnot(const Obec& obec) const override { return obec.patriDo(oblast_); }
	void setVyssiCelok(Oblast* vyssiCelok) { oblast_ = vyssiCelok; }
private:
	Oblast* oblast_ = nullptr;
};

class KriteriumVolici : public Kriterium<unsigned int, Oblast> 
{
public:
	unsigned int ohodnot(const Oblast& oblast) const override { return oblast.pocetZapisanychVolicovVKole(kolo_); }
	void setKolo(const Kolo kolo) { kolo_ = kolo; }
private:
	Kolo kolo_ = ziadne;
};

class KriteriumVydaneObalky : public Kriterium<unsigned int, Oblast>
{
public:
	unsigned int ohodnot(const Oblast& oblast) const override { return oblast.pocetVydanychObalokVKole(kolo_); }
	void setKolo(const Kolo& kolo) { kolo_ = kolo; }
private:
	Kolo kolo_ = ziadne;
};

class KriteriumUcast : public Kriterium<double, Oblast>
{
public:
	double ohodnot(const Oblast& oblast) const override { return oblast.ucastVolicovVKole(kolo_); }
	void setKolo(const Kolo& kolo) { kolo_ = kolo; }
private:
	Kolo kolo_ = ziadne;
};

class KriteriumOdovzdaneObalky : public Kriterium<unsigned int, Oblast>
{
public:
	unsigned int ohodnot(const Oblast& oblast) const override { return oblast.pocetOdovzdanychObalokVKole(kolo_); }
	void setKolo(const Kolo& kolo) { kolo_ = kolo; }
private:
	Kolo kolo_ = ziadne;
};

class KriteriumHlasyOdovzdane : public Kriterium<unsigned int, Oblast>
{
public:
	unsigned int ohodnot(const Oblast& oblast) const override { return oblast.pocetOdovzdanychHlasov(*kandidat_, kolo_); }
	void setParametre(Kandidat* kandidat, const Kolo& kolo) { kandidat_ = kandidat; kolo_ = kolo; }
private:
	Kandidat* kandidat_ = nullptr;
	Kolo kolo_ = ziadne;	
};

class KriteriumMeno : public Kriterium<string, Kandidat>
{
public:
	string ohodnot(const Kandidat& kandidat) const override { return kandidat.getMeno(); }
};

class KriteriumHlasyZiskane : public Kriterium<unsigned int, Kandidat>
{
public:
	unsigned int ohodnot(const Kandidat& kandidat) const override { return oblast_->pocetZiskanychHlasov(kandidat, kolo_); }
	void setParametre(const Oblast* oblast, const Kolo& kolo) { oblast_ = oblast; kolo_ = kolo; }
private:
	const Oblast* oblast_ = nullptr;
	Kolo kolo_ = ziadne;
};

class KriteriumHlasyZiskaneKoaliciou : public Kriterium<unsigned int, Oblast>
{
public:
	unsigned int ohodnot(const Oblast& oblast) const override;
	void pridajKandidata(Kandidat* kandidat) { koalicia_.add(kandidat); }
	void setKolo(const Kolo& kolo) { kolo_ = kolo; }
	string toString(const Oblast& oblast);
private:
	ArrayList<Kandidat*> koalicia_;
	Kolo kolo_ = ziadne;
};

inline unsigned int KriteriumHlasyZiskaneKoaliciou::ohodnot(const Oblast& oblast) const
{
	unsigned int sucet = 0;
	KriteriumHlasyZiskane khlasy;
	khlasy.setParametre(&oblast, kolo_);
	for (size_t i = 0; i < koalicia_.size(); i++) {
		sucet += khlasy.ohodnot(*koalicia_[i]);
	}
	return sucet;
}

inline string KriteriumHlasyZiskaneKoaliciou::toString(const Oblast& oblast)
{
	string retazec = to_string(ohodnot(oblast));
	for (size_t i = 0; i < koalicia_.size(); i++) {
		retazec += " " + koalicia_[i]->getMeno();
	}
	return retazec;
}

