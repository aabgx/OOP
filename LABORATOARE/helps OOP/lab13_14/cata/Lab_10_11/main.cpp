#include "App.h"
#include <QtWidgets/QApplication>
#pragma once
#include <iostream>
#include "teste_domain.h"
#include "teste_repo.h"
#include "teste_service.h"
#include "service.h"
//#include "teste_vector.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "teste_contract_repo.h"
#include "teste_validator.h"
#include "teste_undo.h"


void test_all() {
	//DOMAIN
	test_creaza();
	test_modifica();
	test_egale();
	test_str_disciplina();
	test_str_repo();
	//DOMAIN

	//REPO
	test_creaza_repo();
	test_get_all();
	test_adauga();
	test_sterge();
	test_find();
	//REPO

	//SERVICE
	test_creaza_service();
	test_adauga_service();
	test_find_service();
	test_modifica_service();
	test_sterge_service();
	test_str_service();
	test_filtreaza_dupa_nr_ore();
	test_filtreaza_dupa_cadru_didactic();
	test_sorteaza_dupa_denumire();
	test_sorteaza_dupa_ore();
	test_sorteaza_dupa_cadru_didactic_si_tip();
	test_salveaza_contract();
	test_undo_srv();
	//CONTRACTE
	test_adauga_in_contract();
	test_str_service_contract();
	test_goleste();
	test_genereaza();
	sterge_tip();
	// CONTRACTE
	//SERVICE

	//VALIDATOR
	test_valideaza_disciplina();
	test_valideaza_numere();
	test_valideaza_nr_de_generare();
	//VALIDATOR

	//CONTRACT REPO
	test_adauga_contract();
	test_clear_contract();
	test_str_contract();
	//CONTRACT REPO

	//UNDO
	test_undo_adauga();
	test_undo_sterge();
	test_undo_modifica();
	//UNDO

}


int main(int argc, char *argv[])
{
	test_all();
	Service srv;
    QApplication a(argc, argv);
    App w(srv);
    w.show();
    return a.exec();
}
