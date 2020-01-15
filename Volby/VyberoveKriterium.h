#pragma once
#include "Kriterium.h"
#include <utility>

class VNajviacHlasov {

public:
	VNajviacHlasov(Kandidat* kandidat) : kandidat_(kandidat) {}
	void ohodnot(Oblast* oblast, const Kolo& kolo);
	string toString();
private:
	KriteriumHlasyZiskane khlasy_;
	Kandidat* kandidat_;
	Oblast* oblast_ = nullptr;
	unsigned int maximum_ = 0;
};

inline void VNajviacHlasov::ohodnot(Oblast* oblast, const Kolo& kolo) {
	khlasy_.setParametre(oblast, kolo);
	if (khlasy_.ohodnot(*kandidat_) >= maximum_) {
		maximum_ = khlasy_.ohodnot(*kandidat_);
		oblast_ = oblast;
	}
}

inline string VNajviacHlasov::toString() {
	string retazec;
	retazec += to_string(maximum_) + " v " + oblast_->getNazov();
	if (oblast_->patriDoOkresu() != nullptr) {
		retazec += ", " + oblast_->patriDoOkresu()->getNazov();
	}
	if (oblast_->patriDoKraja() != nullptr) {
		retazec += ", " + oblast_->patriDoKraja()->getNazov();
	}
	return retazec;
}

class VNajmenejHlasov {

public:
	VNajmenejHlasov(Kandidat* kandidat) : kandidat_(kandidat) {}
	void ohodnot(Oblast* oblast, const Kolo& kolo);
	string toString();
private:
	KriteriumHlasyZiskane khlasy_;
	Kandidat* kandidat_;
	Oblast* oblast_ = nullptr;
	unsigned int minimum_ = 500000;
};

inline void VNajmenejHlasov::ohodnot(Oblast* oblast, const Kolo& kolo) {
	khlasy_.setParametre(oblast, kolo);
	if (khlasy_.ohodnot(*kandidat_) < minimum_) {
		minimum_ = khlasy_.ohodnot(*kandidat_);
		oblast_ = oblast;
	}
}

inline string VNajmenejHlasov::toString() {
	string retazec;
	retazec += to_string(minimum_) + " v " + oblast_->getNazov();
	if (oblast_->patriDoOkresu() != nullptr) {
		retazec += ", " + oblast_->patriDoOkresu()->getNazov();
	}
	if (oblast_->patriDoKraja() != nullptr) {
		retazec += ", " + oblast_->patriDoKraja()->getNazov();
	}
	return retazec;
}

class VNajstabilnejsieVysledky {
public:
	VNajstabilnejsieVysledky(Kandidat* kandidat) : kandidat_(kandidat) {}
	void ohodnot(Oblast* oblast);
	string toString();
private:
	KriteriumHlasyZiskane khlasy_;
	Kandidat* kandidat_;
	Oblast* oblast_ = nullptr;
	int najmensiRozdiel_ = 500000;
};

inline void VNajstabilnejsieVysledky::ohodnot(Oblast* oblast)
{
	khlasy_.setParametre(oblast, prve);
	int prveKolo = khlasy_.ohodnot(*kandidat_);
	khlasy_.setParametre(oblast, druhe);
	int druheKolo = khlasy_.ohodnot(*kandidat_);

	int rozdiel;
	if (prveKolo >= druheKolo)
		rozdiel = prveKolo - druheKolo;
	else
		rozdiel = druheKolo - prveKolo;

	if (rozdiel < najmensiRozdiel_) {
		oblast_ = oblast;
		najmensiRozdiel_ = rozdiel;
	}
}

inline string VNajstabilnejsieVysledky::toString() {
	string retazec;
	retazec += to_string(najmensiRozdiel_) + " v " + oblast_->getNazov();
	if (oblast_->patriDoOkresu() != nullptr) {
		retazec += ", " + oblast_->patriDoOkresu()->getNazov();
	}
	if (oblast_->patriDoKraja() != nullptr) {
		retazec += ", " + oblast_->patriDoKraja()->getNazov();
	}
	return retazec;
}

