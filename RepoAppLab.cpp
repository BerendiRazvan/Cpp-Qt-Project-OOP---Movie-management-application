#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

//#include "myVectorDinamic.h"
#include "RepositoryApp.h"
#include "DomainApp.h"
#include "ErrorsApp.h"

using namespace std;


double numarRandom() {

	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, 1000000);
	int randNr = dist(mt);

	double nr = (double)(randNr / 1000000.0);

	return nr;

}



void RepoLab::addFilm(const Film& newFilm) {

	if (probabilitate < numarRandom()) {
		throw RepoException("Probabilitate invalida!");
	}


	map<string, Film>::iterator itr;


	for (itr = listaFilme.begin(); itr != listaFilme.end(); ++itr) {
		if (newFilm.getTitlu() == itr->first) {
			throw RepoException("Film existent!\n");
		}
	}

	listaFilme.insert(pair<string, Film>(newFilm.getTitlu(), newFilm));

}

void RepoLab::modificareFilm(const Film& newFilm) {

	if (probabilitate < numarRandom()) {
		throw RepoException("Probabilitate invalida!");
	}

	int ok = 0;

	map<string, Film>::iterator itr;

	for (itr = listaFilme.begin(); itr != listaFilme.end(); ++itr) {
		if (newFilm.getTitlu() == itr->first) {
			itr->second.setTitlu(newFilm.getTitlu());
			itr->second.setGen(newFilm.getGen());
			itr->second.setAn(newFilm.getAn());
			itr->second.setActor(newFilm.getActor());
			ok = 1;
			break;
		}
	}


	if (ok == 0)
		throw RepoException("Film inexistent!\n");
}

void RepoLab::stergereFilm(const string& titluFilm) {

	if (probabilitate < numarRandom()) {
		throw RepoException("Probabilitate invalida!");
	}

	int ok = 0;

	map<string, Film>::iterator itr;

	for (itr = listaFilme.begin(); itr != listaFilme.end(); ++itr) {
		if (titluFilm == itr->first) {
			ok = 1;
		}
	}

	if (ok == 0)
		throw RepoException("Film inexistent!\n");

	listaFilme.erase(titluFilm);
}



vector<Film>& RepoLab::getAll() {

	convertMapToVector.clear();

	map<string, Film>::iterator itr;

	for (itr = listaFilme.begin(); itr != listaFilme.end(); ++itr) {
		convertMapToVector.push_back(itr->second);
	}

	return convertMapToVector;
}