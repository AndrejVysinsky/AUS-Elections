#pragma once
#include "Kolo.h"
#include "Obec.h"
#include "structures/list/linked_list.h"
#include "structures/table/sorted_sequence_table.h"
#include "heap_monitor.h"
#include "Kriterium.h"


class Sort
{
public:
	Sort();
	~Sort();

	void clear();

	SortedSequenceTable<string, LinkedList<Oblast*>*>& kriteriumNazvu(SortedSequenceTable<int, Oblast*>& obce);
	SortedSequenceTable<int, LinkedList<Oblast*>*>& kriteriumVolicov(SortedSequenceTable<int, Oblast*>& obce, const Kolo& kolo);
	SortedSequenceTable<double, LinkedList<Oblast*>*>& kriteriumUcasti(SortedSequenceTable<int, Oblast*>& obce, const Kolo& kolo);
	SortedSequenceTable<int, LinkedList<Oblast*>*>& kriteriumZiskanychHlasov(SortedSequenceTable<int, Oblast*>& oblasti, const Kolo& kolo, const Kandidat& kandidat);
	SortedSequenceTable<int, LinkedList<Oblast*>*>& kriteriumZiskanychHlasovKoaliciou(SortedSequenceTable<int, Oblast*>& oblasti, KriteriumHlasyZiskaneKoaliciou& khlasyKoalicie);

private:
	template<typename K>
	void usporiadajPodlaKriteria(SortedSequenceTable<int, Oblast*>& obce, SortedSequenceTable<K, LinkedList<Oblast*>*>& tabulka, const Array<K>& kriterium);

	SortedSequenceTable<string, LinkedList<Oblast*>*> nazvy_;
	SortedSequenceTable<int, LinkedList<Oblast*>*> volici_;
	SortedSequenceTable<double, LinkedList<Oblast*>*> ucast_;
	SortedSequenceTable<int, LinkedList<Oblast*>*> hlasyKandidata_;
	SortedSequenceTable<int, LinkedList<Oblast*>*> hlasyKoalicie_;
};

template<typename K>
inline void Sort::usporiadajPodlaKriteria(SortedSequenceTable<int, Oblast*>& obce, SortedSequenceTable<K, LinkedList<Oblast*>*>& tabulka, const Array<K>& kriterium)
{
	for (size_t i = 0; i < obce.size(); i++) {

		K kluc = kriterium[i];
		Oblast* obec = obce.getItemAtIndex(i).accessData();

		LinkedList<Oblast*>* data = nullptr;
		tabulka.tryFind(kluc, data);

		if (data == nullptr) {
			data = new LinkedList<Oblast*>();
			data->add(obec);
			tabulka.insert(kluc, data);
		}
		else {
			data->add(obec);
		}
	}
}
