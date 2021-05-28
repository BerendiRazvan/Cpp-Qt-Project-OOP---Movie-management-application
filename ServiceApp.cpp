#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <fstream>
#include <map>
#include <iterator>

#include "ServiceApp.h"
#include "RepositoryApp.h"
#include "DomainApp.h"
#include "ValidatoriApp.h"
#include "ErrorsApp.h"
#include "RepoAppLab.h"

using namespace std;


int ServFilme::addFilmS(const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal) {

	int anAp;
	try {
		anAp = stoi(anAparitie);
	}
	catch (exception&)
	{
		return 1;
	}

	const auto& filme = repo.getAll();
	if (validator.validareAll(filme, titluFilm, genFilm, anAp, actorPrincipal))
		return 1;

	try {
		Film newFilm{ titluFilm,genFilm,anAp,actorPrincipal };
		repo.addFilm(newFilm);

		//pt. undo
		listaAct.push_back(std::make_unique<UndoAdauga>(repo, newFilm));
	}
	catch (RepoException& err) {
		throw ServException(err.returnError());
	}



	return 0;
}

int ServFilme::cautareFilmS(const string& titlu) {
	int i = 0;
	for (const auto& f : repo.getAll()) {
		if (f.getTitlu() == titlu) {
			return i;
		}
		i++;
	}

	return -1;
}

int ServFilme::modificareFilmS(const string& titluFilm, const string& genFilm, const string& anAparitie, const string& actorPrincipal) {

	if (cautareFilmS(titluFilm) == -1)
		return 1;

	int anAp;
	try {
		anAp = stoi(anAparitie);
	}
	catch (exception&)
	{
		return 1;
	}


	if (validator.validareActor(actorPrincipal) == 1 || validator.validareAn(anAp) == 1 || validator.validareGen(genFilm) == 1)//validare
		return 1;

	try {
		Film mFilm;
		for (auto& f : repo.getAll())
			if (f.getTitlu() == titluFilm)
				mFilm = f;

		Film newFilm{ titluFilm,genFilm,anAp,actorPrincipal };
		repo.modificareFilm(newFilm);

		//pt. undo
		listaAct.push_back(std::make_unique<UndoModifica>(repo, mFilm));
	}
	catch (RepoException& err) {
		throw ServException(err.returnError());
	}

	return 0;
}

int ServFilme::stergereFilmS(const string& titlu) {
	if (cautareFilmS(titlu) == -1)
		return 1;

	try {
		Film newFilm;
		for (auto& f : repo.getAll())
			if (f.getTitlu() == titlu)
				newFilm = f;

		repo.stergereFilm(titlu);
		cos.stergeCos(titlu);

		//pt. undo
		listaAct.push_back(std::make_unique<UndoSterge>(repo, newFilm));
	}

	catch (RepoException& err) {
		throw ServException(err.returnError());
	}

	return 0;
}

const vector<Film>& ServFilme::getAllFilms() const noexcept {
	return repo.getAll();
}


//-----------------Sortari&Filtrari---------------------



bool cmpTitlu(const Film& f1, const Film& f2) {
	return f1.getTitlu() < f2.getTitlu();
}

bool cmpAn(const Film& f1, const Film& f2) noexcept {
	return f1.getAn() > f2.getAn();
}



/*
Sorteaza dupa titlu
*/
void ServFilme::sortTitlu() {
	sort(repo.getAll().begin(), repo.getAll().end(), cmpTitlu);
}

/*
Sorteaza dupa an
*/
void ServFilme::sortAn() {
	sort(repo.getAll().begin(), repo.getAll().end(), cmpAn);
}



//vector<Film> ServFilme::filtrareGenerala(function<bool(const Film&)> fct) {
//	vector<Film> filtru;
//	for (auto& f : repo.getAll()) {
//		if (fct(f)) {
//			filtru.push_back(f);
//		}
//	}
//	return filtru;
//}

vector<Film> ServFilme::filtruTitlu(const string text) {
	/*return filtrareGenerala([text](const Film& f) {
		return f.getTitlu() == text;
		});*/

	vector<Film> filtru(repo.getAll().size());
	const vector<Film>& copie{ repo.getAll() };

	auto rez = copy_if(copie.begin(), copie.end(), filtru.begin(), [text](const Film& f) {
		return f.getTitlu() == text;
		});
	filtru.resize(std::distance(filtru.begin(), rez));
	return filtru;

}

vector<Film> ServFilme::filtruActor(const string text) {
	/*return filtrareGenerala([text](const Film& f) {
		return f.getActor() == text;
		});*/

	vector<Film> filtru(repo.getAll().size());
	const vector<Film>& copie{ repo.getAll() };

	auto rez = copy_if(copie.begin(), copie.end(), filtru.begin(), [text](const Film& f) {
		return f.getActor() == text;
		});
	filtru.resize(std::distance(filtru.begin(), rez));
	return filtru;
}


vector<Film> ServFilme::filtruAnGen(const int nr, const string text) {
	/*return filtrareGenerala([=](const Film& f) {
		return f.getGen() == text && f.getAn()>=nr ;
		});*/

	vector<Film> filtru(repo.getAll().size());
	const vector<Film>& copie{ repo.getAll() };

	auto rez = copy_if(copie.begin(), copie.end(), filtru.begin(), [=](const Film& f) {
		return f.getGen() == text && f.getAn() >= nr;
		});
	filtru.resize(std::distance(filtru.begin(), rez));
	return filtru;

}


void ServFilme::raportFilme(map<string, int>& raportMap) {
	//initializare
	for (auto& f : repo.getAll()) {
		raportMap.insert(pair<string, int>(f.getGen(), 0));
	}

	map<string, int>::iterator itr;

	//parcurgere si incrementare
	for (auto& f : repo.getAll()) {
		for (itr = raportMap.begin(); itr != raportMap.end(); ++itr) {
			if (f.getGen() == itr->first) {
				itr->second++;
			}
		}
	}

}



//---------------CosInchirieri---------------------


int ServFilme::dimCos() noexcept {
	return cos.nrInchirieri();
}

int ServFilme::addInCos(const string text) {

	for (auto& film : repo.getAll()) {
		if (film.getTitlu() == text) {
			cos.adaugaCos(film);
			return 1;
		}
	}

	return 0;
}

void ServFilme::golesteCos() noexcept {

	cos.golesteCos();
}

int ServFilme::generareCos(int nr) {

	if (nr < 0 || repo.getAll().size() == 0)
		return 1;

	while (nr) {
		std::mt19937 mt{ std::random_device{}() };
		const std::uniform_int_distribution<> dist(0, repo.getAll().size() - 1);
		const int randNr = dist(mt);// numar aleator intre [0,size-1]
		cos.adaugaCos(repo.getAll()[randNr]);
		nr--;
	}
	
	return 0;

}

const vector<Film>& ServFilme::getCos() const noexcept {
	return cos.getCosInchirieri();
}



//fake tested
void ServFilme::exportData(const string fis) {

	string fisier = fis + ".html";
	//cout << fisier;

	std::ofstream outfile(fisier);

	if (!outfile.is_open())
		throw ServException("Imposibil de deschis fisierul " + fisier + " pentru a scrie in el datele din cos!");

	outfile << "<h2> <b> <pre>" << "Cosul dumneavoastra: " << cos.getCosInchirieri().size() << " filme " << "\n" << "</pre> </b> </h2>";
	if (cos.getCosInchirieri().size() == 0)
		outfile << "<pre> \t-empty-\n </pre>";
	else {
		for (auto& f : cos.getCosInchirieri())
			outfile << "<pre>" << f.getTitlu() << "\n" << "</pre>";
	}

	outfile.close();

}



//---------------Undo---------------------

void ServFilme::makeUNDO() {
	if (listaAct.empty()) {
		throw ServException("Nu se mai poate efectua undo!\n");
	}

	listaAct.back()->actUndo();
	listaAct.pop_back();

}