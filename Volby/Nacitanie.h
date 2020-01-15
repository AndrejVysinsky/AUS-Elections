#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "structures/table/unsorted_sequence_table.h"
#include "Kraj.h"
#include "Okres.h"
#include "Obec.h"
#include "structures/table/sorted_sequence_table.h"
#include "heap_monitor.h"

using namespace structures;

class Nacitanie
{
public:
	Nacitanie();
	~Nacitanie();
	
	void nacitajOblasti(SortedSequenceTable<int, Oblast*>& kraje, SortedSequenceTable<int, Oblast*>& okresy, SortedSequenceTable<int, Oblast*>& obce);
	void nacitajUdajeOKolach(SortedSequenceTable<int, Oblast*>& obce);
	void nacitajUdajeOKandidatoch(SortedSequenceTable<int, Oblast*>& obce, Array<Kandidat*>& kandidati);
};

