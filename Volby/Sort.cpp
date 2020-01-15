#include "Sort.h"

Sort::Sort()
{
}

Sort::~Sort()
{
	clear();
}

void Sort::clear()
{
	for (TableItem<string, LinkedList<Oblast*>*>* item : nazvy_) {
		delete item->accessData();
	}
	for (TableItem<int, LinkedList<Oblast*>*>* item : volici_) {
		delete item->accessData();
	}
	for (TableItem<double, LinkedList<Oblast*>*>* item : ucast_) {
		delete item->accessData();
	}
	for (TableItem<int, LinkedList<Oblast*>*>* item : hlasyKandidata_) {
		delete item->accessData();
	}
	nazvy_.clear();
	volici_.clear();
	ucast_.clear();
	hlasyKandidata_.clear();
}

SortedSequenceTable<string, LinkedList<Oblast*>*>& Sort::kriteriumNazvu(SortedSequenceTable<int, Oblast*>& obce)
{
	for (size_t i = 0; i < obce.size(); i++) {		
		Oblast* obec = obce.getItemAtIndex(i).accessData();
		string kluc = obec->getNazov();

		LinkedList<Oblast*>* data = nullptr;
		nazvy_.tryFind(kluc, data);

		if (data == nullptr) {
			data = new LinkedList<Oblast*>();
			data->add(obec);
			nazvy_.insert(kluc, data);
		}
		else {
			data->add(obec);
		}
	}
	return nazvy_;
}

SortedSequenceTable<int, LinkedList<Oblast*>*>& Sort::kriteriumVolicov(SortedSequenceTable<int, Oblast*>& obce, const Kolo & kolo)
{
	Array<int> volici(obce.size());
	int index = 0;
	for (TableItem<int, Oblast*>* item : obce) {
		volici[index++] = item->accessData()->pocetZapisanychVolicovVKole(kolo);
	}
	usporiadajPodlaKriteria(obce, volici_, volici);
	return volici_;
}

SortedSequenceTable<double, LinkedList<Oblast*>*>& Sort::kriteriumUcasti(SortedSequenceTable<int, Oblast*>& obce, const Kolo & kolo)
{
	Array<double> ucast(obce.size());
	int index = 0;
	for (TableItem<int, Oblast*>* item : obce) {
		ucast[index++] = item->accessData()->ucastVolicovVKole(kolo);
	}
	usporiadajPodlaKriteria(obce, ucast_, ucast);
	return ucast_;
}

SortedSequenceTable<int, LinkedList<Oblast*>*>& Sort::kriteriumZiskanychHlasov(SortedSequenceTable<int, Oblast*>& oblasti, const Kolo & kolo, const Kandidat & kandidat)
{
	KriteriumHlasyZiskane khlasy;

	for (size_t i = 0; i < oblasti.size(); i++) {
		Oblast* oblast = oblasti.getItemAtIndex(i).accessData();

		khlasy.setParametre(oblast, kolo);
		int kluc = khlasy.ohodnot(kandidat);

		LinkedList<Oblast*>* data = nullptr;
		hlasyKandidata_.tryFind(kluc, data);

		if (data == nullptr) {
			data = new LinkedList<Oblast*>();
			data->add(oblast);
			hlasyKandidata_.insert(kluc, data);
		}
		else {
			data->add(oblast);
		}
	}
	return hlasyKandidata_;
}

SortedSequenceTable<int, LinkedList<Oblast*>*>& Sort::kriteriumZiskanychHlasovKoaliciou(SortedSequenceTable<int, Oblast*>& oblasti, KriteriumHlasyZiskaneKoaliciou & khlasyKoalicie)
{
	for (size_t i = 0; i < oblasti.size(); i++) {
		Oblast* oblast = oblasti.getItemAtIndex(i).accessData();
		int kluc = khlasyKoalicie.ohodnot(*oblast);

		LinkedList<Oblast*>* data = nullptr;
		hlasyKandidata_.tryFind(kluc, data);

		if (data == nullptr) {
			data = new LinkedList<Oblast*>();
			data->add(oblast);
			hlasyKandidata_.insert(kluc, data);
		}
		else {
			data->add(oblast);
		}
	}
	return hlasyKandidata_;
}
