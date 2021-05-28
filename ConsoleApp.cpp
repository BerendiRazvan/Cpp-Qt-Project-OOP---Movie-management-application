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
#include <qcoreapplication.h>

#include "RepositoryApp.h"
#include "ServiceApp.h"
#include "ErrorsApp.h"
#include "ValidatoriApp.h"
#include "RepoAppFISIER.h"
#include "RepoAppLab.h"
#include "TestApp.h"
#include "ConsoleApp.h"



void AppGUI::initConnect() {

    QObject::connect(btnTest, &QPushButton::clicked, [&]() {
        qDebug() << "Aplicatie testata";
        try {
            Tests testeApp{};
            testeApp.runAllTests();
            QMessageBox::information(nullptr, "Info - TEST", " - Toate testele trecute - ");
        }
        catch (...) {
            QMessageBox::information(nullptr, "Info - TEST", " - Testele nu au fost trecute - ");
        }
     
        });


    QObject::connect(btnOpen, &QPushButton::clicked, [&]() {
        qDebug() << "Aplicatie deschisa";
        try {
            Tests testeApp{};
            testeApp.runAllTests();
            qDebug() << "Teste trecute! Utilizare placuta.";
            OpenGUI* mainApp=new OpenGUI(serv);
            mainApp->show();
            close();
            
        }
        catch (exception&) {
            QMessageBox::information(nullptr, "App - Error", " - Testele esuate - ");
            qDebug() << "- Testele esuate -";
        }

        });



    QObject::connect(btnClose, &QPushButton::clicked, [&]() {
        qDebug() << "Aplicatie inchisa";
        close();
        QMessageBox::information(nullptr,"Info - APP", " - Aplicatie inchisa -\n \n      La revedere! ");
        });
}



void AppGUI::initGUI() {

    resize(750, 450);

    QVBoxLayout* lyMain = new QVBoxLayout;
    QVBoxLayout* lyDate = new QVBoxLayout;

    setLayout(lyMain);

    QLabel* appName = new QLabel("- Aplicatie Inchiriere Filme -");
    appName->setAlignment(Qt::AlignCenter);
    QFont fontN = appName->font();
    fontN.setPointSize(17);
    fontN.setBold(true);
    appName->setFont(fontN);

    
    QLabel* labName = new QLabel(" Laboratorul 10-14 ");
    labName->setAlignment(Qt::AlignCenter);
    QFont fontL = labName->font();
    fontL.setPointSize(12);
    labName->setFont(fontL);

    lyDate->setAlignment(Qt::AlignCenter);
    lyDate->addStretch();
    lyDate->addWidget(appName);
    lyDate->addWidget(labName);
    lyDate->addStretch();


    btnTest->setStyleSheet("background: #A3A3A3");
    btnOpen->setStyleSheet("background: #D0E37C");
    btnClose->setStyleSheet("background: #DA5E5E");

    
    lyDate->setAlignment(Qt::AlignCenter);
    lyDate->addWidget(btnTest);
    lyDate->addWidget(btnOpen);
    lyDate->addWidget(btnClose);
    lyDate->addStretch();
    
    lyMain->setAlignment(Qt::AlignCenter);
    lyMain->addLayout(lyDate);

}


void OpenGUI::updateFilme() {
    listaFilme->clear();
    for (const auto& f : serv.getAllFilms()) {

        string film = f.getTitlu() + " - " + f.getGen() + " - " + to_string(f.getAn()) + " - " + f.getActor();
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film));
        item->setData(Qt::UserRole, QString::fromStdString(f.getTitlu()));

        listaFilme->addItem(item);
        
    }
    string cap = "Aveti " + to_string(serv.getCos().size()) + " filme in cos";

    capacitateCos->setText(QString::fromStdString(cap));

}


void OpenGUI::updateFilmeFiltrate(const vector<Film>& filtr) {
    qDebug() << "Colorare filme";
    for (auto& f : filtr) qDebug() << QString::fromStdString(f.getTitlu());
    int n=listaFilme->count();
    for (int i = 0; i < n; i++) {
        for (auto& f : filtr) {
            if (f.getTitlu() == listaFilme->item(i)->data(Qt::UserRole).toString().toStdString())
                listaFilme->item(i)->setBackground(Qt::yellow);
        }
    }

}


void OpenGUI::initConnectO() {


    QObject::connect(listaFilme, &QListWidget::itemSelectionChanged, [&]() {
        qDebug() << "Film selectat";
        QList<QListWidgetItem*> selectFilm = listaFilme->selectedItems();

        if (selectFilm.isEmpty()) {
            titlu->setText("");
        }
        else {
            QListWidgetItem* item = selectFilm.at(0);
            titlu->setText(item->text());

        }



        });
    QObject::connect(btnVizualizareLista, &QPushButton::clicked, [&]() {
        listaFilme->clear();
        updateFilme();
        });


    QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
        
        string titluF = titlu->text().toStdString();
        string genF = gen->text().toStdString();
        string anF = an->text().toStdString();
        string actorF = actor->text().toStdString();
       
        try {
            const auto& ok = serv.addFilmS(titluF, genF, anF, actorF);
            if (ok == 0)
                qDebug() << "Adaugare realizata cu succes.\n";
            else {
                QMessageBox::information(nullptr, "Info - Adaugare", "Date invalide! Adaugare nerealizata.");
                qDebug() << "Date invalide! Adaugare nerealizata.\n";
            }
        }
        catch (ServException& err) {
            qDebug() << QString::fromStdString(err.returnError());
        }

        updateFilme();

        });

    QObject::connect(listaFilme, &QListWidget::itemSelectionChanged, [&]() {
        
        qDebug() << "Film selectat";
        auto selectFilm = listaFilme->selectedItems();
        if (selectFilm.isEmpty()) {
            titlu->setText("");
            gen->setText("");
            an->setText("");
            actor->setText("");
        }
        else {
            auto selectedF = selectFilm.at(0);
            titlu->setText(selectedF->data(Qt::UserRole).toString());
            
            int i = serv.cautareFilmS(selectedF->data(Qt::UserRole).toString().toStdString());
            auto& film = serv.getAllFilms();

            gen->setText(QString::fromStdString(film[i].getGen()));
            
            an->setText(QString::fromStdString(to_string(film[i].getAn())));
            
            actor->setText(QString::fromStdString(film[i].getActor()));

        }
        });


    QObject::connect(btnModifica, &QPushButton::clicked, [&]() {

        string titluF = titlu->text().toStdString();
        string genF = gen->text().toStdString();
        string anF = an->text().toStdString();
        string actorF = actor->text().toStdString();

        try {
            const auto& ok = serv.modificareFilmS(titluF, genF, anF, actorF);
            if (ok == 0)
                qDebug() << "Modificare realizata cu succes.\n";
            else {
                QMessageBox::information(nullptr, "Info - Modificare", "Date invalide! Modificare nerealizata.");
                qDebug() << "Date invalide! Modificare nerealizata.\n";
            }
        }
        catch (ServException& err) {
            qDebug() << QString::fromStdString(err.returnError());
        }

        updateFilme();

        });


    QObject::connect(btnSterge, &QPushButton::clicked, [&]() {

        string titluF = titlu->text().toStdString();
        

        try {
            const auto& ok = serv.stergereFilmS(titluF);
            if (ok == 0)
                qDebug() << "Stergere realizata cu succes.\n";
            else {
                QMessageBox::information(nullptr, "Info - Stergere", "Date invalide! Stergere nerealizata.");
                qDebug() << "Date invalide! Stergere nerealizata.\n";
            }
        }
        catch (ServException& err) {
            qDebug() << QString::fromStdString(err.returnError());
        }

        updateFilme();

        });

    QObject::connect(btnCauta, &QPushButton::clicked, [&]() {

        string titluF = titlu->text().toStdString();


        const int i = serv.cautareFilmS(titluF);
        if (i != -1) {
            qDebug() << "Filmul gasit.\n";
            string film= serv.getAllFilms()[i].getTitlu() + " - " + serv.getAllFilms()[i].getGen() + " - " + to_string(serv.getAllFilms()[i].getAn()) + " - " + serv.getAllFilms()[i].getActor();
            //afisare film daca e gasit
            QMessageBox::information(nullptr, "Info - Cautare", QString::fromStdString(film));

        }
        else {
            QMessageBox::information(nullptr, "Info - Cautare", "Film inexistent.");
            qDebug() << "Film inexistent.\n";
        }

        

        });


    QObject::connect(btnCos, &QPushButton::clicked, [&]() {
        CosGUI* cos1 = new CosGUI(serv);

        qDebug() << "Cos deschis";
        cos1->show();
        
        
        //close();
        });



    QObject::connect(btnCosCRUDGUI, &QPushButton::clicked, [&]() {

        CosCRUDGUI* cos2 = new CosCRUDGUI(serv);

        qDebug() << "Cos deschis";

        cos2->show();


        //close();
        });

    QObject::connect(btnCosReadOnlyGUI, &QPushButton::clicked, [&]() {
        CosReadOnlyGUI* cos = new CosReadOnlyGUI(serv);

        qDebug() << "Cos deschis";

        cos->show();

        //close();
        });


    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            serv.makeUNDO();
            qDebug() << "Undo realizat.\n";
        }
        catch (ServException& err) {
            qDebug() << QString::fromStdString(err.returnError());
            QMessageBox::information(nullptr, "Info - Undo", QString::fromStdString(err.returnError()));
        }

        updateFilme();

        });

    QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
        string raport;
        qDebug() << "Raport generat";

        map<string, int> raportMap;

        serv.raportFilme(raportMap);

        //afisare rezultat
        map<string, int>::iterator itr;
        for (itr = raportMap.begin(); itr != raportMap.end(); ++itr) {
            raport += '\t' + itr->first + " - " + to_string(itr->second) + '\t' + '\n';
        }

        QMessageBox::information(nullptr, "Info - Raport gen filme", QString::fromStdString(raport));

        });


    QObject::connect(sortareTitlu, &QPushButton::clicked, [&]() {
        qDebug() << "Ati ales sortare dupa titlu";

        serv.sortTitlu();
        updateFilme();

        fereastraS->close();
        
        });


    QObject::connect(sortareAn, &QPushButton::clicked, [&]() {
        qDebug() << "Ati ales sortare dupa an";
        
        serv.sortAn();
        updateFilme();

        fereastraS->close();
        
        });



    QObject::connect(btnSortare, &QPushButton::clicked, [&]() {
        qDebug() << "Sortare";

        QWidget* ferSec = new QWidget;
        fereastraS = ferSec;

        //fereastra alegere crt sort
        QVBoxLayout* lyFereastra = new QVBoxLayout;
        QHBoxLayout* lyTxt = new QHBoxLayout;
        QFont fontN = crtMsg->font();
        fontN.setPointSize(12);
        fontN.setBold(true);
        crtMsg->setFont(fontN);
        lyTxt->addWidget(crtMsg);
        QHBoxLayout* lyBtnCrt = new QHBoxLayout;

        sortareTitlu->setStyleSheet("background: #D0E37C");
        sortareAn->setStyleSheet("background: #D0E37C");

        lyBtnCrt->addWidget(sortareTitlu);
        lyBtnCrt->addWidget(sortareAn);
        lyFereastra->addLayout(lyTxt);
        lyFereastra->addLayout(lyBtnCrt);
        fereastraS->setLayout(lyFereastra);
        fereastraS->show();
        
        updateFilme();
        });



    QObject::connect(filtrareTitlu, &QPushButton::clicked, [&]() {
        qDebug() << "Ati ales filtrare dupa titlu";

        dataCrt1->setText("");
        dataCrt2->setText("");

        crt1->hide();
        dataCrt1->hide();
        crt2->hide();
        dataCrt2->hide();

        string cap1 = "Titlu filme:";
        crt1->setText(QString::fromStdString(cap1));
        string cap2 = "NONE:";
        crt2->setText(QString::fromStdString(cap2));
        
        crt1->show();
        dataCrt1->show();
        btnOk->show();
    
        fltrCase = 1;
        
        });

    QObject::connect(filtrareActor, &QPushButton::clicked, [&]() {
        qDebug() << "Ati ales filtrare dupa actor";

        dataCrt1->setText("");
        dataCrt2->setText("");
        
        crt1->hide();
        dataCrt1->hide();
        crt2->hide();
        dataCrt2->hide();

        string cap1 = "Actor filme:";
        crt1->setText(QString::fromStdString(cap1));
        string cap2 = "NONE:";
        crt2->setText(QString::fromStdString(cap2));
        
        crt1->show();
        dataCrt1->show();
        btnOk->show();
        
        fltrCase = 2;

        });

    QObject::connect(filtrareAnGen, &QPushButton::clicked, [&]() {
        qDebug() << "Ati ales filtrare dupa an si gen";

        crt1->hide();
        dataCrt1->hide();
        crt2->hide();
        dataCrt2->hide();

        dataCrt1->setText("");
        dataCrt2->setText("");

        string cap1 = "An filme:";
        crt1->setText(QString::fromStdString(cap1));
        string cap2 = "Gen filme:";
        crt2->setText(QString::fromStdString(cap2));
        
        crt1->show();
        dataCrt1->show();
        crt2->show();
        dataCrt2->show();
        btnOk->show();
        
        fltrCase = 3;

        });


    QObject::connect(btnOk, &QPushButton::clicked, [&]() {
        qDebug() << "Filtrare realizata";
        
        updateFilme();

        string cap1 = "CRT 1:";
        crt1->setText(QString::fromStdString(cap1));
        string cap2 = "CRT 2:";
        crt2->setText(QString::fromStdString(cap2));
        

        crt1->hide();
        dataCrt1->hide();
        crt2->hide();
        dataCrt2->hide();
        btnOk->hide();
        
        filtrat.clear();

        if (fltrCase == 1) {
            fltrTitlu = dataCrt1->text().toStdString();
            if (fltrTitlu != "")
                filtrat=serv.filtruTitlu(fltrTitlu);
            else QMessageBox::information(nullptr, "Filtrare App", "Campuri goale!");
        }

        if (fltrCase == 2) {
            fltrActor = dataCrt1->text().toStdString();
            if (fltrActor != "")
                filtrat = serv.filtruActor(fltrActor);
            else QMessageBox::information(nullptr, "Filtrare App", "Campuri goale!");
        }

        if (fltrCase == 3) {
            fltrAn = dataCrt1->text().toStdString();
            fltrGen = dataCrt2->text().toStdString();
            if (fltrAn != "" && fltrGen != "")
                filtrat = serv.filtruAnGen(stoi(fltrAn), fltrGen);
            else QMessageBox::information(nullptr,"Filtrare App","Campuri goale!");
        }
        
        updateFilmeFiltrate(filtrat);

        fereastraF->close();
        fltrActor = "";
        fltrAn = "";
        fltrGen = "";
        fltrTitlu = "";
        });



    QObject::connect(btnFiltrare, &QPushButton::clicked, [&]() {

        qDebug() << "Filtrare";

        QWidget* ferSec = new QWidget;
        fereastraF = ferSec;

        //fereastra alegere crt filtrare
        QVBoxLayout* lyFereastra = new QVBoxLayout;
        QHBoxLayout* lyTxt = new QHBoxLayout;
        QFont fontN = crtMsgF->font();
        fontN.setPointSize(12);
        fontN.setBold(true);
        crtMsgF->setFont(fontN);
        lyTxt->addWidget(crtMsgF);
        QHBoxLayout* lyBtnCrt = new QHBoxLayout;

        filtrareTitlu->setStyleSheet("background: #D0E37C");
        filtrareActor->setStyleSheet("background: #D0E37C");
        filtrareAnGen->setStyleSheet("background: #D0E37C");

        lyBtnCrt->addWidget(filtrareTitlu);
        lyBtnCrt->addWidget(filtrareActor);
        lyBtnCrt->addWidget(filtrareAnGen);
        lyFereastra->addLayout(lyTxt);
        lyFereastra->addLayout(lyBtnCrt);
        fereastraF->setLayout(lyFereastra);

        

        //date filtrare
        QHBoxLayout* lyC1 = new QHBoxLayout;
        QHBoxLayout* lyC2 = new QHBoxLayout;


        crt1->hide();
        dataCrt1->hide();
        crt2->hide();
        dataCrt2->hide();
        btnOk->hide();

        crt1->setReadOnly(true);
        crt1->setMaximumWidth(150);
        crt1->setStyleSheet("* { background: rgba(240,240,240,255); border: none; }");
        lyC1->addWidget(crt1);
        lyC1->addWidget(dataCrt1);
        lyC1->addStretch();
        
        crt2->setReadOnly(true);
        crt2->setMaximumWidth(150);//
        crt2->setStyleSheet("* { background: rgba(240,240,240,255); border: none; }");
        lyC2->addWidget(crt2);
        lyC2->addWidget(dataCrt2);
        lyC2->addStretch();
        
        lyFereastra->addStretch();
        lyFereastra->addLayout(lyC1);
        lyFereastra->addLayout(lyC2);
        lyFereastra->addStretch();
        lyFereastra->addWidget(btnOk);

        fereastraF->show();

        updateFilme();
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

        //updateCos();
        //updateOferta();
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

        //updateCos();
        //updateOferta();
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

        //updateCos();
        //updateOferta();
        });


    QObject::connect(btnGolire, &QPushButton::clicked, [&]() {

        serv.golesteCos();
        qDebug() << "Cosul a fost golit.\n";
        //updateCos();
        //updateOferta();
        });


    QObject::connect(btnClose, &QPushButton::clicked, [&]() {
        qDebug() << "Aplicatie inchisa";
        close();
        QMessageBox::information(nullptr, "Info - APP", " - Aplicatie inchisa -\n \n      La revedere! ");
        
        QCoreApplication::quit();
        });
}




void OpenGUI::initGUIO() {
    resize(750, 450);
    QVBoxLayout* lyFereastra = new QVBoxLayout;
    setLayout(lyFereastra);

    
    btnClose->setStyleSheet("background: #DA5E5E");

    QHBoxLayout* lyMain = new QHBoxLayout;
    capacitateCos->setReadOnly(true);
    capacitateCos->setFixedWidth(130);
    
    capacitateCos->setStyleSheet("* { background: rgba(240,240,240,255); border: none; }");
    
    QHBoxLayout* lyBtnVCB = new QHBoxLayout;
    lyBtnVCB->addWidget(btnVizualizareLista);
    lyBtnVCB->addStretch();
    lyBtnVCB->addWidget(capacitateCos);
    lyBtnVCB->addWidget(btnCos);
    

    QHBoxLayout* lyBtnUC = new QHBoxLayout;
    lyBtnUC->addStretch();
    lyBtnUC->addWidget(btnUndo);
    lyBtnUC->addWidget(btnClose);


    QVBoxLayout* lyDREAPTA = new QVBoxLayout;
    lyDREAPTA->addLayout(lyBtnUC);


    QVBoxLayout* lySTANGA = new QVBoxLayout;

    lySTANGA->addLayout(lyBtnVCB);
    lySTANGA->addWidget(listaFilme);

    QHBoxLayout* lyBtnSFR = new QHBoxLayout;
    lyBtnSFR->addWidget(btnSortare);
    lyBtnSFR->addWidget(btnFiltrare);
    lyBtnSFR->addWidget(btnRaport);
    lySTANGA->addLayout(lyBtnSFR);


    lyMain->addLayout(lySTANGA);

    auto formLy = new QFormLayout;
    QLabel* filmul = new QLabel("FILM");
    QFont fontN = filmul->font();
    fontN.setPointSize(12);
    fontN.setBold(true);
    filmul->setFont(fontN);


    formLy->addRow(filmul);
    formLy->addRow("Titlu:", titlu);
    formLy->addRow("Gen:", gen);
    formLy->addRow("An:", an);
    formLy->addRow("Actor:", actor);
    
    lyDREAPTA->addLayout(formLy);

    QHBoxLayout* lyBtnAMSS = new QHBoxLayout;
    lyBtnAMSS->addWidget(btnAdauga);
    lyBtnAMSS->addWidget(btnModifica);
    lyBtnAMSS->addWidget(btnSterge);
    lyBtnAMSS->addWidget(btnCauta);

    
    QLabel* cos = new QLabel("COS");
    QFont fontCc = cos->font();
    fontCc.setPointSize(12);
    fontCc.setBold(true);
    cos->setFont(fontCc);

    QHBoxLayout* lyBtnActCos = new QHBoxLayout;
    
    lyBtnActCos->addWidget(btnAaugareC);
    lyBtnActCos->addWidget(btnGenerare);
    lyBtnActCos->addWidget(btnGolire);


    QHBoxLayout* lyBtnCos = new QHBoxLayout;
    lyBtnCos->addStretch();
    QLabel* infoCos = new QLabel("Cosuri speciale (Lab. 13-14) : ");
    lyBtnCos->addWidget(infoCos);
    lyBtnCos->addWidget(btnCosCRUDGUI);
    lyBtnCos->addWidget(btnCosReadOnlyGUI);

    
    lyDREAPTA->addLayout(lyBtnAMSS);
    lyDREAPTA->addSpacing(50);
    lyDREAPTA->addWidget(cos);
    lyDREAPTA->addLayout(lyBtnActCos);
    lyDREAPTA->addStretch();
    lyDREAPTA->addLayout(lyBtnCos);
    
    
    lyMain->addLayout(lyDREAPTA);
    lyFereastra->addLayout(lyMain);
}
