#pragma once
#include<iostream>
#include "domain.h"
#include "repo.h"
#include "service.h"

class Console {
private:
	/*
	Aici e reprezentarea interna
	*/
	Service srv;

	/*
	Citeste de la tastatura optiuniile necesare pentru a adauga o disciplina
	*/
	void ui_adauga();

	/*
	Citeste de la tastatura optiuniile necesare pentru a sterge o disciplina
	*/
	void ui_sterge();

	/*
	Citeste de la tastatura optiuniile necesare pentru a modifica o disciplina
	*/
	void ui_modifica();

	/*
	Afiseaza pe ecran toate disciplinele adaugate pana in momentul actual
	*/
	void ui_print_all();

	/*
	Afiseaza meniul cu optiuni
	*/
	void ui_print_menu();

	/*
	Gasseste o anumita Disciplina
	*/
	void ui_find_disciplina();

	/*
	Filtreaza disciplinele dupa numarul de ore
	*/
	void ui_filtreaza_discipline_nr_ore();

	/*
	Filtreaza disciplinele dupa cadrul didactic
	*/
	void ui_filtreaza_discipline_nr_cadru_didactic();

	/*
	Sorteaza dupa denumirea disciplinei
	*/
	void ui_sorteaza_dupa_denumire();

	/*
	Sorteaza dupa orele pe saptamana
	*/
	void ui_sorteaza_dupa_ore();

	/*
	Sorteaza dupa cadru didactic si tip
	*/
	void ui_sorteaza_dupa_cadru_didactic_si_tip();

	/*
	Afiseaza meniul cu optiuniile contractului
	*/
	void ui_print_menu_contract();

	/*
	Adauga un contract
	*/
	void ui_adauga_contract();

	/*
	Goleste contractul
	*/
	void ui_goleste_contract();

	/*
	Genereaza contracte din lista de discipline
	*/
	void ui_genereaza_contracte();

	/*
	Afiseaza la tastatura toate contractele
	*/
	void ui_print_contracte();

	/*
	Sterge toate contractele de un anumit tip
	*/
	void ui_sterge_tip();

	/*
	Salveaza contractul intr-un fisier
	*/
	void ui_salveaza_contract();

	/*
	Face undo la lista de discipline
	*/
	void ui_undo();

public:
	/*
	Aici e interfata publica
	*/

	/*
	Initializeaza un obiect de tip Console
	srv->Service, service-ul disciplinelor
	*/
	Console(const Service& srv);

	/*
	Porneste aplicatia
	*/
	void start();

};