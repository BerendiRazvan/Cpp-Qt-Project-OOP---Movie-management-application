#include <iostream>
#include <string>
#include <vector>

//#include "myVectorDinamic.h"
#include "RepositoryApp.h"
#include "DomainApp.h"
#include "ErrorsApp.h"

using namespace std;


void RepoFilme::addFilm(const Film& newFilm) {
	for (auto& f : listaFilme) {
		if (f.getTitlu() == newFilm.getTitlu())
			throw RepoException("Film existent!\n");
	}
	listaFilme.push_back(newFilm);
}

void RepoFilme::modificareFilm(const Film& newFilm) {
	int ok = 0;
	for (auto& f : listaFilme) {
		if (f.getTitlu() == newFilm.getTitlu()) {
			f.setTitlu(newFilm.getTitlu());
			f.setGen(newFilm.getGen());
			f.setAn(newFilm.getAn());
			f.setActor(newFilm.getActor());
			ok = 1;
			break;
		}
	}//daca sterg break se acopera si aceasta linie
	if (ok == 0)
		throw RepoException("Film inexistent!\n");
}

void RepoFilme::stergereFilm(const string& titluFilm) {
	int ok = 0;
	int i = 0;

	for (auto& f : listaFilme) {
		if (f.getTitlu() == titluFilm) {
			listaFilme.erase(listaFilme.begin() + i);
			ok = 1;
			break;
		}//daca sterg break se acopera si aceasta linie
		i++;
	}
	if (ok == 0)
		throw RepoException("Film inexistent!\n");
}



vector<Film>& RepoFilme::getAll() noexcept {
	return listaFilme;
}