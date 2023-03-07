#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_App.h"
#include <string>
#include "service.h"

using namespace std;

class App : public QMainWindow
{
    Q_OBJECT
private:
    QTabWidget* tabs;
    QVBoxLayout* btn_layout;

    /*
    Creaza TABUL CRUD al aplicatiei
    */
    void creaza_crud_tab();

    void actualizeaza_butoane_tip();

    /*
    Creaza TABUL FILTREAZA/SORTEAZA al aplicatiei
    */
    void creaza_filtreaza_sorteaza_tab();


    /*
    Adauga text box la un layout
    */
    void adauga_text_box(QLayout* layout,string placeholder, string nume);

    /*
    Adauga un buton la un layout
    */
    void adauga_button(QLayout* layout, string text, string nume);

    /*
    Adauga label text
    */
    void agauga_tabel_discipline(QLayout *layout, string titlu, string nume);

    /*
    Conecteaza toate butoanele cu actiuniiloe lor
    */
    void conecteaza();

    /*
    Creaza un prompt cu un mesaj
    */
    void creaza_prompt(string msg);

    /*
    Sterge chestiile din toate text_boxurile
    */
    void delete_text_boxs();

    /*
    Actualizeaza tabelul cu disciplinele
    */
    void actualizeaza_tabel(string nume, vector<Disciplina>lst);

    /*
    Creaza tab-ul cu butoane
    */
    void creaza_butoane_tab();

    /*
    Constructorul aplicatiei
    */
    Ui::AppClass ui;

    Service srv;
    

public:
    App(const Service &s,QWidget *parent = Q_NULLPTR);

};
