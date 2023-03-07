//
// Created by Laura on 5/4/2022.
//

#ifndef UNTITLED_GUIREZERVA_H
#define UNTITLED_GUIREZERVA_H


#include <QApplication>
#include "QLabel"
#include "CosREADONLYGUI.h"
#include "CosCRUDGUI.h"
#include "QWidget"
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include "Qt"
#include "QRadioButton"
#include "QLineEdit"
#include "QString"
#include "Service.h"
#include "QGroupBox"
#include <QComboBox>
//#include <CosGUI.h>
#include "Observer.h"

class GUItur : public QWidget{
private:
    ProdService& srv;
    //QTableWidget* tabelcos;
    QWidget *wnd;
    QWidget* left;
    QWidget* right;
    QVBoxLayout* vL;
    QVBoxLayout* lyleft,*lyright,*lybutoane;
    QHBoxLayout* layout,*lyrandom;
    QWidget* details;
    QFormLayout* lyform,*lyexport;
    QLabel *lblnume, *lbltip, *lblprod, *lblpret;
    QLineEdit *txtnume, *txttip, *txtprod, *txtpret;

    QWidget* formfilter,*formexport,*butoane;
    QFormLayout* lyformfilter,*lyformexport;
    QLabel* lblfilter,*lblexport;
    QLineEdit* txtfilter,*txtexport;


    QPushButton* btnAddProd;
    QPushButton* btnDellProd;
    QPushButton* btnModifyProd;
    QPushButton *btnprint;
    QPushButton *btnSort;
    QPushButton* btnundo;

    QPushButton* btncount,*btnfilter1,*btnfilter2,*btnfilter3;


    QPushButton* coscrud,*addcos,*dellcos,*randomcos,*cosread;
    QWidget* cos13;
    QFormLayout* cos13layout;
    QLabel *lblnumecos13,  *lblprodcos13;
    QLineEdit *txtnumecos13,  *txtprodcos13;
    QSlider* slider13;


    QVBoxLayout* lyRadioBox;
    QGroupBox* groupBox;
    QPushButton* test;

    QPushButton* btnGen[21]{0};

    QRadioButton *radioSortNume0, *radioSortNume1, *radioSortPret0, *radioSortPret1, *radioSortNumeTip0, *radioSortNumeTip1;

    QWidget* wndcos,*random;
    QWidget* leftcos,*rightcos,*formcos;
    QVBoxLayout* lyleftcos,*lyrightcos;
    QHBoxLayout* layoutcos,*lyrandomcos;
    QFormLayout* lyformcos;
    QLabel *lblnumecos,  *lblprodcos;
    QLineEdit *txtnumecos,  *txtprodcos;
    QPushButton* btnadd,*btnrandom,*btnempty,*btnexport;
    QComboBox* randombox;
    QListWidget* prodlist;
    QPushButton* meniucos,*btnFindProd;

    void initGUI();
    void connectSignalSlots();

    int countvechi=0;
    vector<string> gencount;
    void reloadbutoane();



public:
    explicit GUItur(ProdService& srv):srv{srv}{
        //tabelcos=new QTableWidget(0,4);
        wnd = new QWidget;
        //wnd1 = new QWidget;
        left = new QWidget;
        right = new QWidget;
        lyleft = new QVBoxLayout;
        lyright = new QVBoxLayout;
        btnAddProd = new QPushButton("Adauga produs");
        btnDellProd = new QPushButton("Sterge produs");
        btnModifyProd = new QPushButton("Modifica produs");
        btnprint = new QPushButton("AFISEAZA TOATE PRODUSELE");
        btnundo=new QPushButton("UNDO");

        btnfilter1=new QPushButton("Filtreaza dupa nume");
        btnfilter2=new QPushButton("Filtreaza dupa tip");
        btnfilter3=new QPushButton("Filtreaza dupa producator");

        test=new QPushButton("test");

        layout=new QHBoxLayout;
        vL=new QVBoxLayout;//widget normal principal pentu window
        details = new QWidget;//formularul pentru produs
        lyform = new QFormLayout;
        lblnume = new QLabel;
        lbltip = new QLabel;
        lblprod= new QLabel;
        lblpret = new QLabel;
        txtnume = new QLineEdit;
        txttip = new QLineEdit;
        txtprod = new QLineEdit;
        txtpret = new QLineEdit;

        formfilter=new QWidget;
        lyformfilter=new QFormLayout;
        lblfilter=new QLabel("Cuvant cheie filtrare:");
        txtfilter=new QLineEdit;

        formexport=new QWidget;
        lyformexport=new QFormLayout;
        lblexport=new QLabel("Fisierul in care doriti exportarea:");
        txtexport=new QLineEdit;

        butoane=new QWidget;
        lybutoane=new QVBoxLayout;
        btnFindProd=new QPushButton("GASESTE PRODUS DUPA NUME SI PRODUCATOR");


        lyRadioBox=new QVBoxLayout;
        btnSort=new QPushButton("Sorteaza produsele");
        groupBox = new QGroupBox(tr("Tip sortare"));
        radioSortNume0 = new QRadioButton(QString::fromStdString("Dupa nume crescator"));
        radioSortNume1 = new QRadioButton(QString::fromStdString("Dupa nume descrescator"));
        radioSortPret0 = new QRadioButton(QString::fromStdString("Dupa pret crescator"));
        radioSortPret1 = new QRadioButton(QString::fromStdString("Dupa pret descrescator"));
        radioSortNumeTip0=new QRadioButton(QString::fromStdString("Dupa nume si tip crescator"));
        radioSortNumeTip1 = new QRadioButton(QString::fromStdString("Dupa nume si tip descrescator"));


        //COS DE CUMPARATURI--------------------------------------------------
        wndcos = new QWidget;
        random=new QWidget;
        leftcos = new QWidget;
        rightcos = new QWidget;
        formcos = new QWidget;
        lyleftcos = new QVBoxLayout;
        lyrightcos = new QVBoxLayout;
        btnadd = new QPushButton("ADAUGA PRODUS IN COS");
        btnempty = new QPushButton("GOLESTE COSUL");
        btnrandom = new QPushButton("ADAUGARE PRODUSE RANDOM");
        btnexport = new QPushButton("EXPORT COS");

        lyrandom=new QHBoxLayout;
        lyexport=new QFormLayout;
        lyformcos = new QFormLayout;
        lblnumecos = new QLabel("Nume produs:");
        lblprodcos = new QLabel("Producator produs:");
        txtnumecos = new QLineEdit;
        txtprodcos = new QLineEdit;
        layoutcos=new QHBoxLayout;

        randombox = new QComboBox;
        prodlist = new QListWidget{};
        meniucos=new QPushButton("MENIU COS");

        coscrud = new QPushButton("----COSCRUD-----");
        cosread = new QPushButton("----COSREADONLY-----");
        addcos = new QPushButton("ADAUGARE PRODUS COS");
        dellcos = new QPushButton("GOLIRE COS");
        randomcos = new QPushButton("GENERARE PRODUSE COS");
        cos13=new QWidget;
        cos13layout=new QFormLayout;
        lblnumecos13 = new QLabel("Nume produs:");
        lblprodcos13 = new QLabel("Producator produs:");
        txtnumecos13 = new QLineEdit;
        txtprodcos13 = new QLineEdit;
        slider13=new QSlider;


    }
    void run();
    static void showAll(const vector<Produs>& lista);
    vector<string> generare();
    int bucati(string tip);
    void reloaddata1();
    //void populate(QTableWidget* table, const vector<Produs>& all);
    //void update() override{
    //    reloaddata1();
    //}

};


#endif //UNTITLED_GUIREZERVA_H
