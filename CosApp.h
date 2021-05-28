#pragma once

#include <iostream>
#include <vector>

#include "DomainApp.h"
#include "Observer.h"

class CosInchirieri: public Observable {
private:
	vector<Film> listaInchirieri;

public:
	//operatii clasa
	CosInchirieri() = default;
	CosInchirieri(const CosInchirieri& x) = delete;

	/*
	Returneaza dimensiunea cosului de inchirieri
	*/
	int nrInchirieri() noexcept;

	/*
	Goleste cos
	*/
	void golesteCos() noexcept;

	/*
	Adaugare film in cos
	Parametrii:
	const Film& newFilm
	*/
	void adaugaCos(const Film& newFilm);

	/*
	Sterge film in cos
	Parametrii:
	const string& titluFilm
	*/
	void stergeCos(const string& titluFilm);

	/*
	Returneaza cosul de inchirieri
	*/
	vector<Film>& getCosInchirieri() noexcept;

};