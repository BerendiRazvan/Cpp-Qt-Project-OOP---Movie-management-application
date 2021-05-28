#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qobject.h>
#include <qlistwidget.h>


#include "ServiceApp.h"
#include "CosGuiApp.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include "Observer.h"

class AppGUI:public QWidget{
private:
	//Meniu
	QPushButton* btnTest = new QPushButton("&Testsare aplicatie");
	QPushButton* btnOpen = new QPushButton("&Deschidere");
	QPushButton* btnClose = new QPushButton("&Inchidere");

    ServFilme& serv;
	

    void initGUI();
	void initConnect();

public:
	//operatii clasa
	AppGUI() noexcept = default;
	AppGUI(ServFilme & serv) noexcept : serv{ serv } {
		initGUI();
		initConnect();
	}
	
	AppGUI(const ServFilme & x) = delete;
	
};


class OpenGUI :public QWidget,public Observer {
private:
	//butoane fereastra principala
	QPushButton* btnClose = new QPushButton("&Inchidere");
	QPushButton* btnUndo = new QPushButton("&Undo");
	QPushButton* btnCos = new QPushButton("&Cos");
	QPushButton* btnAdauga = new QPushButton("&Adaugare");
	QPushButton* btnModifica = new QPushButton("&Modificare");
	QPushButton* btnSterge = new QPushButton("&Stergere");
	QPushButton* btnCauta = new QPushButton("&Cautare");
	QPushButton* btnFiltrare = new QPushButton("&Filtrare");
	QPushButton* btnSortare = new QPushButton("&Sortare");
	QPushButton* btnRaport = new QPushButton("&Raport");
	QPushButton* btnVizualizareLista = new QPushButton("&Vizualizare Lista Filme");

	QPushButton* btnGolire = new QPushButton("&Golire cos");
	QPushButton* btnAaugareC = new QPushButton("&Adaugare in cos");
	QPushButton* btnGenerare = new QPushButton("&Generare cos");
	QPushButton* genereaza = new QPushButton("Generare cos");
	QWidget* fereastraGenerare = new QWidget;
	QLineEdit* nrFilme = new QLineEdit;
	
	QPushButton* btnCosCRUDGUI = new QPushButton("&CosCRUDGUI");
	QPushButton* btnCosReadOnlyGUI = new QPushButton("&CosReadOnlyGUI");

	//fereastra sortare
	QLabel* crtMsg = new QLabel("Alegeti criteriu sortare:");
	QPushButton* sortareTitlu = new QPushButton("Titlu");
	QPushButton* sortareAn = new QPushButton("An aparirtie");
	QWidget* fereastraS = new QWidget;

	//fereastra filtrare
	QLabel* crtMsgF = new QLabel("Alegeti criteriu filtrare:");
	QPushButton* filtrareTitlu = new QPushButton("Titlu");
	QPushButton* filtrareActor = new QPushButton("Actor principal");
	QPushButton* filtrareAnGen = new QPushButton("An si gen");
	QPushButton* btnOk = new QPushButton("Ok");
	QWidget* fereastraF = new QWidget;
	QLineEdit* crt1 = new QLineEdit;
	QLineEdit* crt2 = new QLineEdit;
	QLineEdit* dataCrt1 = new QLineEdit;
	QLineEdit* dataCrt2 = new QLineEdit;
	string fltrTitlu = "", fltrActor = "", fltrGen = "", fltrAn = "";
	int fltrCase = -1;
	vector<Film> filtrat;


	//lista + altele
	QListWidget* listaFilme = new QListWidget();

	QLineEdit* titlu = new QLineEdit;
	QLineEdit* gen = new QLineEdit;
	QLineEdit* an = new QLineEdit;
	QLineEdit* actor = new QLineEdit;
	QLineEdit* capacitateCos = new QLineEdit;

	ServFilme& serv;

	
	void initGUIO();
	void initConnectO();
	void updateFilme();
	void updateFilmeFiltrate(const vector<Film>& filtr);
	void update() override { updateFilme();};

public:
	//operatii clasa
	OpenGUI() noexcept = default;
	OpenGUI(ServFilme& serv) noexcept : serv{ serv } {
		updateFilme();
		serv.totCosul().addObserver(this);
		initGUIO();
		initConnectO();
	}
	~OpenGUI() {
		serv.totCosul().removeObserver(this);
	}
	OpenGUI(const ServFilme& x) = delete;

};
