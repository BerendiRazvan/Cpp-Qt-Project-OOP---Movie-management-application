#include <iostream>
#include <fstream>

#include "RepoAppFISIER.h"
#include "ErrorsApp.h"

using namespace std;


void RepoFilmeFIS::loadData() {

	ifstream in(numeFis);
	if (!in.is_open())
		throw RepoFisException("Imposibil de deschis fisierul " + numeFis);

	while (!in.eof()) {

		string titlu, anf, actor, gen;

		if (in.eof()) break;
		getline(in, titlu, ';');

		if (in.eof()) break;
		getline(in, gen, ';');

		if (in.eof()) break;
		getline(in, anf, ';');

		if (in.eof()) break;
		getline(in, actor, '\n');


		int an;
		an = stoi(anf);


		Film newf{ titlu,gen,an,actor };

		RepoFilme::addFilm(newf); //adaugare film

	}

	in.close();
}


void RepoFilmeFIS::writeData() {
	ofstream out(numeFis);
	if (!out.is_open())
		throw RepoFisException("Imposibil de deschis fisierul " + numeFis);

	for (auto& f : getAll()) {
		out << f.getTitlu() << ";";
		out << f.getGen() << ";";
		out << f.getAn() << ";";
		out << f.getActor() << endl;
	}

	out.close();
}


void RepoFilmeFIS::addFilm(const Film& newFilm) {
	RepoFilme::addFilm(newFilm);
	writeData();
}

void RepoFilmeFIS::modificareFilm(const Film& newFilm) {
	RepoFilme::modificareFilm(newFilm);
	writeData();
}

void RepoFilmeFIS::stergereFilm(const string& titluFilm) {
	RepoFilme::stergereFilm(titluFilm);
	writeData();
}