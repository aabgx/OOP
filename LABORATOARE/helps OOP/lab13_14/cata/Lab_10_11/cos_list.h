#pragma once
#include <qwidget.h>
#include "Observer.h"
#include <qlistwidget.h>

#define CursorHeight 28
#define NormalWidth 130

using namespace std;




class ContractGUICuTabel : public QWidget,public Observer{
private:
    Service& srv;
    Observable& obs;
    QListWidget* p_lista;

    void creaza_prompt(string msg) {
        QMessageBox* prmpt = new QMessageBox();
        prmpt->setStyleSheet("QLabel{min-width: 500px;}");
        prmpt->setText(msg.c_str());
        prmpt->show();
    }

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

    void actualizeaza_tabel(string nume, vector<Disciplina>lst) {
        QListWidget* lista = findChild<QListWidget*>(nume.c_str()); // I-am dat numele "Discipline"

        lista->clear();
        for (auto el : lst) {
            lista->addItem(el.str().c_str());
        }
    }

    void delete_text_boxs() {
        QTextEdit* f_cos_dnm_2 = findChild<QTextEdit*>("Cos_Denumire"); // I-am dat numele "Cos_Denumire"
        QTextEdit* f_cos_nr_2 = findChild<QTextEdit*>("Cos_nr"); // I-am dat numele "Cos_Denumire"
        QTextEdit* f_cos_tip_2 = findChild<QTextEdit*>("Cos_tip"); // I-am dat numele "Cos_Denumire"
        QTextEdit* f_cos_nume_2 = findChild<QTextEdit*>("Cos_Nume_HTML"); // I-am dat numele "Cos_Denumire"

        f_cos_dnm_2->setText("");
        f_cos_nr_2->setText("");
        f_cos_tip_2->setText("");
        f_cos_nume_2->setText("");
    }

    void actualizeaza_parinte() {
        auto lst = srv.get_all_contract();
        p_lista->clear();
        for (auto el : lst) {
            p_lista->addItem(el.str().c_str());
        }
    }

    void conecteaza_butoane_second_window() {
        ///ADAUGA
        QPushButton* adauga_2 = findChild<QPushButton*>("Cos_adauga"); // I-am dat numele "Cos_adauga"
        auto f_adauga_2 = [this]() {
            //Gasim Text Boxurile
            QTextEdit* dnm = findChild<QTextEdit*>("Cos_Denumire"); // I-am dat numele "Cos_Denumire"
            string s_dnm = dnm->toPlainText().toStdString();
            try {

                srv.adauga_in_contract(s_dnm);
                actualizeaza_tabel("Contract", srv.get_all_contract());
                delete_text_boxs();
                obs.notify();
                actualizeaza_parinte();
            }
            catch (ExceptiiValidare& e) {
                creaza_prompt(e.get_Msg());
            }
        };
        connect(adauga_2, &QPushButton::released, this, f_adauga_2); // Dam actiune butonului "Sterge"
        ///ADAUGA
        ///GENEREAZA
        QPushButton* genereaza_2 = findChild<QPushButton*>("Cos_Genereaza"); // I-am dat numele "Cos_Genereaza"
        auto f_genereaza_2 = [this]() {
            //Gasim Text Boxurile
            QTextEdit* nr = findChild<QTextEdit*>("Cos_nr"); // I-am dat numele "Cos_nr"
            string s_nr = nr->toPlainText().toStdString();
            try {
                int numar = stoi(s_nr);
                srv.genereaza_contracte(numar);
                actualizeaza_tabel("Contract", srv.get_all_contract());
                obs.notify();
                actualizeaza_parinte();
            }
            catch (ExceptiiValidare& e) {
                creaza_prompt(e.get_Msg());
            }
            catch (exception&) {
                creaza_prompt("Numarul de contracte trebuie sa fie un numar!");
            }
            delete_text_boxs();
        };
        connect(genereaza_2, &QPushButton::released, this, f_genereaza_2); // Dam actiune butonului "Sterge"
        ///GENEREAZA
        ///STERGE
        QPushButton* sterge_2 = findChild<QPushButton*>("Cos_Sterge"); // I-am dat numele "Cos_Genereaza"
        auto f_sterge_2 = [this]() {
            //Gasim Text Boxurile
            QTextEdit* tip = findChild<QTextEdit*>("Cos_tip"); // I-am dat numele "Cos_nr"
            string s_tip = tip->toPlainText().toStdString();
            try {
                srv.sterge_tip(s_tip);
                actualizeaza_tabel("Contract", srv.get_all_contract());
                obs.notify();
                actualizeaza_parinte();
            }
            catch (ExceptiiValidare& e) {
                creaza_prompt(e.get_Msg());
            }
            catch (exception&) {
                creaza_prompt("Numarul de contracte trebuie sa fie un numar!");
            }
            delete_text_boxs();
        };
        connect(sterge_2, &QPushButton::released, this, f_sterge_2); // Dam actiune butonului "Sterge"
        ///STERGE
        ///CLEAR
        QPushButton* clear_2 = findChild<QPushButton*>("Cos_Clear"); // I-am dat numele "Cos_Clear"
        auto f_clear_2 = [this]() {
            //Gasim Text Boxurile
            try {
                srv.goleste();
                actualizeaza_tabel("Contract", srv.get_all_contract());
                obs.notify();
                actualizeaza_parinte();
            }
            catch (ExceptiiValidare& e) {
                creaza_prompt(e.get_Msg());
            }
            delete_text_boxs();
        };
        connect(clear_2, &QPushButton::released, this, f_clear_2); // Dam actiune butonului "Sterge"
        ///CLEAR
        ///SAVE
        QPushButton* b_export_2 = findChild<QPushButton*>("Cos_Export"); // I-am dat numele "Cos_Export"
        auto f_export_2 = [this]() {
            //Gasim Text Boxurile
            QTextEdit* html = findChild<QTextEdit*>("Cos_Nume_HTML"); // I-am dat numele "Cos_Nume_HTML"
            string s_html = html->toPlainText().toStdString();
            try {
                string extensie = s_html.substr(s_html.size() - 5, 5);
                if (extensie != ".html") {
                    creaza_prompt("Fisierul dat nu este de tipul HTML!");
                }
                else
                {
                    srv.salveaza_contract(s_html);
                    actualizeaza_tabel("Contract", srv.get_all_contract());
                    obs.notify();
                    actualizeaza_parinte();
                }
            }
            catch (ExceptiiValidare& e) {
                creaza_prompt(e.get_Msg());
            }
            delete_text_boxs();
        };
        connect(b_export_2, &QPushButton::released, this, f_export_2); // Dam actiune butonului "Sterge"
        ///SAVE
    }


	void initializeaza() {
        QGridLayout* main_layout = new QGridLayout;
        setLayout(main_layout);
        setStyleSheet("font-family: Times New Roman, Times, serif;");

        setFixedHeight(600);
        setFixedWidth(800);
        main_layout->setContentsMargins(0, 0, 0, 0);

        //Labelul cu titlu
        QLabel* titlu = new QLabel();
        titlu->setText("Manager cos");
        titlu->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
        titlu->setAlignment(Qt::AlignCenter);
        main_layout->addWidget(titlu, 0, 0, 1, 2); // Dupa el urmeaza 2 coloane, una cu Text-Box-urile si alta cu Disciplina
        //Labelul cu titlu

        QWidget* stanga_widget = new QWidget;
        QVBoxLayout* stanga_layout = new QVBoxLayout;
        stanga_widget->setLayout(stanga_layout);

        adauga_text_box(stanga_layout, "Denumire", "Cos_Denumire");
        adauga_button(stanga_layout, "Adauga", "Cos_adauga");
        adauga_text_box(stanga_layout, "Numar contracte", "Cos_nr");
        adauga_button(stanga_layout, "Genereaza", "Cos_Genereaza");
        adauga_text_box(stanga_layout, "Tip contract", "Cos_tip");
        adauga_button(stanga_layout, "Sterge toate contractele", "Cos_Sterge");

        QWidget* dreapta_widget = new QWidget;
        QVBoxLayout* dreapta_layout = new QVBoxLayout;
        dreapta_widget->setLayout(dreapta_layout);
        agauga_tabel_discipline(dreapta_layout, "Contract", "Contract");

        QWidget* jos_widget = new QWidget;
        QHBoxLayout* jos_layout = new QHBoxLayout;
        jos_widget->setLayout(jos_layout);

        adauga_button(jos_layout, "Goleste contract", "Cos_Clear");
        adauga_text_box(jos_layout, "Nume fisier HTML", "Cos_Nume_HTML");
        adauga_button(jos_layout, "Salveaza contract", "Cos_Export");

        main_layout->setColumnStretch(1, 2);
        main_layout->setRowStretch(1, 2);
        main_layout->addWidget(stanga_widget);
        main_layout->addWidget(dreapta_widget);
        main_layout->addWidget(jos_widget, 2, 1);
	}
public:

    ContractGUICuTabel(QListWidget* p_lista,Observable& obs,Service& srv) :p_lista{ p_lista },obs(obs),srv(srv) {
        initializeaza();
        conecteaza_butoane_second_window();
        show();
    }

    void update() override {
        actualizeaza_tabel("Contract",srv.get_all_contract());
    }
};