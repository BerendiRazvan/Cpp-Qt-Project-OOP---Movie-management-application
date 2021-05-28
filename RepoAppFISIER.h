#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "RepositoryApp.h"

using namespace std;


class RepoFilmeFIS : public RepoFilme {
private:
	string numeFis;

	/*
	Incaraca datele din fiser
	Arunca exceptie de tip RepoFisException daca: fisierul nu se poate deschide sau datele din fisier nu sunt organizate corect
	*/
	void loadData();

	/*
	Scrie datele in fisier
	Arunca exceptie de tip RepoFisException daca: fisierul nu se poate deschide
	*/
	void writeData();

public:
	//operatii clasa
	//Constructor
	RepoFilmeFIS(string numeFis) : RepoFilme(), numeFis{ numeFis } {
		loadData();
	}


	/*
	Adaugare in repoository cu fisiere

	Parametrii:
	const Film& newFilm

	Arunca exceptie daca obiectul exista deja
	*/
	void addFilm(const Film& newFilm) override;

	/*
	Modificare in repository cu fisiere

	Parametrii:
	const Film& newFilm
	*/
	void modificareFilm(const Film& newFilm) override;

	/*
	Sterge din repository cu fisiere

	Parametrii:
	const string& titluFilm
	*/
	void stergereFilm(const string& titluFilm) override;

};

