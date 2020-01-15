#pragma once
#include "Oblast.h"

class Okres : public Oblast
{
public:
	Okres(string nazov, unsigned int kod, Oblast* kraj);
	~Okres();
};

