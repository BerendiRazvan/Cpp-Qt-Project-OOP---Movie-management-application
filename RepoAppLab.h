#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "DomainApp.h"
#include "RepositoryApp.h"

using namespace std;


class RepoAbstract {
public:
	virtual void addFilm(const Film& newFilm) = 0;
	virtual void modificareFilm(const Film& newFilm) = 0;
	virtual void stergereFilm(const string& titluFilm) = 0;
	virtual vector<Film>& getAll() = 0;

	virtual ~RepoAbstract() {};

};


class RepoLab :public RepoAbstract {
private:
	double probabilitate;
	map<string, Film> listaFilme;
	vector<Film> convertMapToVector;
public:
	//operatii clasa
	RepoLab() = default;
	RepoLab(double probabilitate) :probabilitate{ probabilitate } {}
	RepoLab(const RepoLab& x) = delete;


	/*
	Adauga in repository

	Parametrii:
	const Film& newFilm

	Arunca exceptie daca obiectul exista deja
	*/
	void addFilm(const Film& newFilm) override;

	/*
	Modifica in repository

	Parametrii:
	const Film& newFilm
	*/
	void modificareFilm(const Film& newFilm) override;

	/*
	Sterge din repository

	Parametrii:
	const string& titluFilm

	*/
	void stergereFilm(const string& titluFilm) override;


	/*
	* Returneaza datele din lista stocata in Repository
	*/
	vector<Film>& getAll() override;

};