#pragma once
#include<iostream>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "console.h"
#include <string>
#include <exception>

using namespace std;

Console::Console(const Service& srv) {
	this->srv = srv;

}

void Console::ui_adauga() {
	string denumire, tip, cadru_didactic,ore_pe_saptamana;
	int o;
	cout << "Denumire: ";
	getline(cin,denumire);
	cout << "Ore pe saptamana: ";
	getline(cin, ore_pe_saptamana);
	try {
		o = stoi(ore_pe_saptamana);
	cout << "Tip: ";
	getline(cin, tip);
	cout << "Cadru didactic: ";
	getline(cin, cadru_didactic);
	try {

	Disciplina d = this->srv.adauga(denumire, stoi(ore_pe_saptamana), tip, cadru_didactic);
	cout << d.str() + "\nA fost adaugata cu succes!\n";
	}
	catch (exception&) {
		cout << "Deja exista aceasta denumire!\n";
	}
	}
	catch(exception&){
		cout << "Orele pe saptamana trebuie sa fie un numar!!\n";
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
	catch (exception&) {
		cout << "Denumirea nu exista!\n";
	}
}

void Console::ui_modifica() {
	try {
		int o;
	string denumire, tip, cadru_didactic,denumire_cautata,ore_pe_saptamana;
	cout << "Denumirea disciplinei cautate este: ";
	getline(cin, denumire_cautata);
	cout << "Noile propietati vor fi:\nDenumire: ";
	getline(cin, denumire);
	cout << "Ore pe saptamana: ";
	getline(cin, ore_pe_saptamana);
	o = stoi(ore_pe_saptamana);
	cout << "Tip: ";
	getline(cin, tip);
	cout << "Cadru didactic: ";
	getline(cin, cadru_didactic);
	try {

	Disciplina d = this->srv.modifica(denumire_cautata, denumire, stoi(ore_pe_saptamana), tip, cadru_didactic);

	if (d.get_denumire() != "null") {
		cout << d.str() + "\nA fost actualizata cu succes!\n";
	}
	else {
		cout << "Disciplina cautata nu exista!\n";
	}

	}
	catch (exception&) {
		cout << "Disciplina nu exista sau noua denumire deja exista!\n";
	}

	}
	catch (exception&) {
		cout << "Orele pe saptamana trebuie sa fie un numar!!\n";
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
	try{
	string numarul_minim, numarul_maxim;
	int nr;
	cout << "Numarul minim de ore va fi: ";
	getline(cin, numarul_minim);
	nr = stoi(numarul_minim);
	cout << "Numarul maxim de ore va fi: ";
	getline(cin, numarul_maxim);
	nr = stoi(numarul_maxim);
	Repository repo = srv.filtreaza_dupa_nr_ore(stoi(numarul_minim), stoi(numarul_maxim));
	cout << repo.str();
	}
	catch (exception&) {
		cout << "Orele pe saptamana trebuie sa fie un numar!!\n";
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
		else if (cmd == "x" || cmd == "X") {
			break;
		}
		else {
			cout << "Comanda este gresita!\n";
		}
	}
}