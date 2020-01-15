#include "Nacitanie.h"

Nacitanie::Nacitanie()
{
}

Nacitanie::~Nacitanie()
{
}

void Nacitanie::nacitajOblasti(SortedSequenceTable<int, Oblast*>& kraje, SortedSequenceTable<int, Oblast*>& okresy, SortedSequenceTable<int, Oblast*>& obce)
{
	ifstream vstup("resources/zoznam_miest.csv");

	string nazovKraja, nazovOkresu, nazovObce;
	int kodKraja, kodOkresu, kodObce;

	string riadok;
	Kraj* kraj = nullptr;
	Okres* okres = nullptr;
	int idKraja = 0, idOkresu = 0;
	while (getline(vstup, riadok)) {
		string temp;
		stringstream textStream(riadok);

		getline(textStream, temp, ';');
		kodKraja = stoi(temp);
		getline(textStream, nazovKraja, ';');

		getline(textStream, temp, ';');
		kodOkresu = stoi(temp);
		getline(textStream, nazovOkresu, ';');

		getline(textStream, temp, ';');
		kodObce = stoi(temp);
		getline(textStream, nazovObce, ';');

		if (idKraja != kodKraja) {
			idKraja = kodKraja;
			kraj = new Kraj(nazovKraja, kodKraja);
			kraje.insert(kodKraja, kraj);
		}

		if (idOkresu != kodOkresu) {
			idOkresu = kodOkresu;
			okres = new Okres(nazovOkresu, kodOkresu, kraj);
			okresy.insert(kodOkresu, okres);
		}

		obce.insert(kodObce, new Obec(nazovObce, kodObce, kraj, okres));

	}
	vstup.close();
}

void Nacitanie::nacitajUdajeOKolach(SortedSequenceTable<int, Oblast*>& obce)
{
	ifstream kolo1("resources/1kolo_obce_usporiadane.csv");
	ifstream kolo2("resources/2kolo_obce_usporiadane.csv");

	int pocetVolicov, pocetVydanychObalok, pocetOdovzdanychObalok, pocetPlatnychHlasov;

	char c;
	int index = 0;
	while (kolo1 >> pocetVolicov >> c >> pocetVydanychObalok >> c >> pocetOdovzdanychObalok >> c >> pocetPlatnychHlasov) {
		Oblast* obec = obce.getItemAtIndex(index++).accessData();

		obec->pripocitajVolicov(pocetVolicov, 1);
		obec->pripocitajVydaneObalky(pocetVydanychObalok, 1);
		obec->pripocitajOdovzdaneObalky(pocetOdovzdanychObalok, 1);
		obec->pripocitajPlatneHlasy(pocetPlatnychHlasov, 1);
	}

	index = 0;
	while (kolo2 >> pocetVolicov >> c >> pocetVydanychObalok >> c >> pocetOdovzdanychObalok >> c >> pocetPlatnychHlasov) {
		Oblast* obec = obce.getItemAtIndex(index++).accessData();

		obec->pripocitajVolicov(pocetVolicov, 2);
		obec->pripocitajVydaneObalky(pocetVydanychObalok, 2);
		obec->pripocitajOdovzdaneObalky(pocetOdovzdanychObalok, 2);
		obec->pripocitajPlatneHlasy(pocetPlatnychHlasov, 2);
	}

	kolo1.close();
	kolo2.close();
}

void Nacitanie::nacitajUdajeOKandidatoch(SortedSequenceTable<int, Oblast*>& obce, Array<Kandidat*>& kandidati)
{
	ifstream zoznam("resources/zoznam_kandidatov.csv");

	int cisloKandidata;
	string meno, priezvisko;


	string riadok;
	while (getline(zoznam, riadok)) {
		string temp;
		stringstream textStream(riadok);

		getline(textStream, temp, ';');
		cisloKandidata = stoi(temp);

		getline(textStream, meno, ';');
		getline(textStream, priezvisko, ';');

		kandidati[cisloKandidata - 1] = new Kandidat(meno + " " + priezvisko, cisloKandidata);
	}
	zoznam.close();

	ifstream kolo1("resources/skuskaKandidatovKolo1.csv");
	ifstream kolo2("resources/skuskaKandidatovKolo2.csv");


	char c;
	int index = 0;
	int pocetHlasov;
	Oblast* obec = nullptr;
	while (kolo1 >> cisloKandidata >> c >> pocetHlasov) {
		if (cisloKandidata == 1)
			obec = obce.getItemAtIndex(index++).accessData();

		obec->pripocitajHlasyKandidatov(pocetHlasov, cisloKandidata, 1);
	}

	index = 0;
	while (kolo2 >> cisloKandidata >> c >> pocetHlasov) {
		if (cisloKandidata == 1)
			obec = obce.getItemAtIndex(index++).accessData();

		obec->pripocitajHlasyKandidatov(pocetHlasov, cisloKandidata, 2);
	}
	kolo1.close();
	kolo2.close();
}
