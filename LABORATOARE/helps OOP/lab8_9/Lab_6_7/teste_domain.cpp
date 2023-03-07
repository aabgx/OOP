#pragma once
#include "domain.h"
#include <assert.h>


void test_creaza() {
	Disciplina d("denumire", 2, "tip", "cadru_didactic");

	assert(d.get_denumire() == "denumire");
	assert(d.get_ore_pe_saptamana() == 2);
	assert(d.get_tip() == "tip");
	assert(d.get_cadru_didactic() == "cadru_didactic");

	Disciplina d2("denumire2", 3, "tip2", "cadru_didactic2");

	assert(d2.get_denumire() == "denumire2");
	assert(d2.get_ore_pe_saptamana() == 3);
	assert(d2.get_tip() == "tip2");
	assert(d2.get_cadru_didactic() == "cadru_didactic2");

}

void test_modifica() {
	Disciplina d("denumire", 2, "tip", "cadru_didactic");

	assert(d.get_denumire() == "denumire");
	assert(d.get_ore_pe_saptamana() == 2);
	assert(d.get_tip() == "tip");
	assert(d.get_cadru_didactic() == "cadru_didactic");

	d.set_denumire("denumire2");
	d.set_ore_pe_saptamana(3);
	d.set_tip("tip2");
	d.set_cadru_didactic("cadru_didactic2");

	assert(d.get_denumire() == "denumire2");
	assert(d.get_ore_pe_saptamana() == 3);
	assert(d.get_tip() == "tip2");
	assert(d.get_cadru_didactic() == "cadru_didactic2");

	d.set_denumire("denumire3");
	d.set_ore_pe_saptamana(33);
	d.set_tip("tip3");
	d.set_cadru_didactic("cadru_didactic3");

	assert(d.get_denumire() == "denumire3");
	assert(d.get_ore_pe_saptamana() == 33);
	assert(d.get_tip() == "tip3");
	assert(d.get_cadru_didactic() == "cadru_didactic3");

}

void test_egale() {
	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	Disciplina d2("denumire", 2, "tip", "cadru_didactic");
	assert(d.egale(d2) == true);

	Disciplina d3("denumire2", 2, "tip", "cadru_didactic");
	assert(d.egale(d3) == false);

}

void test_str_disciplina() {
	//1
	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	assert(d.str() == "DENUMIRE: denumire | ORE PE SAPTAMANA: 2 | TIP: tip | CADRU DIDACTIC: cadru_didactic");

	//2
	Disciplina d2("denumire2", 22, "tip2", "cadru_didactic2");
	assert(d2.str() == "DENUMIRE: denumire2 | ORE PE SAPTAMANA: 22 | TIP: tip2 | CADRU DIDACTIC: cadru_didactic2");

	//3
	Disciplina d3("denumire23", 223, "tip23", "cadru_didactic23");
	assert(d3.str() == "DENUMIRE: denumire23 | ORE PE SAPTAMANA: 223 | TIP: tip23 | CADRU DIDACTIC: cadru_didactic23");

}