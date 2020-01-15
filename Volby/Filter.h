#pragma once

#include "Kriterium.h"

template <typename T, typename O>
class Filter
{
public:
	virtual ~Filter() = default;
	virtual bool ohodnot(const O& o, const Kriterium<T, O>& k) = 0;	
};

template <typename T, typename O>
class Filter_fi : public Filter<T, O>
{
public:
	bool ohodnot(const O& o, const Kriterium<T, O>& k) override { return k.ohodnot(o) == alpha_; }
	void setFilter(const T& alpha) { alpha_ = alpha; }
private: 
	T alpha_; // treba settery
};

template <typename T, typename O>
class Filter_FI : public Filter<T, O>
{
public:
	bool ohodnot(const O& o, const Kriterium<T, O>& k) override { T result = k.ohodnot(o); return result >= alpha_ && result <= beta_; }
	void setFilter(const T& alpha, const T& beta) { alpha_ = alpha; beta_ = beta; }
private:
	T alpha_; // treba setter
	T beta_; // treba setter
};

/*
	mozno doplnit ze ked sa vytvori filter automaticky sa vytvori aj kriterium a nastavi sa dany parameter
*/


class FilterNazov : public Filter_fi<string, Oblast> {};
class FilterVolici : public Filter_FI<unsigned int, Oblast> {};
class FilterUcast : public Filter_FI<double, Oblast> {};
class FilterPrislusnostObce : public Filter_fi<bool, Obec> {};
class FilterMeno : public Filter_fi<string, Kandidat> {};