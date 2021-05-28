#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

//#include "myVectorDinamic.h"
#include "RepositoryApp.h"
#include "CosApp.h"
#include "DomainApp.h"
#include "ValidatoriApp.h"
#include "UndoApp.h"
#include "RepoAppLab.h"


using std::unique_ptr;
using namespace std;


class ServFilme {
private:
	RepoAbstract& repo;
	CosInchirieri& cos;
	Validare validator;

	vector<unique_ptr<Actiune>> listaAct;

public:

	//operatii clasa
	ServFilme() = default;
	ServFilme(RepoAbstract& repo, CosInchirieri& cos, Validare validator) noexcept :repo{ repo }, cos{ cos }, validator{ validator } {}
	ServFilme(const ServFilme& x) = delete;


	/*
	Adauga film

	Parametrii:
	const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal

	arunca exceptie pt date invalide
	*/
	int addFilmS(const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal);

	/*
	Cauta film din repo

	Parametrii:
	const string& titluFilm

	Returneaza -1 - Film inexistent
	Returneaza pozitieFilm - Film existent
	*/
	int cautareFilmS(const string& titlu);

	/*
	Modifica film din repo

	Parametrii:
	const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal

	arunca exceptie pt date invalide
	*/
	int modificareFilmS(const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal);

	/*
	Sterge film din repo

	Parametrii:
	const string& titluFilm

	Returneaza 1 - Film inexistent
	Returneaza 0 - Film existent
	*/
	int stergereFilmS(const string& titlu);


	//sortari

	/*
	Sortare generala a aplicatiei
	Paramerii:
	-o functie de tip: bool(*maiMicF)(const Film&, const Film&)

	Realizeaza sortarea dupa criteriul din fct. introdusa
	*/
	//void sortareGenerala(bool(*maiMicF)(const Film&, const Film&));

	/*
	Sortare dupa titlu

	Realizeaza sortarea dupa titlu
	*/
	void sortTitlu();

	/*
	Sortare dupa an

	Realizeaza sortarea dupa an
	*/
	void sortAn();

	//filtrari
	/*
	Filtrare generala a aplicatiei
	Paramerii:
	-o functie de tip: function<bool(const Film&)> fct

	Realizeaza filtrarea dupa criteriul din fct. introdusa
	*/
	//vector<Film> filtrareGenerala(function<bool(const Film&)> fct);

	/*
	Filtrare dupa titlu

	Parametrii:
		<const string> text

	Filtrarea sortarea dupa titlu
	*/
	vector<Film> filtruTitlu(const string text);

	/*
	Filtrare dupa actor

	Parametrii:
		<const string> text

	Filtrarea sortarea dupa actor
	*/
	vector<Film> filtruActor(const string text);

	/*
	Filtrare dupa an si gen

	Parametrii:
		<const string> text
		<const int> nr

	Filtrarea sortarea dupa an si gen
	*/
	vector<Film> filtruAnGen(const int nr, const string text);

	/*
	Returneaza lista de filme
	*/
	const vector<Film>& getAllFilms() const noexcept;

	void raportFilme(map<string, int>& raportMap);

	/*
	Returneaza dimensiunea cosului de inchirieri
	*/
	int dimCos() noexcept;


	/*
	Adaugare film in cos
	Parametrii:
	const string text

	Returneaza 1 - adaugare realizata
	Returneaza 0 - adaugare nerealizata
	*/
	int addInCos(const string text);

	/*
	Goleste cos
	*/
	void golesteCos() noexcept;

	/*
	Adaugare un numar dat de filme, alese random, in cos
	Parametrii:
	int nr

	Returneaza 1 - numar negativ, generare imposibila
	Returneaza 0 - generare realizata
	*/
	int generareCos(int nr);

	/*
	Returneaza cosul de inchirieri
	*/
	const vector<Film>& getCos() const noexcept;
	
	//Returneaza referinta la cos
	CosInchirieri& totCosul() { return cos; };

	/*
	Returneaza cosul de inchirieri intr-un fisier dat

	Parametrii:
	const string fis

	*/
	void exportData(const string fis);

	/*
	Functie care realizeaza undo
	Arunca exceptie daca nu mai exista undo
	*/
	void makeUNDO();
};





