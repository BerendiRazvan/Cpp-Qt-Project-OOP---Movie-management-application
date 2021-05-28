#include <QtWidgets/QApplication>

#include "TestApp.h"
#include "ConsoleApp.h"
#include "RepositoryApp.h"
#include "ServiceApp.h"
#include "ValidatoriApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"



void runGui(ServFilme& servFilme, int argc, char* argv[]) {

	//App QT
	QApplication a(argc, argv);

	//GUI App QT
	AppGUI gui{ servFilme };
	gui.show();

	a.exec();
}



int main(int argc, char *argv[])
{

	//Tasks:
	//-inlocuire QLISTWIDGET cu QLISTVIEW



    //Testare
    Tests testeApp{};
    testeApp.runAllTests();

	//Repository FISIER
	RepoFilmeFIS repoFilme{ "DataApp.txt" };

	//Repository Lab
	//RepoLab repoFilme{0.5};

	//Repository LISTA Locala
	//RepoFilme repoFilme{};

	//Filme
	//Film f1{ "The Martian","SF",2015,"Matt Damon" };
	//Film f2{ "Extraction","Actiune",2020,"Chris Hemsworth" };
	//Film f3{ "Bad Boys For Life","Comedie",2020,"Will Smith & Martin Lawrence" };
	//Film f4{ "Ready Player One","SF",2018,"Tye Sheridan" };
	//Film f5{ "Bird Box","Groaza",2018,"Sarah Paulson" };

	//Filme default
	//repoFilme.addFilm(f1);
	//repoFilme.addFilm(f2);
	//repoFilme.addFilm(f3);
	//repoFilme.addFilm(f4);
	//repoFilme.addFilm(f5);


	//Cos Inchirieri
	CosInchirieri cosFilme{};

	//Validatori
	const Validare validator{};

	//Service
	ServFilme servFilme{ repoFilme,cosFilme,validator };
	
	runGui(servFilme,argc,argv);

	return 0;
}
