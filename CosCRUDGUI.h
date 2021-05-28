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
#include "Observer.h"




class CosCRUDGUI :public QWidget, public Observer {
private:
	QPushButton* btnBack = new QPushButton("&Inapoi");
	QPushButton* btnGolire = new QPushButton("&Golire Cos");
	QPushButton* btnGenerare = new QPushButton("&Generare");

	
	int linii = 0, coloane = 2, liniiO = 0, coloaneO = 4;
	QTableWidget* listaCos = new QTableWidget{ linii, coloane };
	QLineEdit* titlu = new QLineEdit;
	QLineEdit* gen = new QLineEdit;
	QLineEdit* an = new QLineEdit;
	QLineEdit* actor = new QLineEdit;

	QWidget* fereastraExport = new QWidget;
	QWidget* fereastraGenerare = new QWidget;
	QPushButton* genereaza = new QPushButton("Generare cos");
	QPushButton* exportare = new QPushButton("Exportare cos");
	QLineEdit* fisier = new QLineEdit;
	QLineEdit* nrFilme = new QLineEdit;

	ServFilme& serv;

	void initGUIC();
	void initConnectC();

	void update() override { updateCos(); };
	void updateCos();

public:
	//operatii clasa
	CosCRUDGUI() noexcept = default;
	CosCRUDGUI(ServFilme& serv) noexcept : serv{ serv } {
		serv.totCosul().addObserver(this);
		initGUIC();
		initConnectC();
	}
	~CosCRUDGUI() {
		serv.totCosul().removeObserver(this);
	}
	CosCRUDGUI(const ServFilme& x) = delete;


};


