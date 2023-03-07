//
// Created by Laura on 5/4/2022.
//

#include "GUIrezerva.h"
#include "string.h"
#include <QListWidget>
#include "CosCRUDGUI.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QString>
//#include "GUI.h"
#include <QMessageBox>
#include "QApplication"
#include "QLabel"
#include "QWidget"
#include "Qt"
#include "QHeaderView"
#include "QTableWidget"
#include "QLineEdit"
#include "QString"
#include <vector>
#include <algorithm>
#include <string>
#include<QDebug>
#include <QVariant>
#include <Qstring>
using std::strcmp;


void GUItur::run() {
    GUItur::initGUI();
    GUItur::connectSignalSlots();
    //reloaddata1();
    wnd->show();

}

void GUItur::initGUI() {

    left->setLayout(lyleft);
    right->setLayout(lyright);

    details->setLayout(lyform);
    lblnume->setText("Nume produs:");
    lbltip->setText("Tip produs:");
    lblpret->setText("Pret produs:");
    lblprod->setText("Producator produs:");
    lyform->addRow(lblnume, txtnume);
    lyform->addRow(lbltip, txttip);
    lyform->addRow(lblprod, txtprod);
    lyform->addRow(lblpret, txtpret);

    lyleft->addWidget(details);
    lyform->addWidget(btnprint);
    lyform->addWidget(btnAddProd);
    lyform->addWidget(btnDellProd);
    lyform->addWidget(btnModifyProd);
    lyform->addWidget(btnundo);
    lyform->addWidget(btnFindProd);
    lyleft->addWidget(meniucos);


    formfilter->setLayout(lyformfilter);
    lyformfilter->addRow(lblfilter, txtfilter);
    lyleft->addWidget(formfilter);
    lyformfilter->addWidget(btnfilter1);
    lyformfilter->addWidget(btnfilter2);
    lyformfilter->addWidget(btnfilter3);

    groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioSortNume0);
    lyRadioBox->addWidget(radioSortNume1);
    lyRadioBox->addWidget(radioSortPret0);
    lyRadioBox->addWidget(radioSortPret1);
    lyRadioBox->addWidget(radioSortNumeTip0);
    lyRadioBox->addWidget(radioSortNumeTip1);
    lyRadioBox->addWidget(btnSort);
    lyleft->addWidget(groupBox);

    butoane->setLayout(lybutoane);
    reloadbutoane();
    lyright->addWidget(butoane);

    slider13->setMinimum(0);
    slider13->setMaximum(40);
    slider13->setOrientation(Qt::Horizontal);
    slider13->setTickPosition(QSlider::TicksAbove);

    //partea de crud/read
    cos13->setLayout(cos13layout);
    cos13layout->addRow(lblnumecos13,txtnumecos13);
    cos13layout->addRow(lblprodcos13,txtprodcos13);
    cos13layout->addWidget(coscrud);
    cos13layout->addWidget(cosread);
    cos13layout->addWidget(addcos);
    cos13layout->addWidget(dellcos);
    cos13layout->addWidget(randomcos);
    cos13layout->addWidget(slider13);
    layout->addWidget(cos13);


    layout->addWidget(left);
    layout->addWidget(right);

    wnd->setLayout(layout);


    //COS DE CUMPARATURI_________________________________________
    leftcos->setLayout(lyleftcos);
    rightcos->setLayout(lyrightcos);

    formcos->setLayout(lyformcos);
    lyformcos->addRow(lblnumecos,txtnumecos);
    lyformcos->addRow(lblprodcos,txtprodcos);


    lyleftcos->addWidget(formcos);
    lyleftcos->addWidget(btnadd);
    lyleftcos->addWidget(btnempty);

    random->setLayout(lyrandom);
    for(int i=1;i<=10;i++)
        randombox->addItem(QString::fromStdString(std::to_string(i)));
    lyrandom->addWidget(btnrandom);
    lyrandom->addWidget(randombox);
    lyleftcos->addWidget(random);

    formexport->setLayout(lyexport);
    lyexport->addRow(lblexport,txtexport);
    lyexport->addWidget(btnexport);
    lyleftcos->addWidget(formexport);
    lyleftcos->addWidget(formexport);

    prodlist->setFixedWidth(320);
    prodlist->setSelectionMode(QAbstractItemView::SingleSelection);
    lyrightcos->addWidget(prodlist);

    layoutcos->addWidget(leftcos);
    layoutcos->addWidget(rightcos);
    wndcos->setLayout(layoutcos);

}





void GUItur::connectSignalSlots() {
    //partea crud/read pe fereastra principala------------
    QObject::connect(coscrud, &QPushButton::clicked, [this] {
        auto cos=new CosCRUDGUI(srv.getcos(),srv);
        //cos->run();
        cos->run();
    });
    QObject::connect(cosread, &QPushButton::clicked, [this] {
        auto cos=new CosReadOnlyGUI(srv.getcos());
        cos->show();
    });
    QObject::connect(addcos, &QPushButton::clicked, [this] {

        string nume = txtnumecos13->text().toStdString();
        string prod = txtprodcos13->text().toStdString();
        txtnume->clear();
        txtprod->clear();
        try {

            this->srv.addlistsrv(nume, prod);
            QMessageBox::information(this, "Info", QString::fromStdString("Produs adaugat cu succes in cos."));
            //populate(tabelcos,srv.getallfromlistsrv());
            //this->update();
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });
    QObject::connect(dellcos, &QPushButton::clicked, [&]() {
        srv.emptylistsrv();
        //populate(tabelcos,srv.getallfromlistsrv());
        //this->update();
        //this->reloaddata1();
    });
    QObject::connect(randomcos, &QPushButton::clicked, [&]() {
        int nr= slider13->value();
        this->srv.addrandomsrv(nr);
        //this->update();
        //reloaddata1();
    });
    //meniu principal----------------------------

    QObject::connect(btnprint, &QPushButton::clicked, [this] {
        GUItur::showAll(this->srv.getallproducts());
    });

    QObject::connect(btnundo, &QPushButton::clicked, [this] {
        try {
            this->srv.undo();
            QMessageBox::information(this, "Info", QString::fromStdString("Succes Undo"));
        }
        catch (UndoException &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.get_msg()));
        }
    });

    QObject::connect(btnfilter1, &QPushButton::clicked, [this] {
        string cuv = txtfilter->text().toStdString();
        GUItur::showAll(this->srv.filtreaza_nume(cuv));

    });
    QObject::connect(btnfilter2, &QPushButton::clicked, [this] {
        string cuv=txtfilter->text().toStdString();
        GUItur::showAll(this->srv.filtreaza_tip(cuv));

    });
    QObject::connect(btnfilter3, &QPushButton::clicked, [this] {
        string cuv=txtfilter->text().toStdString();
        GUItur::showAll(this->srv.filtreaza_prod(cuv));
    });
    QObject::connect(btnAddProd, &QPushButton::clicked, [this] {

        string nume = txtnume->text().toStdString();
        string tip = txttip->text().toStdString();
        string prod = txtprod->text().toStdString();
        double pret = txtpret->text().toDouble();
        txtnume->clear();
        txttip->clear();
        txtprod->clear();
        txtpret->clear();
        try {

            this->srv.addservice(nume, tip, prod, pret);
            QMessageBox::information(this, "Info", QString::fromStdString("Produs adaugat cu succes."));
            reloadbutoane();
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });
    QObject::connect(btnFindProd, &QPushButton::clicked, [this] {

        string nume = txtnume->text().toStdString();
        string prod = txtprod->text().toStdString();
        txtnume->clear();
        txtprod->clear();
        try {

            Produs p=srv.findservice(nume,  prod);
            string afis="PRODUSUL ESTE: "+ p.getNume()+" "+p.getTip()+" "+p.getProd()+" " + std::to_string(p.getPret());
            QMessageBox::information(this, "Info", QString::fromStdString(afis));
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });
    QObject::connect(btnDellProd, &QPushButton::clicked, [this] {

        string nume = txtnume->text().toStdString();
        string tip = txttip->text().toStdString();
        string prod = txtprod->text().toStdString();
        double pret = txtpret->text().toDouble();

        txtnume->clear();
        txttip->clear();
        txtprod->clear();
        txtpret->clear();
        try {

            this->srv.dellservice(nume, tip, prod, pret);
            QMessageBox::information(this, "Info", QString::fromStdString("Produs sters cu succes."));
            reloadbutoane();
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });

    QObject::connect(btnModifyProd, &QPushButton::clicked, [this] {

        string nume = txtnume->text().toStdString();
        string tip = txttip->text().toStdString();
        string prod = txtprod->text().toStdString();
        double pret = txtpret->text().toDouble();
        txtnume->clear();
        txttip->clear();
        txtprod->clear();
        txtpret->clear();
        try {
            this->srv.modifyservice(nume, tip, prod, pret);
            QMessageBox::information(this, "Info", QString::fromStdString("Produsul s-a modificat cu succes."));
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });
    QObject::connect(btnSort, &QPushButton::clicked, [this] {
        if (this->radioSortNume0->isChecked())
            this->showAll(srv.sortnume(0));
        else if (this->radioSortNume1->isChecked())
            this->showAll(srv.sortnume(1));
        if (this->radioSortPret0->isChecked())
            this->showAll(srv.sortpret(0));
        if (this->radioSortPret1->isChecked())
            this->showAll(srv.sortpret(1));
        if (this->radioSortNumeTip0->isChecked())
            this->showAll(srv.sortNumeTip(0));
        if (this->radioSortNumeTip1->isChecked())
            this->showAll(srv.sortNumeTip(1));
    });




    //COS de Cumparaturi---------------------------------
    QObject::connect(meniucos, &QPushButton::clicked, [this] {
        //GUItur::initGUIcos();
        wndcos->show();
    });
    QObject::connect(btnadd, &QPushButton::clicked, [this] {

        string nume = txtnumecos->text().toStdString();
        string prod = txtprodcos->text().toStdString();
        txtnume->clear();
        txtprod->clear();
        try {

            this->srv.addlistsrv(nume, prod);
            QMessageBox::information(this, "Info", QString::fromStdString("Produs adaugat cu succes in cos."));
            reloaddata1();
        }
        catch (RepoExcep &re) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(re.getErrorMessage()));
        }
        catch (ValidationExcep &ve) {
            QMessageBox::warning(this, "Fail", QString::fromStdString(ve.getErrorMessages()));

        }
    });
    QObject::connect(btnempty, &QPushButton::clicked, [&]() {
        srv.emptylistsrv();
        this->reloaddata1();
    });
    QObject::connect(btnexport, &QPushButton::clicked, [&]() {
        string fisier = txtexport->text().toStdString();
        srv.exportsrv(fisier);
    });
    QObject::connect(btnrandom, &QPushButton::clicked, [&]() {
        QString numar= randombox->currentText();
        int nr=numar.toInt();
        this->srv.addrandomsrv(nr);
        reloaddata1();
    });



}


void GUItur::showAll(const vector<Produs> &lista) {
    int noLines = 10;
    int noColumns = 4;
    auto *list = new QTableWidget{noLines, noColumns};

    //setam header-ul tabelului
    QStringList tblHeaderList;
    tblHeaderList << "NUME" << "TIP" << "PRODUCATOR" << "PRET";
    list->setHorizontalHeaderLabels(tblHeaderList);

    //optiune pentru a se redimensiona celulele din tabel in functie de continut
    list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    list->setRowCount(lista.size());

    int lineNumber = 0;
    for (auto& song : lista) {
        list->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(song.getNume())));
        list->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(song.getTip())));
        list->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(song.getProd())));
        list->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(song.getPret())));
        lineNumber++;
    }
    list->show();
}
void clearLayout(QLayout* layout) {
    if (layout == NULL)
        return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void GUItur::reloadbutoane() {
    clearLayout(this->lybutoane);
    const vector<Produs>& prods = this->srv.getallproducts();
    vector<string> tipuri = this->generare();

    for (string tip : tipuri) {
        btncount = new QPushButton{ QString::fromStdString(tip) };
        lybutoane->addWidget(btncount);
        int buc = bucati(tip);
        QObject::connect(btncount, &QPushButton::clicked, [tip, buc]() {
            QMessageBox::information(nullptr, "BUCATI", QString::fromStdString(std::to_string(buc)));

        });
    }
}
int GUItur:: bucati( string tip){
    vector<Produs>list =srv.getallproducts();
    int number=0;
    for(const auto prod: list)
    {
        if(prod.getTip()==tip)
            number++;
    }
    return number;
}
vector<string> GUItur::generare() {
    vector<Produs> lista = srv.getallproducts();
    vector<string> tipuri;
    for (const auto prod: lista) {
        int ok=0;//nu se gaseste
        for(const auto p: tipuri)
        {
            if(prod.getTip()==p)
                ok=1;
        }
       if(ok==0) {
           tipuri.push_back(prod.getTip());
           string count = std::to_string(bucati(prod.getTip()));
           //tipuri.push_back(count);
       }
    }
    return tipuri;
}

void GUItur::reloaddata1() {
    this->prodlist->clear();

    const vector<Produs>& prod = srv.getallfromlistsrv();
    for (auto& p : prod) {
        QString currentItem = QString::fromStdString(p.getNume() + "\t" + p.getTip() + "\t" + p.getProd() + "\t" + std::to_string(p.getPret()));
        this->prodlist->addItem(currentItem);
    }

}

