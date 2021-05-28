#include <vector>
#include <assert.h>
#include <iostream>
//#include <gsl.h>

#include "TestApp.h"
#include "RepositoryApp.h"
#include "ServiceApp.h"
#include "ErrorsApp.h"
#include "ValidatoriApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"
//#include "myVectorDinamic.h"

using namespace std;


void testDomain() {
	Film f{ "titlu","gen",10,"actor" };

	//teste getteri
	assert(f.getActor() == "actor");
	assert(f.getGen() == "gen");
	assert(f.getTitlu() == "titlu");
	assert(f.getAn() == 10);

	//teste setteri
	f.setActor("nouAct");
	f.setAn(1);
	f.setGen("nouGen");
	f.setTitlu("nouTit");

	assert(f.getActor() == "nouAct");
	assert(f.getGen() == "nouGen");
	assert(f.getTitlu() == "nouTit");
	assert(f.getAn() == 1);

}


void testRepo() {
	RepoFilme repoTest{};

	Film f1{ "film","comedie",2010,"actor principal" };

	try {
		repoTest.modificareFilm(f1);

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	try {
		repoTest.stergereFilm("ana are mere");

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}



	//teste adaugare

	repoTest.addFilm(f1);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "film");

	try {
		repoTest.addFilm(f1);

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


	//teste stergere
	repoTest.stergereFilm(f1.getTitlu());

	assert(repoTest.getAll().size() == 0);

	Film f4{ "Bird Box","SF",2018,"Tye Sheridan" };
	Film f5{ "Bird Box","Groaza",2008,"Sarah Paulson" };


	repoTest.addFilm(f4);

	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Tye Sheridan");
	assert(repoTest.getAll()[0].getAn() == 2018);
	assert(repoTest.getAll()[0].getGen() == "SF");

	//teste modifica
	repoTest.modificareFilm(f5);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Sarah Paulson");
	assert(repoTest.getAll()[0].getAn() == 2008);
	assert(repoTest.getAll()[0].getGen() == "Groaza");

}



void testRepoLab() {
	RepoLab repoTest{ 1 };


	Film f1{ "film","comedie",2010,"actor principal" };

	try {
		repoTest.modificareFilm(f1);

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	try {
		repoTest.stergereFilm("ana are mere");

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}



	//teste adaugare

	repoTest.addFilm(f1);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "film");

	try {
		repoTest.addFilm(f1);

		assert(false);
	}
	catch (RepoException& err) {
		assert(true);
		assert(err.returnError() == "Film existent!\n");
	}


	//teste stergere
	repoTest.stergereFilm(f1.getTitlu());

	assert(repoTest.getAll().size() == 0);

	Film f4{ "Bird Box","SF",2018,"Tye Sheridan" };
	Film f5{ "Bird Box","Groaza",2008,"Sarah Paulson" };


	repoTest.addFilm(f4);

	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Tye Sheridan");
	assert(repoTest.getAll()[0].getAn() == 2018);
	assert(repoTest.getAll()[0].getGen() == "SF");

	//teste modifica
	repoTest.modificareFilm(f5);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Sarah Paulson");
	assert(repoTest.getAll()[0].getAn() == 2008);
	assert(repoTest.getAll()[0].getGen() == "Groaza");

}





void testRepoFis() {
	try {
		RepoFilmeFIS repoTest{ "alabalaportocala12345zkx_FisierInexistent.txt" };
		assert(false);
	}
	catch (RepoFisException) {
		assert(true);
	}

	//stergem continutul din fisier pt. testare
	std::ofstream ofs;
	ofs.open("dataTestFisier.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();



	RepoFilmeFIS repoTest{ "dataTestFisier.txt" };


	Film f1{ "film","comedie",2010,"actor principal" };

	try {
		repoTest.modificareFilm(f1);

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	try {
		repoTest.stergereFilm("ana are mere");

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}



	//teste adaugare

	repoTest.addFilm(f1);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "film");

	try {
		repoTest.addFilm(f1);

		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


	//teste stergere
	repoTest.stergereFilm(f1.getTitlu());

	assert(repoTest.getAll().size() == 0);

	Film f4{ "Bird Box","SF",2018,"Tye Sheridan" };
	Film f5{ "Bird Box","Groaza",2008,"Sarah Paulson" };


	repoTest.addFilm(f4);

	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Tye Sheridan");
	assert(repoTest.getAll()[0].getAn() == 2018);
	assert(repoTest.getAll()[0].getGen() == "SF");

	//teste modifica
	repoTest.modificareFilm(f5);
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.getAll()[0].getTitlu() == "Bird Box");
	assert(repoTest.getAll()[0].getActor() == "Sarah Paulson");
	assert(repoTest.getAll()[0].getAn() == 2008);
	assert(repoTest.getAll()[0].getGen() == "Groaza");


	//stergem continutul din fisier
	std::ofstream ofsAgain;
	ofsAgain.open("dataTestFisier.txt", std::ofstream::out | std::ofstream::trunc);
	ofsAgain.close();

}



void testService() {

	RepoFilme repoFilme{};
	CosInchirieri cosFilme{};

	Validare validator{};

	ServFilme servFilme{ repoFilme,cosFilme,validator };

	//teste adaugare
	assert(servFilme.addFilmS("The Martian", "SF", "2015", "Matt Damon") == 0);
	assert(servFilme.addFilmS("Extraction", "Actiune", "2020", "Chris Hemsworth") == 0);
	assert(servFilme.addFilmS("Bad Boys For Life", "Comedie", "2020", "Will Smith & Martin Lawrence") == 0);
	assert(servFilme.addFilmS("Ready Player One", "SF", "2018", "Tye Sheridan") == 0);
	assert(servFilme.addFilmS("Bird Box", "Groaza", "2018psda", "Sarah Paulson") == 0);


	auto& date = servFilme.getAllFilms();
	assert(date.size() == 5);
	assert(date[0].getTitlu() == "The Martian");
	assert(date[1].getTitlu() == "Extraction");
	assert(date[2].getTitlu() == "Bad Boys For Life");
	assert(date[3].getTitlu() == "Ready Player One");
	assert(date[4].getTitlu() == "Bird Box");

	assert(servFilme.addFilmS("Bird Box", "Groaza", "2018psda", "Sarah Paulson") == 1);
	assert(servFilme.addFilmS("Birdox", "Groaza", "psda", "Sarah Paulson") == 1);
	assert(servFilme.getAllFilms().size() == 5);
	assert(servFilme.addFilmS("", "", "123", "") == 1);
	assert(servFilme.getAllFilms().size() == 5);
	assert(servFilme.addFilmS("asd", "asd", "123", "asd") == 1);
	assert(servFilme.getAllFilms().size() == 5);
	assert(servFilme.addFilmS("asd", "", "2003", "asd") == 1);
	assert(servFilme.getAllFilms().size() == 5);
	assert(servFilme.addFilmS("", "asd", "2003", "asd") == 1);
	assert(servFilme.getAllFilms().size() == 5);

	//teste cautare
	assert(servFilme.cautareFilmS("Bird Box") == 4);
	assert(servFilme.cautareFilmS("brd") == -1);

	//teste modificare
	auto& date2 = servFilme.getAllFilms();
	assert(servFilme.modificareFilmS("Bird Box", "Groazaaaa", "2000", "Sarah-Paulson") == 0);
	assert(date2[4].getTitlu() == "Bird Box");
	assert(date2[4].getAn() == 2000);
	assert(date2[4].getGen() == "Groazaaaa");
	assert(date2[4].getActor() == "Sarah-Paulson");
	assert(servFilme.modificareFilmS("Bird sox", "Groazaaaa", "2000", "Sarah-Paulson") == 1);
	assert(servFilme.modificareFilmS("Bird Box", "Groazaaaa", "dasadas", "Sarah-Paulson") == 1);
	assert(servFilme.modificareFilmS("Bird Box", "Groazaaaa", "10", "Sarah-Paulson") == 1);

	//teste stergere
	assert(servFilme.stergereFilmS("Bird Box") == 0);
	assert(servFilme.getAllFilms().size() == 4);
	assert(servFilme.stergereFilmS("The Martian") == 0);
	assert(servFilme.getAllFilms().size() == 3);
	assert(servFilme.stergereFilmS("The") == 1);
	assert(servFilme.getAllFilms().size() == 3);

	//teste sortare
	servFilme.sortAn();
	servFilme.sortTitlu();


	//teste filtrare
	assert(servFilme.filtruActor("Chris Hemsworth").size() == 1);
	assert(servFilme.filtruTitlu("Extraction").size() == 1);
	assert(servFilme.filtruAnGen(2000, "SF").size() == 1);


	//teste undo

	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();
	servFilme.makeUNDO();

	auto& dateU = servFilme.getAllFilms();
	assert(dateU.size() == 0);

	try {
		servFilme.makeUNDO();
		assert(false);
	}
	catch (ServException& err) {
		assert(true);
		assert(err.returnError() == "Nu se mai poate efectua undo!\n");
	}


	try {
		RepoLab repoFilme2{ 0 };
		CosInchirieri cosFilme2{};

		Validare validator2{};

		ServFilme servFilme2{ repoFilme2,cosFilme2,validator2 };

		servFilme2.addFilmS("The Martian", "SF", "2015", "Matt Damon");
		assert(false);
	}
	catch (ServException& err) {
		assert(true);
		assert(err.returnError() == "Probabilitate invalida!");
	}



}


void testareCos() {
	RepoFilme repoFilme{};
	CosInchirieri cosFilme{};

	Validare validator{};

	ServFilme servFilme{ repoFilme,cosFilme,validator };

	//teste adaugare
	assert(servFilme.addFilmS("The Martian", "SF", "2015", "Matt Damon") == 0);
	assert(servFilme.addFilmS("Extraction", "Actiune", "2020", "Chris Hemsworth") == 0);
	assert(servFilme.addFilmS("Bad Boys For Life", "Comedie", "2020", "Will Smith & Martin Lawrence") == 0);
	assert(servFilme.addFilmS("Ready Player One", "SF", "2018", "Tye Sheridan") == 0);
	assert(servFilme.addFilmS("Bird Box", "Groaza", "2018psda", "Sarah Paulson") == 0);


	//generere random cos
	assert(servFilme.generareCos(-50) == 1);
	assert(servFilme.generareCos(2) == 0);
	assert(servFilme.dimCos() == 2);

	servFilme.exportData("testCosAppExtract");

	//golire cos
	servFilme.golesteCos();
	assert(servFilme.dimCos() == 0);

	assert(servFilme.addInCos("The Martianaaa") == 0);
	assert(servFilme.addInCos("The Martian") == 1);
	assert(servFilme.dimCos() == 1);
	assert(servFilme.getCos()[0].getTitlu() == "The Martian");

	cosFilme.stergeCos("The Martian");
	assert(servFilme.dimCos() == 0);

	servFilme.exportData("testCosAppExtract");

	//testare raport
	map<string, int> raportMap;
	servFilme.raportFilme(raportMap);
	assert(raportMap.size() == 4);

}



/*
void testVectorDinamic() {
	myVector<int> vectTest;
	vectTest.push(0);
	vectTest.push(1);
	vectTest.push(2);
	vectTest.push(3);
	vectTest.push(4);
	vectTest.push(5);
	vectTest.push(6);
	vectTest.push(7);
	vectTest.push(8);
	vectTest.push(9);
	vectTest.push(10);
	vectTest.push(11);

	assert(vectTest[2] == 2);

	assert(vectTest.size() == 12);

	vectTest.erase(10);

	try {
		vectTest.erase(20);

		assert(false);
	}
	catch (exception) {
		assert(true);
	}


	try {
		int k;
		k = vectTest[20];

		assert(false);
	}
	catch (exception) {
		assert(true);
	}

	assert(vectTest.size() == 11);
}
*/

void Tests::runAllTests() {

	//testVectorDinamic();
	testDomain();
	testRepo();
	testRepoLab();
	testRepoFis();
	testService();//+testValidatori
	testareCos();//+testeService

	//cout << "\n - All tests passed - " << endl;
}