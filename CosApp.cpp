#include <iostream>
#include <vector>

#include "CosApp.h"
#include "DomainApp.h"

using namespace std;


int CosInchirieri::nrInchirieri() noexcept {
	return listaInchirieri.size();
}


void CosInchirieri::golesteCos() noexcept {
	int lung = listaInchirieri.size();
	while (0 < lung) {
		listaInchirieri.erase(listaInchirieri.begin() + 0);
		lung--;
	}
	notify();
}


void CosInchirieri::adaugaCos(const Film& newFilm) {
	listaInchirieri.push_back(newFilm);
	notify();
}


void CosInchirieri::stergeCos(const string& titluFilm) {
	int i = 0, lung = listaInchirieri.size();
	while (i < lung) {
		if (listaInchirieri[i].getTitlu() == titluFilm) {
			listaInchirieri.erase(listaInchirieri.begin() + i);
			i--;
			lung--;
		}
		i++;
	}
	notify();
}


vector<Film>& CosInchirieri::getCosInchirieri() noexcept {
	return listaInchirieri;
}