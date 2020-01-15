
#include <string>
#include "Kriterium.h"
#include "Filter.h"
#include "heap_monitor.h"
#include "Kraj.h"
#include "Okres.h"
#include "Nacitanie.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/list/linked_list.h"
#include "Sort.h"
#include "VyberoveKriterium.h"

using namespace std;
using namespace structures;

void naplnOblasti();
void menu();
void funkcionalita13();
template<typename T, typename O, typename K>
void vypisPodlaFiltru(SortedSequenceTable<K, LinkedList<Oblast*>*>& zoznam, Filter<T, O>& filter, Kriterium<T, O>& kriterium, int indexOd, int indexDo);
void vypisInformacieOoblasti(Oblast* oblast);

void funkcionalita24(bool vypisPodlaFiltra);
template<typename K>
void vypisZoznam(SortedSequenceTable<K, LinkedList<Oblast*>*>& zoznam, bool vzostupne, bool vypisPodlaFiltra);

void funkcionalita567(int cisloFunkcionality);
void funkcionalita5(Kandidat* kandidat);
void funkcionalita6(Kandidat* kandidat);
void funkcionalita7(Kandidat* kandidat);

void funkcionalita8();

void vytvorKoaliciu();

void nastavFiltreNazovVoliciUcast();

void destruktor();

SortedSequenceTable<int, Oblast*> kraje;
SortedSequenceTable<int, Oblast*> okresy;
SortedSequenceTable<int, Oblast*> obce;
SortedSequenceTable<int, Oblast*> oblasti;

Array<Kandidat*> kandidati = Array<Kandidat*>(15);
Array<int> cisloKoalicie = Array<int>(15);

Sort usporiadaj = Sort();

KriteriumNazov knazov; KriteriumHlasyOdovzdane khlasyOdovzdane; KriteriumHlasyZiskane khlasyZiskane; KriteriumMeno kmeno;
KriteriumOdovzdaneObalky kodovzdaneObalky; KriteriumPrislusnostObce kprislusnostObce; 
KriteriumUcast kucast; KriteriumVolici kvolici; KriteriumVydaneObalky kvydaneObalky;

FilterVolici fvolici; FilterMeno fmeno; FilterNazov fnazov; FilterPrislusnostObce fprislusnostObce; FilterUcast fucast;

Kolo kolo;

int main(int argc, char* argv[])
{
	initHeapMonitor();
	
	Nacitanie nacitanie = Nacitanie();
	nacitanie.nacitajOblasti(kraje, okresy, obce);
	nacitanie.nacitajUdajeOKolach(obce);
	nacitanie.nacitajUdajeOKandidatoch(obce, kandidati);

	naplnOblasti();
	
	menu();

	destruktor();
	return 0;
}

void naplnOblasti()
{
	for (TableItem<int, Oblast*>* item : kraje)
		oblasti.insert(item->getKey(), item->accessData());
	for (TableItem<int, Oblast*>* item : okresy)
		oblasti.insert(item->getKey(), item->accessData());
	for (TableItem<int, Oblast*>* item : obce)
		oblasti.insert(item->getKey(), item->accessData());
}

void menu()
{
	string retazec;
	int cislo;

	while (true) {
		system("cls");

		cout << "1. Vypisanie informacii o obciach\n";
		cout << "2. Zoradenie obci\n";
		cout << "3. Vypisanie informacii o uzemnych jednotkach\n";
		cout << "4. Zoradenie uzemnych jednotiek splnujucich dany filter\n";
		cout << "5. Vypisanie vysledkov kandidata v uzemnej jednotke\n";
		cout << "6. Zoradenie kandidatov podla vysledkov v uzemnych jednotkach\n";
		cout << "7. Vypisanie vyberovych kriterii\n";
		cout << "8. Zoradenie fiktivnych koalicii\n";
		cout << "9. Vytvor fiktivnu koaliciu\n";
		cout << "0. Ukoncenie programu\n";
		cout << "\n";

		cin >> cislo;

		system("cls");
		switch (cislo) {
		case 1:
			funkcionalita13();
			break;
		case 2:
			funkcionalita24(false);
			break;
		case 3:
			funkcionalita13();
			break;
		case 4:
			funkcionalita24(true);
			break;
		case 5:
			funkcionalita567(5);
			break;
		case 6:
			funkcionalita567(6);
			break;
		case 7:
			funkcionalita567(7);
			break;
		case 8:
			funkcionalita8();
			break;
		case 9:
			vytvorKoaliciu();
			break;
		default:;
		}

		if (cislo == 0)
			break;

		cout << "Pre navrat do menu stlacte enter\n";
		cin.ignore();

	}
}

void funkcionalita13()
{
	cout << "Zvolte filter:\n";
	cout << "1. Filter - nazov\n";
	cout << "2. Filter - volici\n";
	cout << "3. Filter - ucast\n";

	int vstup;
	cin >> vstup;
	
	system("cls");
	if (vstup == 1) {
		cout << "Zadajte nazov obce/uzemnej jednotky\n";
		string nazov;
		cin.ignore();
		getline(cin, nazov);

		fnazov.setFilter(nazov);

		SortedSequenceTable<string, LinkedList<Oblast*>*> nazvy = usporiadaj.kriteriumNazvu(oblasti);
		int indexOd = nazvy.najdiIndexNaVlozenie(nazov, 0, nazvy.size() - 1);
		int indexDo = indexOd;
		vypisPodlaFiltru(nazvy, fnazov, knazov, indexOd, indexDo);
	}
	else if (vstup == 2 || vstup == 3) {
		cout << "Zadajte spodnu a vrchu hranicu\n";
		int alpha, beta;
		cin >> alpha >> beta;

		if (vstup == 2) {
			fvolici.setFilter(alpha, beta);
			kvolici.setKolo(obidve);

			SortedSequenceTable<int, LinkedList<Oblast*>*> volici = usporiadaj.kriteriumVolicov(oblasti, obidve);
			int indexOd = volici.najdiIndexNaVlozenie(alpha, 0, volici.size() - 1);
			int indexDo = volici.najdiIndexNaVlozenie(beta, 0, volici.size() - 1);
			vypisPodlaFiltru(volici, fvolici, kvolici, indexOd, indexDo);
		}
		if (vstup == 3) {
			fucast.setFilter(alpha, beta);
			kucast.setKolo(obidve);

			SortedSequenceTable<double, LinkedList<Oblast*>*> ucast = usporiadaj.kriteriumUcasti(oblasti, obidve);
			int indexOd = ucast.najdiIndexNaVlozenie(alpha, 0, ucast.size() - 1);
			int indexDo = ucast.najdiIndexNaVlozenie(beta, 0, ucast.size() - 1);
			vypisPodlaFiltru(ucast, fucast, kucast, indexOd, indexDo);
		}
		cin.ignore();
	}
	usporiadaj.clear();
	cin.ignore();
}

template<typename T, typename O, typename K>
void vypisPodlaFiltru(SortedSequenceTable<K, LinkedList<Oblast*>*>& zoznam, Filter<T, O>& filter, Kriterium<T, O>& kriterium, int indexOd, int indexDo)
{
	if (indexDo >= zoznam.size())
		indexDo = zoznam.size() - 1;

	for (int i = indexOd; i <= indexDo; i++) {
		LinkedList<Oblast*>* list = zoznam.getItemAtIndex(i).accessData();
		for (Oblast* oblast : *list) {
			if (filter.ohodnot(*oblast, kriterium)) {
				vypisInformacieOoblasti(oblast);
			}
		}
	}
}

void vypisInformacieOoblasti(Oblast * oblast)
{
	kvolici.setKolo(obidve);
	kvydaneObalky.setKolo(obidve);
	kucast.setKolo(obidve);
	kodovzdaneObalky.setKolo(obidve);

	khlasyOdovzdane.setParametre(nullptr, obidve);

	cout << endl;
	cout << knazov.ohodnot(*oblast) << endl;

	Oblast* kraj = oblast->patriDoKraja();
	if (kraj != nullptr)
		cout << "Patri do: " << knazov.ohodnot(*kraj);
	Oblast* okres = oblast->patriDoOkresu();
	if (okres != nullptr) {
		cout << ", " << knazov.ohodnot(*okres) << endl;
	}
	else {
		cout << endl;
	}

	cout << "Volici: " << kvolici.ohodnot(*oblast) << endl;
	cout << "Vydane obalky: " << kvydaneObalky.ohodnot(*oblast) << endl;
	cout << "Ucast: " << kucast.ohodnot(*oblast) << endl;
	cout << "Odovzdane obalky: " << kodovzdaneObalky.ohodnot(*oblast) << endl;

	unsigned int pocetHlasov = 0;
	for (size_t i = 0; i < kandidati.size(); i++) {
		khlasyOdovzdane.setParametre(kandidati[i], obidve);
		pocetHlasov += khlasyOdovzdane.ohodnot(*oblast);
	}
	cout << "Platne hlasy: " << pocetHlasov << endl;
}

void funkcionalita24(bool vypisPodlaFiltra)
{
	cout << "Zvolte filter:\n";
	cout << "1. Kriterium - nazov\n";
	cout << "2. Kriterium - volici\n";
	cout << "3. Kriterium - ucast\n";

	int vstup;
	cin >> vstup;

	system("cls");

	if (vstup != 1 || vypisPodlaFiltra) {
		cout << "Zadajte kolo (1 - prve, 2 - druhe, 3 - obidve):\n";
		int akeKolo;
		cin >> akeKolo;
		kolo = akeKolo == 1 ? prve : akeKolo == 2 ? druhe : obidve;
	}
	
	cout << "Zvolte poradie v ktorom vypisat vysledok:\n";
	cout << "1. vzostupne\n";
	cout << "2. zostupne\n";
	int volba;
	cin >> volba;
	bool vzostupne = volba == 1;

	system("cls");

	if (vstup == 1) {
		SortedSequenceTable<string, LinkedList<Oblast*>*> obcePodlaNazvu = usporiadaj.kriteriumNazvu(obce);
		vypisZoznam(obcePodlaNazvu, vzostupne, vypisPodlaFiltra);
	}
	else if (vstup == 2) {
		SortedSequenceTable<int, LinkedList<Oblast*>*> obcePodlaVolicov = usporiadaj.kriteriumVolicov(obce, kolo);
		vypisZoznam(obcePodlaVolicov, vzostupne, vypisPodlaFiltra);
	}
	else if (vstup == 3) {
		SortedSequenceTable<double, LinkedList<Oblast*>*> obcePodlaUcasti = usporiadaj.kriteriumUcasti(obce, kolo);
		vypisZoznam(obcePodlaUcasti, vzostupne, vypisPodlaFiltra);
	}
	usporiadaj.clear();
	cin.ignore();
	cin.ignore();
}

template<typename K>
void vypisZoznam(SortedSequenceTable<K, LinkedList<Oblast*>*>& zoznam, bool vzostupne, bool vypisPodlaFiltra)
{
	kucast.setKolo(kolo);
	fprislusnostObce.setFilter(true);

	if (vypisPodlaFiltra) {
		cout << "Zadajte interval od, do:\n";
		int alpha, beta;
		cin >> alpha >> beta;
		fucast.setFilter(alpha, beta);

		cout << "Zadajte prislusnost obce:\n";
		string prislusnost;
		cin.ignore();
		getline(cin, prislusnost);

		bool nasiel = false;
		for (TableItem<int, Oblast*>* item : kraje) {
			if (item->accessData()->getNazov() == prislusnost) {
				kprislusnostObce.setVyssiCelok(item->accessData());
				nasiel = true;
			}
		}

		for (TableItem<int, Oblast*>* item : okresy) {
			if (item->accessData()->getNazov() == prislusnost) {
				kprislusnostObce.setVyssiCelok(item->accessData());
				nasiel = true;
			}
		}

		if (!nasiel) {
			cout << "Zadany vyssi celok neexistuje.\n";
			return;
		}
	}

	int i, koniec, krok;
	if (vzostupne) {
		i = 0;
		koniec = zoznam.size();
		krok = 1;
	}
	else {
		i = zoznam.size() - 1;
		koniec = -1;
		krok = -1;
	}

	while (i != koniec) {
		LinkedList<Oblast*>* list = zoznam.getItemAtIndex(i).accessData();
		K kluc = zoznam.getItemAtIndex(i).getKey();
		for (Oblast* obec : *list) {
			if (vypisPodlaFiltra) {
				if (fucast.ohodnot(*obec, kucast) && fprislusnostObce.ohodnot(*dynamic_cast<Obec*>(obec), kprislusnostObce)) {
					cout << "Nazov obce: " << obec->getNazov() << ", hodnota kriteria: " << kluc << endl;
				}
			}
			else {
				cout << "Nazov obce: "  << obec->getNazov() << ", hodnota kriteria: " << kluc << endl;
			}
		}
		i += krok;
	}
}

void funkcionalita567(int cisloFunkcionality) {
	cout << "Zadajte meno kandidata:\n";
	string nazov;
	cin.ignore();
	getline(cin, nazov);
	fmeno.setFilter(nazov);

	Kandidat* kandidat = nullptr;
	for (int i = 0; i < kandidati.size(); i++) {
		if (fmeno.ohodnot(*kandidati[i], kmeno)) {
			kandidat = kandidati[i];
		}
	}

	if (kandidat == nullptr) {
		cout << "Zadany kandidat neexistuje\n";
		return;
	}
	
	nastavFiltreNazovVoliciUcast();

	if (cisloFunkcionality == 5)
		funkcionalita5(kandidat);
	else if (cisloFunkcionality == 6)
		funkcionalita6(kandidat);
	else if (cisloFunkcionality == 7)
		funkcionalita7(kandidat);

	cin.ignore();
	cin.ignore();
}

void funkcionalita5(Kandidat* kandidat) 
{
	kvydaneObalky.setKolo(kolo);
	khlasyOdovzdane.setParametre(kandidat, kolo);
	for (TableItem<int, Oblast*>* item : oblasti) {
		Oblast* oblast = item->accessData();
		if (fnazov.ohodnot(*oblast, knazov) && fvolici.ohodnot(*oblast, kvolici) && fucast.ohodnot(*oblast, kucast)) {
			cout << kandidat->getMeno() << " " << oblast->getNazov() << endl;
			cout << kvolici.ohodnot(*oblast) << " " << kvydaneObalky.ohodnot(*oblast) << " " << khlasyOdovzdane.ohodnot(*oblast) << endl;
		}
	}
}

void funkcionalita6(Kandidat* kandidat) 
{
	cout << "1. vzostupne, 2. zostupne\n";
	int volba;
	cin >> volba;
	SortedSequenceTable<int, LinkedList<Oblast*>*> hlasy = usporiadaj.kriteriumZiskanychHlasov(oblasti, kolo, *kandidat);

	int i, koniec, krok;
	if (volba == 1) {
		i = 0;
		koniec = hlasy.size();
		krok = 1;
	}
	else {
		i = hlasy.size() - 1;
		koniec = -1;
		krok = -1;
	}

	while (i != koniec) {
		LinkedList<Oblast*>* list = hlasy.getItemAtIndex(i).accessData();
		int hodnotaKriteria = hlasy.getItemAtIndex(i).getKey();
		for (Oblast* oblast : *list) {
			if (fnazov.ohodnot(*oblast, knazov) && fvolici.ohodnot(*oblast, kvolici) && fucast.ohodnot(*oblast, kucast)) {
				cout << kandidat->getMeno() << " " << oblast->getNazov() << " " << hodnotaKriteria << endl;
			}
		}
		i += krok;
	}
	usporiadaj.clear();
}

void funkcionalita7(Kandidat* kandidat)
{
	VNajviacHlasov najviacHlasov(kandidat);
	VNajmenejHlasov najmenejHlasov(kandidat);
	VNajstabilnejsieVysledky najstabilnejsieVysledky(kandidat);
	
	bool naslo = false;
	for (TableItem<int, Oblast*>* item : oblasti) {
		Oblast* oblast = item->accessData();		

		if (fnazov.ohodnot(*oblast, knazov) && fvolici.ohodnot(*oblast, kvolici) && fucast.ohodnot(*oblast, kucast)) {
			najviacHlasov.ohodnot(oblast, kolo);
			najmenejHlasov.ohodnot(oblast, kolo);
			najstabilnejsieVysledky.ohodnot(oblast);
			naslo = true;
		}
	}
	if (!naslo) {
		cout << "Zadanym filtrom nevyhovuje ziadna oblast.\n";
		return;
	}

	cout << "Meno kandidata: " << kandidat->getMeno() << endl;
	cout << "Najviac hlasov: " << najviacHlasov.toString() << endl;
	cout << "Najmenej hlasov: " << najmenejHlasov.toString() << endl;
	cout << "Najstabilnejsie vysledky: " << najstabilnejsieVysledky.toString() << endl;
}

void funkcionalita8()
{
	cin.ignore();
	nastavFiltreNazovVoliciUcast();

	int cislo;
	cout << "Zadajte cislo koalicie\n";
	cin >> cislo;

	KriteriumHlasyZiskaneKoaliciou khlasyKoalicie;
	khlasyKoalicie.setKolo(kolo);

	for (int i = 0; i < 15; i++) {
		if (cislo == cisloKoalicie[i]) {
			khlasyKoalicie.pridajKandidata(kandidati[i]);
		}
	}
	SortedSequenceTable<int, LinkedList<Oblast*>*> hlasy = usporiadaj.kriteriumZiskanychHlasovKoaliciou(oblasti, khlasyKoalicie);

	cout << "1. vzostupne, 2. zostupne\n";
	int volba;
	cin >> volba;	

	int i, koniec, krok;
	if (volba == 1) {
		i = 0;
		koniec = hlasy.size();
		krok = 1;
	}
	else {
		i = hlasy.size() - 1;
		koniec = -1;
		krok = -1;
	}

	while (i != koniec) {
		LinkedList<Oblast*>* list = hlasy.getItemAtIndex(i).accessData();
		for (Oblast* oblast : *list) {
			if (fnazov.ohodnot(*oblast, knazov) && fvolici.ohodnot(*oblast, kvolici) && fucast.ohodnot(*oblast, kucast)) {
				cout << khlasyKoalicie.toString(*oblast) << endl;
			}
		}
		i += krok;
	}
	usporiadaj.clear();

	cin.ignore();
	cin.ignore();
}

void vytvorKoaliciu()
{
	int max = 0;
	for (int i = 0; i < 15; i++) {
		cout << i + 1 << " " << kandidati[i]->getMeno() << endl;

		if (cisloKoalicie[i] > max)
			max = cisloKoalicie[i];
	}
	int volba = 1;
	cout << "Zadajte subor cisel, ukoncite 0\n";
	
	max += 1;
	cin >> volba;
	while (volba != 0) {		
		cisloKoalicie[volba - 1] = max;
		cin >> volba;
	}
}

void nastavFiltreNazovVoliciUcast() 
{
	string nazov;
	cout << "Zadajte nazov uzemnej jednotky:\n";
	getline(cin, nazov);
	fnazov.setFilter(nazov);

	cout << "Zadajte kolo (1 - prve, 2 - druhe, 3 - obidve):\n";
	int akeKolo;
	cin >> akeKolo;
	kolo = akeKolo == 1 ? prve : akeKolo == 2 ? druhe : obidve;

	int alpha, beta;
	cout << "Zadajte pocet volicov od, do:\n";
	cin >> alpha >> beta;

	fvolici.setFilter(alpha, beta);
	kvolici.setKolo(kolo);

	cout << "Zadajte ucast od, do:\n";
	cin >> alpha >> beta;

	fucast.setFilter(alpha, beta);
	kucast.setKolo(kolo);
}

void destruktor()
{
	for (TableItem<int, Oblast*>* item : kraje)
		delete item->accessData();

	for (TableItem<int, Oblast*>* item : okresy)
		delete item->accessData();

	for (TableItem<int, Oblast*>* item : obce)
		delete item->accessData();

	for (size_t i = 0; i < kandidati.size(); i++)
		delete kandidati[i];
}