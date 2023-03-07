#pragma once
#include<iostream>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "console.h"
#include <string>
#include <exception>
#include "validator.h"

using namespace std;

Console::Console(const Service& srv) {
	this->srv = srv;

}

void Console::ui_adauga() {
	string denumire, tip, cadru_didactic,ore_pe_saptamana;
	Validator v;
	int o;
	cout << "Denumire: ";
	getline(cin,denumire);
	cout << "Ore pe saptamana: ";
	getline(cin, ore_pe_saptamana);
	try {
	cout << "Tip: ";
	getline(cin, tip);
	cout << "Cadru didactic: ";
	getline(cin, cadru_didactic);
	v.valideaza_disciplina(denumire, ore_pe_saptamana, tip, cadru_didactic);
	o = stoi(ore_pe_saptamana);
	Disciplina d = this->srv.adauga(denumire, stoi(ore_pe_saptamana), tip, cadru_didactic);
	cout << d.str() + "\nA fost adaugata cu succes!\n";
	}
	catch(ExceptiiValidare& e){
		cout << e.get_Msg();
	}
}

void Console::ui_sterge() {
	string denumire;
	cout << "Denumire: ";
	getline(cin, denumire);
	try {

	Disciplina d = this->srv.sterge(denumire);

		cout << d.str() + "\nA fost stersa cu succes!\n";
	}
	catch (ExceptiiValidare& e) {
		cout << e.get_Msg();
	}
}

void Console::ui_modifica() {
	Validator v;
	try {
		int o;
	string denumire, tip, cadru_didactic,denumire_cautata,ore_pe_saptamana;
	cout << "Denumirea disciplinei cautate este: ";
	getline(cin, denumire_cautata);
	cout << "Noile propietati vor fi:\nDenumire: ";
	getline(cin, denumire);
	cout << "Ore pe saptamana: ";
	getline(cin, ore_pe_saptamana);
	cout << "Tip: ";
	getline(cin, tip);
	cout << "Cadru didactic: ";
	getline(cin, cadru_didactic);

	v.valideaza_disciplina(denumire, ore_pe_saptamana, tip, cadru_didactic);
	o = stoi(ore_pe_saptamana);

	Disciplina d = this->srv.modifica(denumire_cautata, denumire, stoi(ore_pe_saptamana), tip, cadru_didactic);

	cout << d.str() + "\nA fost actualizata cu succes!\n";
	}
	catch (ExceptiiValidare& e) {
		cout << e.get_Msg();
	}
}

void Console::ui_print_all() {
	cout << "Disciplinele sunt:\n"<<this->srv.str();
}

void Console::ui_print_menu() {
	cout << "1. Adauga o disciplina\n";
	cout << "2. Sterge o disciplina\n";
	cout << "3. Modifica o disciplina\n";
	cout << "4. Gaseste o disciplina\n";
	cout << "5. Filtreaza discipline dupa numarul de ore\n";
	cout << "6. Filtreaza discipline dupa cadru didactic\n";
	cout << "7. Sorteaza dupa denumire\n";
	cout << "8. Sorteaza dupa numarul de ore\n";
	cout << "9. Sorteaza dupa cadru didactic si tip\n";
	cout << "P. Afiseaza toate disciplinele\n";
	cout << "C. Contract\n";
	cout << "U. Undo\n";
	cout << "X. Exit\n";
}

void Console::ui_find_disciplina() {
	string denumire;
	cout << "Denumirea disciplinei cautate este: ";
	getline(cin, denumire);
	Disciplina d = this->srv.find(denumire);
	if (d.get_denumire() == "null")cout << "Disciplina cautata nu exista!\n";
	else cout << "Disciplina cautata este: \n"+d.str() + "\n";
}

void Console::ui_filtreaza_discipline_nr_ore() {
	Validator v;
	try{
	string numarul_minim, numarul_maxim;
	cout << "Numarul minim de ore va fi: ";
	getline(cin, numarul_minim);
	cout << "Numarul maxim de ore va fi: ";
	getline(cin, numarul_maxim);

	v.valideaza_numere(numarul_minim, numarul_maxim);
	Repository repo = srv.filtreaza_dupa_nr_ore(stoi(numarul_minim), stoi(numarul_maxim));
	cout << repo.str();
	}
	catch (ExceptiiValidare& e) {
		cout << e.get_Msg();
	}
}

void Console::ui_filtreaza_discipline_nr_cadru_didactic() {
	string cadru_didactic;
	cout << "Cadrul didactic va fi: ";
	getline(cin, cadru_didactic);
	Repository repo = srv.filtreaza_dupa_cadru_didactic(cadru_didactic);
	cout << repo.str();
}

void Console::ui_sorteaza_dupa_denumire() {
	Repository repo = srv.sorteaza_dupa_denumire();
	cout << repo.str();
}

void Console::ui_sorteaza_dupa_ore() {
	Repository repo = srv.sorteaza_dupa_ore();
	cout << repo.str();
}

void Console::ui_sorteaza_dupa_cadru_didactic_si_tip() {
	Repository repo = srv.sorteaza_dupa_cadru_didactic_si_tip();
	cout << repo.str();
}

void Console::ui_print_menu_contract() {
	cout << "1. Adauga un contract\n";
	cout << "2. Goleste contractele\n";
	cout << "3. Genereaza aleator contracte\n";
	cout << "4. Sterge toate contractele cu un anumit tip\n";
	cout << "S. Salveaza contract\n";
	cout << "P. Afiseaza toate contractele\n";
	cout << "X. Exit\n";
}



void Console::ui_adauga_contract() {
	try{ 
	string denumire;
	cout << "Denumirea disciplinei pe care doriti sa o adaugati in contract este:";
	getline(cin, denumire);
	Disciplina d = srv.adauga_in_contract(denumire);
	cout << "Disciplina: " << d.str() << " a fost adaugata cu succes!\n";
	}
	catch (ExceptiiValidare& el) {
		cout << el.get_Msg();
	}
}

void Console::ui_goleste_contract() {
	srv.goleste();
	cout << "Toate contractele au fost sterse!\n";
}

void Console::ui_genereaza_contracte() {
	Validator v;
	try {
		cout << "Numarul de generari aleatoare este:";
		string nr;
		getline(cin, nr);
		v.valideaza_nr_de_generare(nr);
		int n = stoi(nr);
		srv.genereaza_contracte(n);
		cout << "Au fost adaugate " << n << " contracte!\n";
	}
	catch (ExceptiiValidare& e) {
		cout << e.get_Msg();
	}
}

void Console::ui_print_contracte() {
	cout << srv.str_contract();
}

void Console::ui_sterge_tip() {
	string tip;
	cout << "Tipul va fi: ";
	getline(cin, tip);
	srv.sterge_tip(tip);
}

void Console::ui_salveaza_contract() {
	string nume_fisier;

	cout << "Numele fisierului HTML va fi:";
	getline(cin, nume_fisier);
	if (nume_fisier.size() > 4)
	{
	string extensie = nume_fisier.substr(nume_fisier.size()-5,5);
	if (extensie != ".html") {
		cout << "Fisierul dat nu este de tipul HTML!\n";
	}
	else {
		srv.salveaza_contract(nume_fisier);
		cout << "Contract salvat cu succes!\n";
	}
	}
	else {
		cout << "Fisierul dat nu este de tipul HTML!\n";
	}
}

void Console::ui_undo() {
	try {
		srv.undo();
		cout << "Undo realizat cu succes!\n";
	}
	catch (exception&) {
		cout << "Nu se mai poate fac undo!\n";
	}
}

void Console::start() {
	while (1) {
		this->ui_print_menu();
		string cmd;
		cout << "Optiunea dvs este: ";
		getline(cin,cmd);
		if (cmd == "1") {
			this->ui_adauga();
		}
		else if (cmd == "2") {
			this->ui_sterge();
		}
		else if (cmd == "3") {
			this->ui_modifica();
		}
		else if (cmd == "4"){
			this->ui_find_disciplina();
		}
		else if (cmd == "5") {
			this->ui_filtreaza_discipline_nr_ore();
		}
		else if (cmd == "6") {
			this->ui_filtreaza_discipline_nr_cadru_didactic();
		}
		else if(cmd == "7") {
			this->ui_sorteaza_dupa_denumire();
		}
		else if (cmd == "8") {
			this->ui_sorteaza_dupa_ore();
		}
		else if (cmd == "9") {
			this->ui_sorteaza_dupa_cadru_didactic_si_tip();
		}
		else if (cmd == "P" || cmd == "p") {
			this->ui_print_all();
		}
		else if (cmd == "U" || cmd == "u") {
			ui_undo();
		}
		else if (cmd == "C" || cmd == "c") {
			while (true) {
				ui_print_menu_contract();
				string cmd2;
				cout << "Optiunea dvs este: ";
				getline(cin, cmd2);
				if (cmd2 == "1") {
					ui_adauga_contract();
				}
				else if (cmd2 == "2") {
					ui_goleste_contract();
				}
				else if (cmd2 == "3") {
					ui_genereaza_contracte();
				}
				else if (cmd2 == "4") {
					ui_sterge_tip();
				}
				else if (cmd2 == "S" || cmd2 == "s") {
					ui_salveaza_contract();
				}
				else if (cmd2 == "P" || cmd2 == "p") {
					ui_print_contracte();
				}
				else if (cmd2 == "X" || cmd2 == "x") {
					break;
				}
				else {
					cout << "Comanda este gresita!\n";
				}
				cout << "Numarul de contracte este: " << srv.nr_contracte() << "\n";
			}
		}
		else if (cmd == "x" || cmd == "X") {
			break;
		}
		else {
			cout << "Comanda este gresita!\n";
		}
	}
}