#include <iostream>
#include <string>
#include "DomainApp.h"

using namespace std;


string Film::getTitlu() const {
	return titluFilm;
}

string Film::getGen() const {
	return genFilm;
}

string Film::getActor() const {
	return actorPrincipal;
}

int Film::getAn() const noexcept {
	return anAparitie;
}


void Film::setTitlu(const string& titluF) {
	titluFilm = titluF;
}

void Film::setGen(const string& genF) {
	genFilm = genF;
}

void Film::setActor(const string& actorP) {
	actorPrincipal = actorP;
}

void Film::setAn(const int& anA) noexcept {
	anAparitie = anA;
}



//-------------DTO-------------


//string DTO::getText() const {
//	return text;
//}
//
//int DTO::getNumar() const noexcept {
//	return numar;
//}
//
//void DTO::setText(const string& tx) {
//	text = tx;
//}
//
//void DTO::setNumar(const int& nr) noexcept {
//	numar = nr;
//}