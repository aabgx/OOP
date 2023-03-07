#pragma once
#include "service.h"
#include "repo.h"
#include "domain.h"
#include <cassert>

void test_creaza_service() {
	Service srv;
	assert(srv.get_size() == 0);
}

void test_adauga_service() {
	Service srv;
	assert(srv.get_size() == 0);

	//1
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	assert(d.egale(srv.find("denumire")));
	assert(srv.get_size() == 1);

	//2
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	Disciplina d2("denumire2", 12, "tip2", "cadru_didactic2");
	assert(d2.egale(srv.find("denumire2")));
	assert(srv.get_size() == 2);

	//3
	try {
		srv.adauga("denumire", 1, "tip", "cadru_didactic");
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}

void test_find_service() {
	Service srv;
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	assert(d.egale(srv.find("denumire")));
	assert(srv.get_size() == 1);
	Disciplina nu_exista = srv.find("nu_exista");
	assert(nu_exista.get_denumire() == "null");

}

void test_modifica_service() {
	Service srv;
	assert(srv.get_size() == 0);

	//1
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	assert(d.egale(srv.find("denumire")));
	assert(srv.get_size() == 1);
	Disciplina noua_disciplina("new_denumire", 2, "new_tip", "new_cadru_didactic");
	srv.modifica("denumire", "new_denumire", 2, "new_tip", "new_cadru_didactic");
	assert(noua_disciplina.egale(srv.find("new_denumire")));

	//2
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	Disciplina d2("denumire2", 12, "tip2", "cadru_didactic2");
	assert(d2.egale(srv.find("denumire2")));
	assert(srv.get_size() == 2);
	Disciplina noua_disciplina2("new_denumire2", 22, "new_tip2", "new_cadru_didactic2");
	srv.modifica("denumire2", "new_denumire2", 22, "new_tip2", "new_cadru_didactic2");
	assert(noua_disciplina2.egale(srv.find("new_denumire2")));

	//3
	try {

	srv.modifica("nu_exista","new_denumire3", 20, "new_tip", "new_cadru_didactic");
	assert(false);
	}
	catch (exception&) {
		assert(true);
	}

}

void test_sterge_service() {
	Service srv;
	assert(srv.get_size() == 0);

	//1
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	assert(d.egale(srv.find("denumire")));
	assert(srv.get_size() == 1);
	Disciplina d_stearsa = srv.sterge("denumire");
	assert(srv.get_size() == 0);
	assert(d_stearsa.egale(d));

	//2
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");
	d_stearsa = srv.sterge("denumire");
	assert(srv.get_size() == 2);
	assert(d_stearsa.egale(d));
	srv.sterge("denumire2");
	assert(srv.get_size() == 1);
	srv.sterge("denumire3");
	assert(srv.get_size() == 0);

	//3
	try {
		srv.sterge("nu_exista");
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

}
void test_str_service() {
	Service srv;
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	assert(srv.str() == d.str() + "\n");
}

void test_filtreaza_dupa_nr_ore() {
	Service srv;
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(i), i, "tip", "cadru_didactic");
	}
	Repository rezultat = srv.filtreaza_dupa_nr_ore(1,2);
	assert(rezultat.get_size() == 2);
	rezultat = srv.filtreaza_dupa_nr_ore(1, 5);
	assert(rezultat.get_size() == 5);
	rezultat = srv.filtreaza_dupa_nr_ore(1, 20);
	assert(rezultat.get_size() == 20);
	rezultat = srv.filtreaza_dupa_nr_ore(100, 200);
	assert(rezultat.get_size() == 1);
	rezultat = srv.filtreaza_dupa_nr_ore(101, 200);
	assert(rezultat.get_size() == 0);

}

void test_filtreaza_dupa_cadru_didactic() {
	Service srv;
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(i), i, "tip", "cadru_didactic" + to_string(i / 5));
	}
	Repository rezultat = srv.filtreaza_dupa_cadru_didactic("cadru_didactic0");
	assert(rezultat.get_size() == 5);
	rezultat = srv.filtreaza_dupa_cadru_didactic("cadru_didactic13");
	assert(rezultat.get_size() == 5);

	srv.adauga("dr1", 1, "tip", "c1");
	srv.adauga("dr12", 1, "tip", "c1");
	srv.adauga("dr13", 1, "tip", "c1");
	srv.adauga("dr14", 1, "tip", "c1");
	srv.adauga("dr15", 1, "tip", "c1");
	srv.adauga("dr16", 1, "tip", "c1");
	srv.adauga("dr17", 1, "tip", "c1");

	rezultat = srv.filtreaza_dupa_cadru_didactic("c1");
	assert(rezultat.get_size() == 7);
}
void test_sorteaza_dupa_denumire() {
	Service srv;
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(i), i, "tip", "cadru_didactic" + to_string(i));
	}
	Repository rezultat = srv.sorteaza_dupa_denumire();
	assert(rezultat.get_size() == 101);
	VectorDinamic < Disciplina >lst= rezultat.get_all();
	for (int i = 0; i < 100; i++)
	{
		assert(lst[i].get_denumire() <= lst[i + 1].get_denumire());
	}
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(-i-1), i, "tip", "cadru_didactic" + to_string(i));
	}
	rezultat = srv.sorteaza_dupa_denumire();
	assert(rezultat.get_size() == 202);
	lst = rezultat.get_all();
	for (int i = 0; i < 201; i++)
	{
		assert(lst[i].get_denumire() <= lst[i + 1].get_denumire());
	}
}
void test_sorteaza_dupa_ore() {
	Service srv;
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(i), i, "tip", "cadru_didactic" + to_string(i));
	}
	Repository rezultat = srv.sorteaza_dupa_ore();
	assert(rezultat.get_size() == 101);
	VectorDinamic < Disciplina >lst = rezultat.get_all();
	for (int i = 0; i < 100; i++)
	{
		assert(lst[i].get_ore_pe_saptamana() <= lst[i + 1].get_ore_pe_saptamana());
	}
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(-i-1), i, "tip", "cadru_didactic" + to_string(i));
	}
	rezultat = srv.sorteaza_dupa_ore();
	assert(rezultat.get_size() == 202);
	lst = rezultat.get_all();
	for (int i = 0; i < 201; i++)
	{
		assert(lst[i].get_ore_pe_saptamana() <= lst[i + 1].get_ore_pe_saptamana());
	}
}
void test_sorteaza_dupa_cadru_didactic_si_tip() {
	Service srv;
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(i), i, "tip" + to_string(i), "cadru_didactic" + to_string(i*3));
	}
	Repository rezultat = srv.sorteaza_dupa_cadru_didactic_si_tip();
	assert(rezultat.get_size() == 101);
	VectorDinamic < Disciplina >lst = rezultat.get_all();
	for (int i = 0; i < 100; i++)
	{
		assert((lst[i].get_cadru_didactic() < lst[i + 1].get_cadru_didactic())||((lst[i].get_cadru_didactic() == lst[i + 1].get_cadru_didactic())&&lst[i].get_tip()<=lst[i+1].get_tip()));

	}
	for (int i = 0; i <= 100; i++)
	{
		srv.adauga("denumire" + to_string(-i-1), i, "tip" + to_string(i), "cadru_didactic" + to_string(i));
	}
	rezultat = srv.sorteaza_dupa_cadru_didactic_si_tip();
	assert(rezultat.get_size() == 202);
	lst = rezultat.get_all();
	for (int i = 0; i < 201; i++)
	{
		assert((lst[i].get_cadru_didactic() < lst[i + 1].get_cadru_didactic()) || ((lst[i].get_cadru_didactic() == lst[i + 1].get_cadru_didactic()) && lst[i].get_tip() <= lst[i + 1].get_tip()));
	}
}