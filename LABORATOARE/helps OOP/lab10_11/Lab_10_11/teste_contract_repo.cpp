#pragma once
#include "domain.h"
#include "contract_repo.h"
#include <cassert>

void test_adauga_contract() {
	ContractRepo c;
	Disciplina d("denumire", 1, "tip", "cadru didactic");
	c.adauga(d);
	assert(c.size() == 1);
	c.adauga(d);
	assert(c.size() == 2);
	c.adauga(d);
	assert(c.size() == 3);
	c.adauga(d);
	assert(c.size() == 4);

}

void test_clear_contract() {
	ContractRepo c;
	Disciplina d("denumire", 1, "tip", "cadru didactic");
	c.adauga(d);
	c.adauga(d);
	c.adauga(d);
	c.adauga(d);
	c.clear();
	assert(c.size() == 0);
}

void test_str_contract() {
	ContractRepo repo;

	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d);
	assert(repo.size() == 1);

	//1
	assert(repo.str() == d.str() + "\n");

	//2
	Disciplina d2("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d2);
	assert(repo.str() == d.str() + "\n" + d2.str() + "\n");
}
