//
// Created by Laura on 4/8/2022.
//

#include "UI.h"
#include <iostream>

using namespace std;
void ConsoleUI::printMenu() {
    cout << "COMENZI DISPONIBILE:" << endl;
    cout << "1.AFISEAZA produsele." << endl;
    cout << "2. ADAUGA produs." << endl;
    cout << "3.CAUTA un anumit produs." << endl;
    cout << "4.RANDOMIZE adaugare produse." << endl;
    cout << "5.STERGE un anumit produs." << endl;
    cout << "6.MODIFICATI pretul unui anumit produs" << endl;
    cout << "7.FILTRATI produse dupa un anumit criteriu" << endl;
    cout << "8.SORTARE produse" << endl;
    cout<<"9.COS PRODUSE MENIU"<<endl;
    cout<<"10.DTO"<<endl;
    cout<<"11.UNDO"<<endl;
    cout << "0.EXIT" << endl;
}

void ConsoleUI::printListMenu() {
    cout << "MENIU COS DE CUMPARATURI"<< endl;
    cout << "1. Adauga produs in cos" << endl;
    cout << "2. Adauga produse random in cos" << endl;
    cout << "3. Goleste cosul" << endl;
    cout << "4. Afiseaza cosul curent" << endl;
    cout<<"5.Export cos cumparaturi"<<endl;
    cout << "6. Inapoi la meniul principal" << endl;
}

void ConsoleUI::uiAdd() {
    string nume,tip,producator;
    double pret;
    cout << "Numele produsului este:";
    getline(cin >> ws, nume);

    cout << "Tipul produsului este:";
    getline(cin >> ws, tip);
    cout << "Producatorul produsului este:";
    getline(cin >> ws, producator);

    cout << "Pretul produsului (numar real>0) este:";
    cin >> pret;
    try {
        srv.addservice(nume,tip,producator,pret);
        cout << "Produsul a fost adaugat cu succes." << endl;
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationExcep& ve) {
        cout << "Produsul nu este valid!" << endl;
        cout << ve.getErrorMessages();
    }

}

void ConsoleUI::uiDell() {
    string nume, tip, producator;
    double pret;
    cout << "Numele produsului pe care doriti sa il stergeti  este:";
    getline(cin >> ws, nume);

    cout << "Tipul produsului pe care doriti sa il stergeti este:";
    getline(cin >> ws, tip);
    cout << "Producatorul produsului este:";
    getline(cin >> ws, producator);

    cout << "Pretul produsului (numar real>0) este:";
    cin >> pret;
    try {
        srv.dellservice(nume, tip, producator, pret);
        cout << "Produsul a fost sters cu succes." << endl;
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationExcep& ve) {
        cout << "Produsul nu este valid!" << endl;
        cout << ve.getErrorMessages();
    }

}

void ConsoleUI::uiModify() {
    string nume, tip, producator;
    //string pret;
    double pretnou;
    cout << "Numele produsului pe care doriti sa il modificati  este:";
    getline(cin >> ws, nume);

    cout << "Tipul produsului pe care doriti sa il modificati este:";
    getline(cin >> ws, tip);
    cout << "Producatorul produsului este:";
    getline(cin >> ws, producator);


    cout << " Pretul nou al produsului: ";
    cin >> pretnou;
    //getline(cin >> ws, pret);
    //pretnou = stod(pret);
    try {
        srv.modifyservice(nume, tip, producator, pretnou);
        cout << "Produsul a fost fost modificat cu succes." << endl;
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationExcep& ve) {
        cout << "Produsul nu este valid!" << endl;
        cout << ve.getErrorMessages();
    }

}


void ConsoleUI::uiFind() {
    string nume, producator;
    Produs prod;
    cout << "Numele produsului pe care il cautati este:";
    getline(cin >> ws, nume);

    cout << "Producatorul produsului pe care il cautati este:";
    getline(cin >> ws, producator);

    try {
        prod = srv.findservice(nume, producator);
        cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationExcep& ve) {
        cout << "datele nu sunt valide!" << endl;
        cout << ve.getErrorMessages();
    }

}

void ConsoleUI::uiRandomize() {
    srv.addservice("masca", "cosmetic", "the body shop", 80.5);
    srv.addservice("paine", "alimentar", "vel pitar", 2.8);
    srv.addservice("aspirator", "electrocasnic", "electrolux",256);
    srv.addservice("cuptor", "electrocasnic", "electrolux", 569);
    srv.addservice("apa","alimentar","dorna",5.2);
    srv.addservice("stilou","papetarie","herlitz",25);
}

void ConsoleUI::uiFiltreaza() {
    cout << "Optiune 1-dupa tip\n";
    cout << "Optiune 2-dupa producator\n";
    cout << "Optiune 3-dupa nume\n";
    cout << "Optiunea aleasa este:";
    int filtru;
    string tip,prod, nume;
    cin >> filtru;
    if (filtru == 1)
    {
        cout << "Introduceti tipul dupa care doriti filtrarea:";
        getline(cin >> ws, tip);
        if (srv.filtreaza_tip(tip).size() == 0)
            cout << "Nu exista produse cu acest tip\n";
        for (const auto& prod1 : srv.filtreaza_tip(tip)) {
            cout << "NUME: " << prod1.getNume() << " | TIP: " << prod1.getTip() << " | PRODUCATOR: " << prod1.getProd() << " | PRET: " << prod1.getPret() << endl;
        }
    }
    if (filtru == 2)
    {

        cout << "Introduceti producatorul dupa care doriti filtrarea:";
        getline(cin >> ws, prod);
        if (srv.filtreaza_prod(prod).size() == 0)
            cout << "Nu exista produse cu acest producator\n";
        for (const auto& prod : srv.filtreaza_prod(prod)) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
    }
    if (filtru == 3)
    {
        cout << "Introduceti numele dupa care doriti filtrarea:";
        getline(cin >> ws, nume);
        if (srv.filtreaza_nume(nume).size() == 0)
            cout << "Nu exista produse cu acest nume\n";
        for (const auto& prod : srv.filtreaza_nume(nume)) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
    }

}

void ConsoleUI::uiSort() {
    int ordine, optiune;
    cout << "Sortati dupa:"<<endl;
    cout << "1-Nume   2-Pret   3-Nume si Tip" << endl;
    cin >> optiune;
    cout << "Ordinea sa fie : 0-crescator   1-descrescator" << endl;
    cin >> ordine;
    if (optiune == 1)
    {
        for (const auto& prod : srv.sortnume(ordine)) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
    }
    if (optiune == 2)
    {
        for (const auto& prod : srv.sortpret(ordine)) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
    }
    if (optiune == 3)
    {
        for (const auto& prod : srv.sortNumeTip(ordine)) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
    }

}


void ConsoleUI::printAllProducts() {
    vector <Produs>& allproducts = srv.getallproducts();
    if (allproducts.size() == 0)
        cout << "Nu exista produse." << endl;
    else
        for (const auto& prod : allproducts) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
}

void ConsoleUI::uiValoare_Cos(const vector <Produs>& allproducts) {
    double valoare=0;
    if (allproducts.size() == 0)
        cout << "Nu exista produse." << endl;
    else {

        for (const auto &prod: allproducts) {
            valoare = valoare + prod.getPret();
        }
        cout << "Valoarea produselor din cos este" << " " << valoare<<endl;
    }

}


void ConsoleUI::printAllfromlist() {
    const vector <Produs>& allproducts = srv.getallfromlistsrv();
    if (allproducts.size() == 0)
        cout << "Nu exista produse." << endl;
    else
        for (const auto& prod : allproducts) {
            cout << "NUME: " << prod.getNume() << " | TIP: " << prod.getTip() << " | PRODUCATOR: " << prod.getProd() << " | PRET: " << prod.getPret() << endl;
        }
}

void ConsoleUI::uiaddlist() {
    string nume, prod;
    cout << "Numele produsului este:";
    getline(cin >> ws, nume);

    cout << "Producatorul produsului este:";
    getline(cin >> ws, prod);

    try {
        srv.addlistsrv(nume, prod);
        cout << "Produsul s-a adaugat cu succes in cos." << endl;
        const vector <Produs>& allproducts = srv.getallfromlistsrv();
        uiValoare_Cos(allproducts);
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationExcep& ve) {
        cout << "Produsul nu este valid!" << endl;
        cout << ve.getErrorMessages();
    }
}
void ConsoleUI::uiaddrandomlist() {
    int howManyToAdd;
    cout << "Cate produse sa se adauge in cos?";
    cin >> howManyToAdd;


    try {
        int howManyAdded = srv.addrandomsrv(howManyToAdd);
        cout << "S-au adaugat " << howManyAdded-1 << " produse in cos." << endl;
        const vector <Produs>& allproducts = srv.getallfromlistsrv();
        uiValoare_Cos(allproducts);
    }
    catch (RepoExcep& re) {
        cout << re.getErrorMessage();
    }
}

void ConsoleUI::uiemptylist() {
    srv.emptylistsrv();
    cout << "S-au sters toate produsele din cosul curent." << endl;
    cout<<"Valoarea produselor din cos este 0"<<endl;
}

void ConsoleUI::uiDto() {
        auto dict = srv.get_dict();
        for (auto& el : dict) {
            cout << "Key: " << el.first << " Tip: " << el.second.getTip() << " Nr: "<< el.second.get_nr() << '\n';

    }
}

void ConsoleUI::uiexport(){
        cout << "Introduceti fisierul in care se exporta produsele:";
        string fisier;
        cin >> fisier;
        srv.exportsrv(fisier);
    }

void ConsoleUI::uiundo() {
    try {
        srv.undo();
        cout << "Undo realizat cu succes!\n";
    }
    catch (const UndoException& ue) {
        cout << ue.get_msg();
    }
}


void ConsoleUI::uiCos() {
    int cmd;
    int runninglist = 1;
    while (runninglist) {
        printListMenu();
        cout << "Comanda este:";
        cin >> cmd;
        switch (cmd)
        {
            case 1:
                uiaddlist();
                break;
            case 2:
                uiaddrandomlist();
                break;
            case 3:
                uiemptylist();
                break;

            case 4:
                printAllfromlist();
                break;
            case 6:
                runninglist = 0;
                break;
            case 5:
                uiexport();
                break;
            default:
                break;
        }

    }
}

void ConsoleUI::run() {
    int running = 1;
    int cmd;
    while (running) {
        printMenu();
        cout << "Comanda este:";
        cin >> cmd;
        switch (cmd)
        {
            case 2:
                uiAdd();
                break;
            case 1:
                printAllProducts();
                break;
            case 3:
                uiFind();
                break;
            case 4:
                uiRandomize();
                break;
            case 5:
                uiDell();
                break;
            case 6:
                uiModify();
                break;
            case 7:
                uiFiltreaza();
                break;
            case 8:
                uiSort();
                break;
            case 9:
                uiCos();
                break;
            case 10:
                uiDto();
                break;
            case 11:
                uiundo();
                break;
            case 0:
                running = 0;
                break;
            default:
                break;
        }

    }
}
