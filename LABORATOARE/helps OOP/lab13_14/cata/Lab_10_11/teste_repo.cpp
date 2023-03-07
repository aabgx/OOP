#pragma once
#include "repo.h"
#include "domain.h"
#include <assert.h>
#include <cassert>
#include "vector_dinamic.h"

void test_creaza_repo() {
	Repository repo;
	assert(repo.get_size() == 0);
}

void test_get_all() {
	Repository repo;
	vector <Disciplina> lst = repo.get_all();
	assert(lst.size() == 0);
}

void test_adauga() {
	Repository repo;
	//1
	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d);
	assert(repo.get_size() == 1);
	vector < Disciplina > lst = repo.get_all();
	assert(d.egale(lst[0]) == true);

	//2
	Disciplina d2("denumire2", 22, "tip2", "cadru_didactic2");
	repo.adauga(d2);
	assert(repo.get_size() == 2);
	lst = repo.get_all();
	assert(d2.egale(lst[1]) == true);

	//3
	Disciplina d3("denumire23", 223, "tip23", "cadru_didactic23");
	repo.adauga(d3);
	assert(repo.get_size() == 3);
	lst = repo.get_all();
	assert(d3.egale(lst[2]) == true);

	//4
	Disciplina d4("denumire234", 2234, "tip234", "cadru_didactic234");
	repo.adauga(d4);
	assert(repo.get_size() == 4);
	lst = repo.get_all();
	assert(d4.egale(lst[3]) == true);
}

void test_sterge() {
	Repository repo;

	//1
	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d);
	assert(repo.get_size() == 1);
	vector < Disciplina > lst = repo.get_all();
	assert(d.egale(lst[0]) == true);

	repo.sterge(d);
	assert(repo.get_size() == 0);

	//2
	Disciplina d2("denumire2", 22, "tip2", "cadru_didactic2");
	repo.adauga(d2);
	assert(repo.get_size() == 1);
	lst = repo.get_all();
	assert(d2.egale(lst[0]) == true);
	Disciplina d3("denumire23", 223, "tip23", "cadru_didactic23");
	repo.adauga(d3);
	assert(repo.get_size() == 2);
	lst = repo.get_all();
	assert(d3.egale(lst[1]) == true);

	repo.sterge(d2);
	assert(repo.get_size() == 1);
	lst = repo.get_all();
	assert(d3.egale(lst[0]) == true);

	//3
	repo.sterge(d3);
	assert(repo.get_size() == 0);

}

void test_find() {
	Repository repo;

	//1
	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d);
	assert(repo.get_size() == 1);
	vector < Disciplina > lst = repo.get_all();
	assert(d.egale(lst[0]) == true);
	repo.sterge(repo.find("denumire"));
	assert(repo.get_size() == 0);

	//2
	Disciplina d2("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d2);
	assert(repo.get_size() == 1);
	lst = repo.get_all();
	assert(d2.egale(lst[0]) == true);

	assert(d.egale(repo.find("denumire")));

	//3
	d = repo.find("nu_exista");
	assert(d.get_denumire() == "null");

}

void test_str_repo() {
	Repository repo;

	Disciplina d("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d);
	assert(repo.get_size() == 1);
	vector < Disciplina > lst = repo.get_all();
	assert(d.egale(lst[0]) == true);

	//1
	assert(repo.str() == d.str() + "\n");

	//2
	Disciplina d2("denumire", 2, "tip", "cadru_didactic");
	repo.adauga(d2);
	assert(repo.str() == d.str() + "\n" + d2.str() + "\n");
}

