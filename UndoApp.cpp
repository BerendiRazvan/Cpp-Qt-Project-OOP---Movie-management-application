#include <iostream>

#include "UndoApp.h"
#include "RepositoryApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"

using namespace std;


void UndoAdauga::actUndo() {
	repo.stergereFilm(filmAdaugat.getTitlu());
}


void UndoSterge::actUndo() {
	repo.addFilm(filmSters);
}


void UndoModifica::actUndo() {
	repo.modificareFilm(filmModificat);
}