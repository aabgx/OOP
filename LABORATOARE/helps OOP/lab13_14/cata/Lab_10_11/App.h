#pragma once

#include <QtWidgets/QMainWindow>
#include "service.h"
#include <string>
#include "domain.h"
#include <QTableWidget>
#include <QListWidget>
#include "validator.h"
#include "service.h"
#include <QMessageBox>
#include "ui_App.h"
#include "utils.h"
#include "cos_list.h"

using namespace std;



class App : public QMainWindow
{
    Q_OBJECT
private:
    QTabWidget* tabs;
    QVBoxLayout* btn_layout;
    Observable observatori;

    
    void adauga_button(QLayout* layout, string text, string nume) {
        QPushButton* button = new QPushButton();
        button->setText(text.c_str());
        button->setObjectName(nume.c_str());
        button->setFixedWidth(NormalWidth);
        button->setStyleSheet("background-color: #E8E9EB;border: 1px solid #746D69;color: #746D69;");
        layout->addWidget(button);
    }

    void adauga_text_box(QLayout* layout, string placeholder, string nume) {
        QTextEdit* text_box = new QTextEdit();
        text_box->setFixedHeight(CursorHeight);
        text_box->setFixedWidth(NormalWidth);
        text_box->setPlaceholderText(placeholder.c_str());
        text_box->setObjectName(nume.c_str());

        //STYLE
        text_box->setStyleSheet("background: 0;border: 0;border-bottom: 0.5px solid #ACADA8;color: #746D69;");
        //STYLE

        layout->addWidget(text_box);
    }

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
    Creaza window-ul cu cos
    */
    void creaza_cos_window();

    /*
    Constructorul aplicatiei
    */
    Ui::AppClass ui;

    /*
    Conecteaza butoanele pentru a doua fereastra
    */
    void conecteaza_butoane_second_window();

    /*
    Creaza cos tab
    */
    void creaza_cos_tab();

    /*
    Creaza un window nou read-only al cosului
    */
    void creaza_cos_window_read_only();


    Service srv;
    

public:
    App(const Service &s,QWidget *parent = Q_NULLPTR);

    void agauga_tabel_discipline(QLayout* layout, string titlu, string nume) {
        layout->setContentsMargins(2, 0, 0, 0);
        //Labelul cu titlu
        QLabel* titlu_label = new QLabel();
        titlu_label->setText(titlu.c_str());
        titlu_label->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
        titlu_label->setAlignment(Qt::AlignCenter);
        //Labelul cu titlu
        layout->addWidget(titlu_label);

        QListWidget* lista = new QListWidget;
        lista->setFixedHeight(600);
        lista->setFixedWidth(600);
        lista->setObjectName(nume.c_str());
        lista->setStyleSheet("color: #746D69;background-color: #E8E9EB;border-color: #746D69;font-size: 15px;");

        auto fnct = [lista]() {
            lista->setStyleSheet("color: #746D69;background-color: #E8E9EB;border-color: #746D69;font-size: 15px;color: red;");
        };
        QObject::connect(lista, &QListWidget::itemSelectionChanged, this, fnct);

        layout->addWidget(lista);
    }


};
