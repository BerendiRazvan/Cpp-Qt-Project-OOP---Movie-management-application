#pragma once
#include <iostream>
#include <string>
#include <vector>

//#include "myVectorDinamic.h"
#include "ServiceApp.h"

using namespace std;


class Validare {
public:

	/*
	Valideaza actor

	Parametrii:
	const string& actor

	returneaza 1 - invalid
	returneaza 0 - valid
	*/
	int validareActor(const string& actor) noexcept;

	/*
	Valideaza an

	Parametrii:
	const int& an

	returneaza 1 - invalid
	returneaza 0 - valid
	*/
	int validareAn(const int& an) noexcept;

	/*
	Valideaza gen

	Parametrii:
	const string& gen

	returneaza 1 - invalid
	returneaza 0 - valid
	*/
	int validareGen(const string& gen) noexcept;

	/*
	Valideaza titlu

	Parametrii:
	const vector<Film>& listaFilme,const string& titlu

	returneaza 1 - invalid
	returneaza 0 - valid
	*/
	int validareTitlu(const vector<Film>& listaFilme, const string& titlu);

	/*
	Valideaza dupa toate criteriile

	Parametrii:
	const vector<Film>& listaFilme,const string& titlu,const string& gen,const int& an,const string& actor

	returneaza 1 - invalid
	returneaza 0 - valid
	*/
	int validareAll(const vector<Film>& listaFilme, const string& titlu, const string& gen, const int& an, const string& actor);

};
