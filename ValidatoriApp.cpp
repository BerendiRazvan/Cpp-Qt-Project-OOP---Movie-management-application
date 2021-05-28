#include <iostream>
#include <string>
#include <vector>

//#include "myVectorDinamic.h"
#include "ServiceApp.h"
#include "ValidatoriApp.h"

using namespace std;


int Validare::validareActor(const string& actor) noexcept {
	if (actor.size() == 0)
		return 1;
	return 0;
}

int Validare::validareAn(const int& an) noexcept {
	if (an < 1500 || an >2100)
		return 1;
	return 0;
}

int Validare::validareGen(const string& gen)  noexcept {
	if (gen.size() == 0)
		return 1;
	return 0;
}

int Validare::validareTitlu(const vector<Film>& listaFilme, const string& titlu) {
	if (titlu.size() == 0)
		return 1;

	for (auto& f : listaFilme) {
		if (f.getTitlu() == titlu)
			return 1;
	}


	return 0;
}

int Validare::validareAll(const vector<Film>& listaFilme, const string& titlu, const string& gen, const int& an, const string& actor) {
	if (validareActor(actor) == 1 || validareAn(an) == 1 || validareGen(gen) == 1 || validareTitlu(listaFilme, titlu) == 1)
		return 1;
	return 0;
}
