#pragma once
#include <iostream>
#include <vector>

//#include "myVectorDinamic.h"
#include "DomainApp.h"
#include "RepoAppLab.h"

using namespace std;


class RepoFilme : public RepoAbstract {
private:
	vector<Film> listaFilme;

public:
	//operatii clasa
	RepoFilme() = default;
	RepoFilme(const RepoFilme& x) = delete;


	/*
	Adauga in repository

	Parametrii:
	const Film& newFilm

	Arunca exceptie daca obiectul exista deja
	*/
	virtual void addFilm(const Film& newFilm) override;

	/*
	Modifica in repository

	Parametrii:
	const Film& newFilm
	*/
	virtual void modificareFilm(const Film& newFilm) override;

	/*
	Sterge din repository

	Parametrii:
	const string& titluFilm

	*/
	virtual void stergereFilm(const string& titluFilm) override;


	/*
	* Returneaza datele din lista stocata in Repository
	*/
	virtual vector<Film>& getAll() noexcept;

};