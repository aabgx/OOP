#pragma once
#include "service.h"
#include "repo.h"
#include "domain.h"
#include <cassert>
#include <vector>
#include "validator.h"
#include <iostream>
#include <fstream>

using namespace std;

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
	bool ok = false;
	try {
		srv.adauga("denumire", 1, "tip", "cadru_didactic");
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);
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

	bool ok = false;
	//3
	try {

	srv.modifica("nu_exista","new_denumire3", 20, "new_tip", "new_cadru_didactic");
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);

	//4
	ok = false;
	try {
		srv.modifica("new_denumire2", "new_denumire", 20, "new_tip", "new_cadru_didactic");
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);
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
	bool ok = false;
	try {
		srv.sterge("nu_exista");
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);

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
	vector < Disciplina >lst= rezultat.get_all();
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
	vector < Disciplina >lst = rezultat.get_all();
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
	vector < Disciplina >lst = rezultat.get_all();
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

void test_adauga_in_contract() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru didactic");
	srv.adauga("denumire2", 12, "tip2", "cadru didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru didactic3");
	srv.adauga("denumire4", 14, "tip4", "cadru didactic4");
	assert(srv.nr_contracte() == 0);
	srv.adauga_in_contract("denumire");
	assert(srv.nr_contracte() == 1);
	srv.adauga_in_contract("denumire");
	assert(srv.nr_contracte() == 2);
	srv.adauga_in_contract("denumire2");
	assert(srv.nr_contracte() == 3);
	bool ok = false;
	try {
		srv.adauga_in_contract("nu_exista");
	}
	catch (ExceptiiValidare& el) {
		ok = true;
		assert(el.get_Msg() != "");
	}
	assert(ok);
}

void test_str_service_contract() {
	Service srv;
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	Disciplina d("denumire", 1, "tip", "cadru_didactic");
	srv.adauga_in_contract("denumire");
	assert(srv.str_contract() == d.str() + "\n");

}

void test_goleste() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire1");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire3");
	srv.adauga_in_contract("denumire3");
	srv.adauga_in_contract("denumire3");
	srv.adauga_in_contract("denumire3");
	srv.goleste();
	assert(srv.nr_contracte() == 0);
}
void test_genereaza() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.genereaza_contracte(5);
	assert(srv.nr_contracte() == 5);
	srv.genereaza_contracte(10);
	assert(srv.nr_contracte() == 15);
	srv.genereaza_contracte(2);
	assert(srv.nr_contracte() == 17);
	srv.genereaza_contracte(13);
	assert(srv.nr_contracte() == 30);

	Service srv2;
	bool ok = false;
	try {

	srv2.genereaza_contracte(5);
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);

}

void sterge_tip() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire1");
	srv.adauga_in_contract("denumire2");

	//cout << srv.nr_contracte();
	srv.sterge_tip("tip");
	assert(srv.nr_contracte() == 2);
	srv.sterge_tip("tip");
	assert(srv.nr_contracte() == 2);

	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.sterge_tip("tip");
	assert(srv.nr_contracte() == 5);

	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire");

	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.adauga_in_contract("denumire2");
	srv.sterge_tip("tip");
	assert(srv.nr_contracte() == 14);

}

void test_salveaza_contract() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.adauga_in_contract("denumire");
	srv.adauga_in_contract("denumire1");
	srv.adauga_in_contract("denumire2");
	
	srv.salveaza_contract("test.html");

	ifstream fin("test.html");
	Disciplina d1("denumire", 1, "tip", "cadru_didactic");
	Disciplina d2("denumire1", 11, "tip1", "cadru_didactic1");
	Disciplina d3("denumire2", 12, "tip2", "cadru_didactic2");

	string test;
	getline(fin, test);
	assert(test == "<div>");
	getline(fin, test);
	assert(test == "	<p>" + d1.str() + "</p>");
	getline(fin, test);
	assert(test == "	<p>" + d2.str() + "</p>");
	getline(fin, test);
	assert(test == "	<p>" + d3.str() + "</p>");
	getline(fin, test);
	assert(test == "</div>");

	fin.close();

}

void test_undo_srv() {
	Service srv;
	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.undo();
	assert(srv.get_size() == 3);
	srv.undo();
	assert(srv.get_size() == 2);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");
	srv.undo();
	assert(srv.get_size() == 3);
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");
	assert(srv.get_size() == 4);
	srv.undo();
	assert(srv.get_size() == 3);
	srv.undo();
	assert(srv.get_size() == 2);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.sterge("denumire");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.sterge("denumire2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");
	srv.sterge("denumire3");
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 2);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 2);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 0);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 0);

	srv.adauga("denumire", 1, "tip", "cadru_didactic");
	srv.adauga("denumire1", 11, "tip1", "cadru_didactic1");
	srv.adauga("denumire2", 12, "tip2", "cadru_didactic2");
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");

	srv.modifica("denumire", "new_denumire", 11, "new_tip", "new_cadru_didactic");
	srv.modifica("denumire1", "new_denumire1", 111, "new_tip1", "new_cadru_didactic1");
	srv.modifica("denumire2", "new_denumire2", 112, "new_tip2", "new_cadru_didactic2");
	srv.modifica("denumire3", "new_denumire3", 113, "new_tip3", "new_cadru_didactic3");
	
	srv.undo();
	assert(srv.get_size() == 4);
	assert(srv.find("denumire3").get_denumire() != "null");
	assert(srv.find("new_denumire3").get_denumire() == "null");

	srv.undo();
	assert(srv.get_size() == 4);
	assert(srv.find("denumire2").get_denumire() != "null");
	assert(srv.find("new_denumire2").get_denumire() == "null");

	srv.undo();
	assert(srv.get_size() == 4);
	assert(srv.find("denumire1").get_denumire() != "null");
	assert(srv.find("new_denumire1").get_denumire() == "null");

	srv.undo();
	assert(srv.get_size() == 4);
	assert(srv.find("denumire").get_denumire() != "null");
	assert(srv.find("new_denumire").get_denumire() == "null");

	srv.undo();
	assert(srv.get_size() == 3);
	srv.adauga("denumire3", 13, "tip3", "cadru_didactic3");
	assert(srv.get_size() == 4);
	srv.undo();
	assert(srv.get_size() == 3);
	srv.undo();
	assert(srv.get_size() == 2);
	srv.undo();
	assert(srv.get_size() == 1);
	srv.undo();
	assert(srv.get_size() == 0);
	bool ok = false;
	try {
		srv.undo();
	}
	catch (exception&) {
		ok = true;
	}
	assert(ok);
}