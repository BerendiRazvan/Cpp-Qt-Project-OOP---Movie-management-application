#include "CosGuiApp.h"
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qobject.h>
#include <qmessagebox.h>
#include <qlistwidget.h>
#include <qtableview.h>


#include "RepositoryApp.h"
#include "ServiceApp.h"
#include "ErrorsApp.h"
#include "ValidatoriApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"
#include "TestApp.h"
#include "ConsoleApp.h"

void CosGUI::initConnectC() {
    

    QObject::connect(oferta, &QTableWidget::itemSelectionChanged, [&]() {
        qDebug() << "Film selectat";
        QList<QTableWidgetItem*> selectFilm = oferta->selectedItems();

        if (selectFilm.isEmpty()) {
            titlu->setText("");
        }
        else {
            QTableWidgetItem* item = selectFilm.at(0);
            titlu->setText(item->text());

        }



        });


    QObject::connect(btnAaugareC, &QPushButton::clicked, [&]() {

        string newFilm = titlu->text().toStdString();

        const int ok = serv.addInCos(newFilm);
        if (ok == 1)
            qDebug() << "Film adaugat.\n";
        else {
            qDebug() << "Filmul nu exista.\n";
            QMessageBox::information(nullptr, "Info - Adaugare cos ", "Alegeti un film/titlu din lista!");
        }


        updateCos();
        updateOferta();
        });

    QObject::connect(btnBack, &QPushButton::clicked, [&]() {

        updateCos();
        updateOferta();

        /*OpenGUI* mainApp = new OpenGUI(serv);
        mainApp->show();*/


        close();
        });



    QObject::connect(exportare, &QPushButton::clicked, [&]() {
        qDebug() << "Exportare realizata";

        string fisExport = fisier->text().toStdString();

        if (fisExport != "") {

            serv.exportData(fisExport);

        }
        else {
            QMessageBox::information(nullptr, "Export App", "Camp nume fisier gol!");
        }

        fereastraExport->close();

        updateCos();
        updateOferta();
        fisier->setText("");
        });


    QObject::connect(btnExport, &QPushButton::clicked, [&]() {

        QWidget* ferSec = new QWidget;
        fereastraExport = ferSec;

        //fereastra export
        QVBoxLayout* lyFereastra = new QVBoxLayout;


        QLabel* msgE = new QLabel("Introduceti nume fisier:");

        QFont fontN = msgE->font();
        fontN.setPointSize(12);
        fontN.setBold(true);
        msgE->setFont(fontN);

        exportare->setStyleSheet("background: #D0E37C");

        lyFereastra->addWidget(msgE);
        lyFereastra->addWidget(fisier);
        lyFereastra->addWidget(exportare);


        fereastraExport->setLayout(lyFereastra);

        fereastraExport->show();



        updateCos();
        updateOferta();

        });


    QObject::connect(genereaza, &QPushButton::clicked, [&]() {
        qDebug() << "Generare realizata";

        string nrGenerare = nrFilme->text().toStdString();

        if (nrGenerare != "") {
            serv.generareCos(stoi(nrGenerare));
        }
        else {
            QMessageBox::information(nullptr, "Generare App", "Camp cantitate cos gol!");
        }

        fereastraGenerare->close();

        updateCos();
        updateOferta();
        nrFilme->setText("");

        });

    QObject::connect(btnGenerare, &QPushButton::clicked, [&]() {

        QWidget* ferSec = new QWidget;
        fereastraGenerare = ferSec;

        QVBoxLayout* lyFereastra = new QVBoxLayout;


        QLabel* msgE = new QLabel("Introduceti numarul de produse:");

        QFont fontN = msgE->font();
        fontN.setPointSize(12);
        fontN.setBold(true);
        msgE->setFont(fontN);

        genereaza->setStyleSheet("background: #D0E37C");

        lyFereastra->addWidget(msgE);
        lyFereastra->addWidget(nrFilme);
        lyFereastra->addWidget(genereaza);


        fereastraGenerare->setLayout(lyFereastra);

        fereastraGenerare->show();

        updateCos();
        updateOferta();
        });

    QObject::connect(btnGolire, &QPushButton::clicked, [&]() {

        serv.golesteCos();
        qDebug() << "Cosul a fost golit.\n";
        updateCos();
        updateOferta();
        });

}

void CosGUI::updateCos() {
    listaCos->clear();
    listaCos->setRowCount(0);
    QStringList denumire;
    denumire << "Film" << "Cantitate";
    listaCos->setHorizontalHeaderLabels(denumire);

    map<string, int> cos;
    for (auto& f : serv.getCos()) {
        cos.insert(pair<string, int>(f.getTitlu(), 0));
    }

    map<string, int>::iterator itr;

    //parcurgere si incrementare
    for (auto& f : serv.getCos()) {
        for (itr = cos.begin(); itr != cos.end(); ++itr) {
            if (f.getTitlu() == itr->first) {
                itr->second++;
            }
        }
    }

    int i = 0;
    for (itr = cos.begin(); itr != cos.end(); ++itr) {
        QTableWidgetItem* itmT = new QTableWidgetItem(QString::fromStdString(itr->first));
        QTableWidgetItem* itmCant = new QTableWidgetItem(QString::fromStdString(to_string(itr->second)));

        listaCos->setRowCount(i + 1);
        listaCos->setItem(i, 0, itmT);
        listaCos->setItem(i, 1, itmCant);
        i++;

    }

}

void CosGUI::updateOferta() {
    oferta->clear();
    QStringList denumire;
    denumire << "Titlu" << "Gen" << "An" << "Actor";
    oferta->setHorizontalHeaderLabels(denumire);
    int i = 0;
    for (const auto& f : serv.getAllFilms()) {

        QTableWidgetItem* itemTitlu = new QTableWidgetItem(QString::fromStdString(f.getTitlu()));
        QTableWidgetItem* itemGen = new QTableWidgetItem(QString::fromStdString(f.getGen()));
        QTableWidgetItem* itemAn = new QTableWidgetItem(QString::fromStdString(to_string(f.getAn())));
        QTableWidgetItem* itemActor = new QTableWidgetItem(QString::fromStdString(f.getActor()));

        oferta->setRowCount(i + 1);
        oferta->setItem(i, 0, itemTitlu);
        oferta->setItem(i, 1, itemGen);
        oferta->setItem(i, 2, itemAn);
        oferta->setItem(i, 3, itemActor);
        i++;
    }

}

void CosGUI::initGUIC() {
    updateCos();
    updateOferta();
    resize(750, 450);
    QVBoxLayout* lyFereastra = new QVBoxLayout;
    QHBoxLayout* lyCos = new QHBoxLayout;

    setLayout(lyCos);

    QVBoxLayout* lySTANGA = new QVBoxLayout;
    QVBoxLayout* lyDREAPTA = new QVBoxLayout;


    QLabel* mesaj = new QLabel("Cosul dumneavoastra");
    mesaj->setAlignment(Qt::AlignCenter);
    QFont fontN = mesaj->font();
    fontN.setPointSize(15);
    fontN.setBold(true);
    mesaj->setFont(fontN);

    lySTANGA->addWidget(mesaj);
    lySTANGA->addWidget(new QLabel(""));
    lySTANGA->addWidget(btnAaugareC);
    lySTANGA->addWidget(btnGenerare);
    lySTANGA->addWidget(btnGolire);
    lySTANGA->addStretch();
    QHBoxLayout* lyBtnEB = new QHBoxLayout;
    btnBack->setStyleSheet("background: #DA5E5E");
    lyBtnEB->addWidget(btnBack);
    lyBtnEB->addWidget(btnExport);
    lySTANGA->addLayout(lyBtnEB);


    QHBoxLayout* lyListaTitlu = new QHBoxLayout;
    QLabel* cos = new QLabel("Cos");
    cos->setAlignment(Qt::AlignCenter);
    QFont fontC = cos->font();
    fontC.setPointSize(12);
    fontC.setBold(true);
    cos->setFont(fontC);
    QLabel* oF = new QLabel("Filme");
    oF->setAlignment(Qt::AlignCenter);
    QFont fontF = oF->font();
    fontF.setPointSize(12);
    fontF.setBold(true);
    oF->setFont(fontF);
    lyListaTitlu->addWidget(cos);
    lyListaTitlu->addWidget(oF);
    lyDREAPTA->addLayout(lyListaTitlu);

    QHBoxLayout* lyLista = new QHBoxLayout;
    


    lyCos->addLayout(lySTANGA);
    lyCos->addWidget(listaCos);
    lyCos->addWidget(oferta);

    lyFereastra->addLayout(lyCos);
}