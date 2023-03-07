#include "App.h"
#include <string>
#include "domain.h"
#include <QTableWidget>
#include "validator.h"
#include "service.h"
#include <QMessageBox>
#define CursorHeight 28
#define NormalWidth 130

using namespace std;

App::App(const Service& s, QWidget* parent)
    : QMainWindow(parent) {
    srv = s;

    ui.setupUi(this);
    tabs = new QTabWidget(this);
    tabs->setFixedHeight(400);
    tabs->setFixedWidth(600);

    //Creaza tab-ul CRUD
    creaza_crud_tab();
    //CREAZA tab-ul FILTREAZA/SORTEAZA
    creaza_filtreaza_sorteaza_tab();
    //Da actiuni la butoane
    //CREAZA TABUL BUTOANE
    creaza_butoane_tab();
    conecteaza();
    setStyleSheet("font-family: Times New Roman, Times, serif;");
}

void App::creaza_prompt(string msg) {
    QMessageBox* prmpt = new QMessageBox();
    prmpt->setStyleSheet("QLabel{min-width: 500px;}");
    prmpt->setText(msg.c_str());
    prmpt->show();
}

void App::agauga_tabel_discipline(QLayout *layout, string titlu, string nume) {
    layout->setContentsMargins(2, 0, 0, 0);
    //Labelul cu titlu
    QLabel* titlu_label = new QLabel();
    titlu_label->setText(titlu.c_str());
    titlu_label->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
    titlu_label->setAlignment(Qt::AlignCenter);
    //Labelul cu titlu
    layout->addWidget(titlu_label);

    QTableWidget* tabel = new QTableWidget();
    tabel->setObjectName(nume.c_str());
    tabel->setColumnCount(4);
    tabel->setRowCount(0);
    tabel->setStyleSheet("color: #746D69;background-color: #E8E9EB;border-color: #746D69;");
    QStringList tblHeaderList;
    tblHeaderList << "Denumire" << "Ore pe saptamana" << "Tip" << "Cadru didactic";
    tabel->setHorizontalHeaderLabels(tblHeaderList);
    //tabel->setCellWidget(0, 0, new QLabel("denumire 1"));

    layout->addWidget(tabel);
    
    
}

void App :: adauga_button(QLayout* layout, string text, string nume)             {
    QPushButton* button = new QPushButton();
    button->setText(text.c_str());
    button->setObjectName(nume.c_str());
    button->setFixedWidth(NormalWidth);
    button->setStyleSheet("background-color: #E8E9EB;border: 1px solid #746D69;color: #746D69;");
    layout->addWidget(button);
}

void App::adauga_text_box(QLayout* layout, string placeholder, string nume) {
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

void App::delete_text_boxs() {
    QTextEdit* dnm = findChild<QTextEdit*>("Denumire"); // I-am dat numele "Denumire"
    QTextEdit* ora = findChild<QTextEdit*>("Ora"); // I-am dat numele "Ora"
    QTextEdit* tip = findChild<QTextEdit*>("Tip"); // I-am dat numele "Tip"
    QTextEdit* cdr = findChild<QTextEdit*>("Cadru"); // I-am dat numele "Cadru"
    QTextEdit* fdm = findChild<QTextEdit*>("Find/Delete/Modify"); // I-am dat numele "Find/Delete/Modify"
    QTextEdit* min = findChild<QTextEdit*>("Minim"); // I-am dat numele "Minim"
    QTextEdit* max = findChild<QTextEdit*>("Maxim"); // I-am dat numele "Maxim"
    QTextEdit* f_cdr = findChild<QTextEdit*>("Filtreaza Cadru"); // I-am dat numele "Filtreaza Cadru"

    dnm->setText("");
    ora->setText("");
    tip->setText("");
    cdr->setText("");
    fdm->setText("");
    min->setText("");
    max->setText("");
    f_cdr->setText("");
}

void App::actualizeaza_tabel(string nume, vector<Disciplina>lst) {
    QTableWidget* tabel = findChild<QTableWidget*>(nume.c_str()); // I-am dat numele "Discipline"
    tabel->setRowCount(lst.size());
    for (int i = 0;i<lst.size();i++) {
        //Seteaza denumirea
        tabel->setCellWidget(i, 0, new QLabel(lst[i].get_denumire().c_str()));
        //Seteaza ora

        tabel->setCellWidget(i, 1, new QLabel(to_string(lst[i].get_ore_pe_saptamana()).c_str()));
        //Seteaza tipul
        tabel->setCellWidget(i, 2, new QLabel(lst[i].get_tip().c_str()));
        //Seteaza denumirea
        tabel->setCellWidget(i, 3, new QLabel(lst[i].get_cadru_didactic().c_str()));
    }
}

void App::conecteaza() {
    //BUTONUL ADAUGA
    QPushButton* adauga = findChild<QPushButton*>("Adauga"); // I-am dat numele "Adauga"
    auto f_adauga = [this]() {
        //Gasim Text Boxurile
        QTextEdit* dnm = findChild<QTextEdit*>("Denumire"); // I-am dat numele "Denumire"
        QTextEdit* ora = findChild<QTextEdit*>("Ora"); // I-am dat numele "Ora"
        QTextEdit* tip = findChild<QTextEdit*>("Tip"); // I-am dat numele "Tip"
        QTextEdit* cdr = findChild<QTextEdit*>("Cadru"); // I-am dat numele "Cadru"
        string s_dnm = dnm->toPlainText().toStdString();
        string s_ora = ora->toPlainText().toStdString();
        string s_tip = tip->toPlainText().toStdString();
        string s_cdr = cdr->toPlainText().toStdString();

        try {
            srv.adauga(s_dnm, stoi(s_ora), s_tip, s_cdr);
            actualizeaza_tabel("Discipline", srv.get_all());
            actualizeaza_butoane_tip();
        }
        catch (ExceptiiValidare& e) {
            creaza_prompt(e.get_Msg());
        }
        catch (exception&) {
            creaza_prompt("Nr. de ore trebuie sa fie un numar!");
        }
        delete_text_boxs();
    };
    connect(adauga, &QPushButton::released, this, f_adauga); // Dam actiune butonului "Adauga"
    //BUTONUL ADAUGA
    //BUTONUL STERGE
    QPushButton* sterge = findChild<QPushButton*>("Sterge"); // I-am dat numele "Sterge"
    auto f_sterge = [this]() {
        //Gasim Text Boxurile
        QTextEdit* dnm = findChild<QTextEdit*>("Find/Delete/Modify"); // I-am dat numele "Denumire"
        string s_dnm = dnm->toPlainText().toStdString();
        try {
            srv.sterge(s_dnm);
            actualizeaza_tabel("Discipline", srv.get_all());
            actualizeaza_butoane_tip();
        }
        catch (ExceptiiValidare& e) {
            creaza_prompt(e.get_Msg());
        }
        delete_text_boxs();
    };
    connect(sterge, &QPushButton::released, this, f_sterge); // Dam actiune butonului "Sterge"
    //BUTONUL STERGE
    //BUTONUL MODIFICA
    QPushButton* modifica = findChild<QPushButton*>("Modifica"); // I-am dat numele "Modifica"
    auto f_modifica = [this]() {
        //Gasim Text Boxurile
        QTextEdit* dnm = findChild<QTextEdit*>("Denumire"); // I-am dat numele "Denumire"
        QTextEdit* ora = findChild<QTextEdit*>("Ora"); // I-am dat numele "Ora"
        QTextEdit* tip = findChild<QTextEdit*>("Tip"); // I-am dat numele "Tip"
        QTextEdit* cdr = findChild<QTextEdit*>("Cadru"); // I-am dat numele "Cadru"
        string s_dnm = dnm->toPlainText().toStdString();
        string s_ora = ora->toPlainText().toStdString();
        string s_tip = tip->toPlainText().toStdString();
        string s_cdr = cdr->toPlainText().toStdString();

        QTextEdit* v_dnm = findChild<QTextEdit*>("Find/Delete/Modify"); // I-am dat numele "Denumire"
        string s_v_dnm = v_dnm->toPlainText().toStdString();
        try {
            srv.modifica(s_v_dnm, s_dnm,stoi(s_ora), s_tip, s_cdr);
            actualizeaza_tabel("Discipline",srv.get_all());
            actualizeaza_butoane_tip();
        }
        catch (ExceptiiValidare& e) {
            creaza_prompt(e.get_Msg());
        }
        catch (exception&) {
            creaza_prompt("Nr. de ore trebuie sa fie un numar!");
        }
        delete_text_boxs();
    };
    connect(modifica, &QPushButton::released, this, f_modifica); // Dam actiune butonului "Sterge"
    //BUTONUL MODIFICA
    //BUTONUL GASESTE
    QPushButton* gaseste = findChild<QPushButton*>("Gaseste"); // I-am dat numele "Gaseste"
    auto f_gaseste = [this]() {
        //Gasim Text Boxurile
        QTextEdit* dnm = findChild<QTextEdit*>("Find/Delete/Modify"); // I-am dat numele "Denumire"
        string s_dnm = dnm->toPlainText().toStdString();
        Disciplina d=srv.find(s_dnm);
        if (d.get_denumire() != "null")
            creaza_prompt(d.str());
        else
            creaza_prompt("Nu exista aceasta disciplina!");
        delete_text_boxs();
    };
    connect(gaseste, &QPushButton::released, this, f_gaseste); // Dam actiune butonului "Gaseste"
    //BUTONUL GASESTE
    //BUTONUL FILTREAZA ORE
    QPushButton* filtreaza_ore = findChild<QPushButton*>("F_Ore"); // I-am dat numele "F_Ore"
    auto f_filtreaza_ore = [this]() {
        //Gasim Text Boxurile
        QTextEdit* minim = findChild<QTextEdit*>("Minim"); // I-am dat numele "Minim"
        QTextEdit* maxim = findChild<QTextEdit*>("Maxim"); // I-am dat numele "Maxim"
        string s_minim = minim->toPlainText().toStdString();
        string s_maxim = maxim->toPlainText().toStdString();
        
        try {
            int m = stoi(s_minim), M = stoi(s_maxim);
            Repository repo = srv.filtreaza_dupa_nr_ore(m, M);
            actualizeaza_tabel("Filtreaza/Sorteaza", repo.get_all());
        }
        catch (exception&) {
            creaza_prompt("Nr. Minim si Nr. Maxim trebuie sa fie numere!");
        }
        
        delete_text_boxs();
    };
    connect(filtreaza_ore, &QPushButton::released, this, f_filtreaza_ore); // Dam actiune butonului "Gaseste"
    //BUTONUL FILTREAZA ORE
    //BUTONUL FILTREAZA CADRU DIDACTIC
    QPushButton* filtreaza_cadru_didactic = findChild<QPushButton*>("F_Cadru"); // I-am dat numele "F_Cadru"
    auto f_filtreaza_cadru_didactic = [this]() {
        //Gasim Text Boxurile
        QTextEdit* cdr = findChild<QTextEdit*>("Filtreaza Cadru"); // I-am dat numele "Filtreaza Cadru"
        string s_cdr = cdr->toPlainText().toStdString();
        Repository repo = srv.filtreaza_dupa_cadru_didactic(s_cdr);
        actualizeaza_tabel("Filtreaza/Sorteaza", repo.get_all());
        delete_text_boxs();
    };
    connect(filtreaza_cadru_didactic, &QPushButton::released, this, f_filtreaza_cadru_didactic); // Dam actiune butonului "Gaseste"
    //BUTONUL FILTREAZA CADRU DIDACTIC
    //BUTONUL SORTEAZA DENUMIRE
    QPushButton* sorteaza_denumire = findChild<QPushButton*>("S_Denumire"); // I-am dat numele "S_Denumire"
    auto f_sorteaza_denumire = [this]() {
        //Gasim Text Boxurile
        Repository repo = srv.sorteaza_dupa_denumire();
        actualizeaza_tabel("Filtreaza/Sorteaza", repo.get_all());
        delete_text_boxs();
    };
    connect(sorteaza_denumire, &QPushButton::released, this, f_sorteaza_denumire); // Dam actiune butonului "Gaseste"
    //BUTONUL SORTEAZA DENUMIRE
    //BUTONUL SORTEAZA ORE
    QPushButton* sorteaza_ore = findChild<QPushButton*>("S_Ore"); // I-am dat numele "S_Ore"
    auto f_sorteaza_ore = [this]() {
        //Gasim Text Boxurile
        Repository repo = srv.sorteaza_dupa_ore();
        actualizeaza_tabel("Filtreaza/Sorteaza", repo.get_all());
        delete_text_boxs();
    };
    connect(sorteaza_ore, &QPushButton::released, this, f_sorteaza_ore); // Dam actiune butonului "Gaseste"
    //BUTONUL SORTEAZA ORE
    //BUTONUL SORTEAZA CADRU SI TIP
    QPushButton* sorteaza_cadru_tip = findChild<QPushButton*>("S_Cadru_Tip"); // I-am dat numele "S_Cadru_Tip"
    auto f_sorteaza_cadru_tip = [this]() {
        //Gasim Text Boxurile
        Repository repo = srv.sorteaza_dupa_cadru_didactic_si_tip();
        actualizeaza_tabel("Filtreaza/Sorteaza", repo.get_all());
        delete_text_boxs();
    };
    connect(sorteaza_cadru_tip, &QPushButton::released, this, f_sorteaza_cadru_tip); // Dam actiune butonului "Gaseste"
    //BUTONUL SORTEAZA CADRU SI TIP
}

void App::creaza_filtreaza_sorteaza_tab() {
    QWidget* main_widget = new QWidget(); // Widgetul principal care are layout de tip grid
    QGridLayout* main_layout = new QGridLayout(); // Gridul
    main_widget->setLayout(main_layout);
    //Labelul cu titlu
    QLabel* titlu = new QLabel();
    titlu->setText("Filtreaza sau sorteaza discipline");
    titlu->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
    titlu->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(titlu, 0, 0, 1, 2); // Dupa el urmeaza 2 coloane, una cu Text-Box-urile si alta cu Disciplina
    //Labelul cu titlu
    QWidget* text_box_widget = new QWidget(); // Widget-ul pentru partea din "stanga"
    QVBoxLayout* text_box_layout = new QVBoxLayout; // Widget-urile vor fi asezate pe verticala aici
    text_box_widget->setLayout(text_box_layout);

    adauga_text_box(text_box_layout, "Nr. Minim", "Minim");
    adauga_text_box(text_box_layout, "Nr. Maxim", "Maxim");
    adauga_button(text_box_layout, "Filtreaza dupa nr. ore","F_Ore");
    adauga_text_box(text_box_layout, "Cadru didactic", "Filtreaza Cadru");
    adauga_button(text_box_layout, "Filtreaza cadru didactic", "F_Cadru");

    main_layout->setColumnStretch(1, 2);
    QWidget* text_widget = new QWidget(); // Widgetul din "dreapta"
    QVBoxLayout* text_layout = new QVBoxLayout; // Widget-urile vor fi asezate pe verticala aici
    text_widget->setLayout(text_layout);
    agauga_tabel_discipline(text_layout, "Discipline", "Filtreaza/Sorteaza");

    QWidget* butoane_widget = new QWidget();
    QHBoxLayout* butoane_layout = new QHBoxLayout(); // Butoanele vor fi asezaete pe orizontala
    butoane_widget->setLayout(butoane_layout);
    adauga_button(butoane_layout, "Sorteaza denumire", "S_Denumire");
    adauga_button(butoane_layout, "Sorteaza ore", "S_Ore");
    adauga_button(butoane_layout, "Sorteaza cadru&tip", "S_Cadru_Tip");



    main_layout->addWidget(text_box_widget);
    main_layout->addWidget(text_widget);
    main_layout->addWidget(butoane_widget, 2, 1);

    //main_widget->show();
    tabs->addTab(main_widget, "FILTREAZA/SORTEAZA");
}

void App::creaza_crud_tab() {
    QWidget* main_widget = new QWidget(); // Widgetul principal care are layout de tip grid
    QGridLayout* main_layout = new QGridLayout(); // Gridul
    main_widget->setLayout(main_layout);

    //Labelul cu titlu
    QLabel* titlu = new QLabel();
    titlu->setText("Manager discipline");
    titlu->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
    titlu->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(titlu,0,0,1,2); // Dupa el urmeaza 2 coloane, una cu Text-Box-urile si alta cu Disciplina
    //Labelul cu titlu

    QWidget* text_box_widget = new QWidget(); // Widget-ul pentru partea din "stanga"
    QVBoxLayout* text_box_layout = new QVBoxLayout; // Widget-urile vor fi asezate pe verticala aici
    text_box_widget->setLayout(text_box_layout);

    adauga_text_box(text_box_layout, "Denumire", "Denumire");
    adauga_text_box(text_box_layout, "Ora", "Ora");
    adauga_text_box(text_box_layout, "Tip", "Tip");
    adauga_text_box(text_box_layout, "Cadru didactic", "Cadru");
    adauga_button(text_box_layout, "Adauga disciplina", "Adauga");

    QWidget* text_widget = new QWidget(); // Widgetul din "dreapta"
    QVBoxLayout* text_layout = new QVBoxLayout; // Widget-urile vor fi asezate pe verticala aici
    text_widget->setLayout(text_layout);
    agauga_tabel_discipline(text_layout, "Discipline", "Discipline");




    QWidget* butoane = new QWidget(); // Widget-ul cu cele 3 butoane
    QHBoxLayout* layout_butoane = new QHBoxLayout(); // De data asta le punem pe orizontala
    butoane->setLayout(layout_butoane);

    adauga_button(layout_butoane, "Sterge", "Sterge");
    adauga_button(layout_butoane, "Gaseste", "Gaseste");
    adauga_button(layout_butoane, "Modifica", "Modifica");


    main_layout->addWidget(text_box_widget); // Adauga Widget-ul la main_widget
    main_layout->setColumnStretch(1, 2);
    main_layout->addWidget(text_widget); // Adauga Widget-ul la main_widget
    adauga_text_box(main_layout, "Denumire", "Find/Delete/Modify");
    main_layout->addWidget(butoane);

    //Creaza TAB
    tabs->addTab(main_widget, "CRUD");
}

void App::creaza_butoane_tab() {
    QWidget* main_widget = new QWidget(); // Widgetul principal care are layout de tip grid
    QGridLayout* main_layout = new QGridLayout(); // Gridul
    main_widget->setLayout(main_layout);

    //Labelul cu titlu
    QLabel* titlu = new QLabel();
    titlu->setText("Manager discipline");
    titlu->setStyleSheet("font-size: 20px;font-weight: bold;color: #ACADA8;");
    titlu->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(titlu, 0, 0, 1, 2); // Dupa el urmeaza 2 coloane, una cu Text-Box-urile si alta cu Disciplina
    //Labelul cu titlu



    QWidget* text_widget = new QWidget(); // Widgetul din "stanga"
    QVBoxLayout* text_layout = new QVBoxLayout; // Widget-urile vor fi asezate pe verticala aici
    text_widget->setLayout(text_layout);
    agauga_tabel_discipline(text_layout, "Discipline Filtrate", "D_Filtrate");

    QWidget* buttons_widget = new QWidget(); // Widgetul din "dreapta"
    btn_layout = new QVBoxLayout;
    buttons_widget->setLayout(btn_layout);
    /*adauga_button(btn_layout, "TIP", "TIP");
    adauga_button(btn_layout, "TIP2", "TIP");
    adauga_button(btn_layout, "TIP3", "TIP");*/

    /*auto item = btn_layout->takeAt(0);
    delete item->widget();
    delete item;*/


    main_layout->setColumnStretch(0, 2);
    main_layout->addWidget(text_widget); // Adauga Widget-ul la main_widget
    main_layout->addWidget(buttons_widget);

    //Creaza TAB
    tabs->addTab(main_widget, "BUTOANE");
}

void App::actualizeaza_butoane_tip() {
    QLayoutItem* item;
    actualizeaza_tabel("D_Filtrate", srv.get_all());
    while ((item = btn_layout->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }
    vector<string>tipuri;
    vector<Disciplina>lst = srv.get_all();
    for (auto el : lst) {
        string tip = el.get_tip();
        bool ok = true;
        for (auto el_2 : tipuri) {
            if (el_2 == tip)
                ok = false;
        }
        if (ok) {
            tipuri.push_back(tip);
        }
    }
    for (auto el : tipuri) {
        adauga_button(btn_layout, el, el + "NUME");
        string nume = el + "NUME";

        QPushButton* button = findChild<QPushButton*>(nume.c_str());
        auto f_button = [this,el,lst]() {
            int cnt = 0;
            for (auto disciplina : lst) {
                if (disciplina.get_tip() == el) {
                    cnt++;
                }
            }
            string contor = to_string(cnt);
            creaza_prompt("Numarul de discipline va fi: "+ contor);

        };
        connect(button, &QPushButton::released, this, f_button);
    }
}
