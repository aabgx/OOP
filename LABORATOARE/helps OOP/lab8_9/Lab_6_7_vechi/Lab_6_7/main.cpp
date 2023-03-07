#pragma once
#include <iostream>
#include "teste_domain.h"
#include "teste_repo.h"
#include "teste_service.h"
#include "service.h"
#include "console.h"
#include "teste_vector.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
	//SERVICE

	//VECTOR
	test_size();
	test_push_back();
	test_get();
	test_clear();
	test_resize();
	test_erase();
	//VECTOR
}

int main() {
	test_all();

	{
		Service srv;
		Console console(srv);
		console.start(); 
	}
	_CrtDumpMemoryLeaks();
	return 0;
}