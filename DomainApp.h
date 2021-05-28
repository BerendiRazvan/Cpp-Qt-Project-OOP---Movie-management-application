#pragma once
#include <iostream>
#include <string>

using namespace std;


class Film {
private:
	string titluFilm{};
	string genFilm{};
	int anAparitie{};
	string actorPrincipal{};

public:
	//operatii clasa
	Film() = default;
	Film(string titluFilm, string genFilm, int anAparitie, string actorPrincipal) : titluFilm{ titluFilm }, genFilm{ genFilm }, anAparitie{ anAparitie }, actorPrincipal{ actorPrincipal }{}

	//Getter

	/*
	Returneaza titlu
	*/
	string getTitlu() const;

	/*
	Returneaza gen
	*/
	string getGen() const;

	/*
	Returneaza actor
	*/
	string getActor() const;

	/*
	Returneaza an
	*/
	int getAn() const noexcept;

	//Setter

	/*
	Seteaza titlu

	Parametrii:
	const string& titluFilm
	*/
	void setTitlu(const string& titluFilm);

	/*
	Seteaza gen
	Parametrii:
	const string&  genFilm
	*/
	void setGen(const string& genFilm);

	/*
	Seteaza actor

	Parametrii:
	const string& actorPrincipal
	*/
	void setActor(const string& actorPrincipal);

	/*
	Seteaza an

	Parametrii:
	const int& anAparitie
	*/
	void setAn(const int& anAparitie) noexcept;


	//Film(const Film& x) : titluFilm{ x.titluFilm }, genFilm{ x.genFilm }, anAparitie{ x.anAparitie }, actorPrincipal{ x.actorPrincipal }{
	//	//cout << "*";
	//}

};

//class DTO {
//private:
//	int numar;
//	string text;
//public:
//
//	DTO() = default;
//
//	//Constructor DTO
//	DTO(string text, int numar) : text{ text }, numar{ numar }{}
//
//
//	string getText() const;
//
//	int getNumar() const noexcept;
//
//	void setText(const string& tx);
//
//	void setNumar(const int& nr) noexcept;
//
//};