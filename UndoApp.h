#pragma once
#include <iostream>

#include "DomainApp.h"
#include "RepoAppFISIER.h"
#include "RepositoryApp.h"

using namespace std;


class Actiune {
public:
	//actiune generica
	virtual void actUndo() = 0;

	//destructor actiune
	virtual ~Actiune() {};
};

class UndoAdauga : public Actiune {
	Film filmAdaugat;
	RepoAbstract& repo;

public:
	//constructor
	UndoAdauga(RepoAbstract& repo, const Film& film) :repo{ repo }, filmAdaugat{ film }{}

	//Functie undo pt. adaugare
	void actUndo() override;
};

class UndoSterge : public Actiune {
	Film filmSters;
	RepoAbstract& repo;

public:
	//constructor
	UndoSterge(RepoAbstract& repo, const Film& film) :repo{ repo }, filmSters{ film }{}

	//Functie undo pt. stergere
	void actUndo() override;
};

class UndoModifica : public Actiune {
	Film filmModificat;
	RepoAbstract& repo;

public:
	//constructor
	UndoModifica(RepoAbstract& repo, const Film& film) :repo{ repo }, filmModificat{ film }{}

	//Functie undo pt. modificare
	void actUndo() override;
};

