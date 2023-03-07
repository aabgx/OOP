#pragma once
#include "domain.h"
#include "repo.h"
#include <vector>
#include "undo.h"
#include <cassert>
#include <iostream>

using namespace std;

void test_undo_adauga() {
	vector<Disciplina> lst;
	Repository repo;
	Disciplina d1("denumire1", 1, "tip1", "cadru1");
	Disciplina d2("denumire12", 12, "tip12", "cadru12");
	Disciplina d3("denumire13", 13, "tip13", "cadru13");
	Disciplina d4("denumire14", 14, "tip14", "cadru14");
	vector<ActiuneUndo*>undo_list;

	repo.adauga(d1);
	undo_list.push_back(new UndoAdauga(repo, d1));
	repo.adauga(d2);
	undo_list.push_back(new UndoAdauga(repo, d2));
	repo.adauga(d3);
	undo_list.push_back(new UndoAdauga(repo, d3));
	repo.adauga(d4);
	undo_list.push_back(new UndoAdauga(repo, d4));

	undo_list[3]->doUndo();
	assert(repo.get_size() == 3);
	lst = repo.get_all();
	assert(lst[0] == d1);
	assert(lst[1] == d2);
	assert(lst[2] == d3);

	undo_list[2]->doUndo();
	assert(repo.get_size() == 2);
	lst = repo.get_all();
	assert(lst[0] == d1);
	assert(lst[1] == d2);

	undo_list[1]->doUndo();
	assert(repo.get_size() == 1);
	lst = repo.get_all();
	assert(lst[0] == d1);

	undo_list[0]->doUndo();
	assert(repo.get_size() == 0);

	for (auto& el : undo_list) {
		delete el;
	}
}

void test_undo_sterge() {
	vector<Disciplina> lst;
	Repository repo;
	Disciplina d1("denumire1", 1, "tip1", "cadru1");
	Disciplina d2("denumire12", 12, "tip12", "cadru12");
	Disciplina d3("denumire13", 13, "tip13", "cadru13");
	Disciplina d4("denumire14", 14, "tip14", "cadru14");
	vector<ActiuneUndo*>undo_list;

	repo.adauga(d1);
	undo_list.push_back(new UndoAdauga(repo, d1));
	repo.adauga(d2);
	undo_list.push_back(new UndoAdauga(repo, d2));
	repo.adauga(d3);
	undo_list.push_back(new UndoAdauga(repo, d3));
	repo.adauga(d4);
	undo_list.push_back(new UndoAdauga(repo, d4));

	repo.sterge(d4);
	undo_list.push_back(new UndoSterge(repo, d4));
	repo.sterge(d3);
	undo_list.push_back(new UndoSterge(repo, d3));
	repo.sterge(d2);
	undo_list.push_back(new UndoSterge(repo, d2));
	repo.sterge(d1);
	undo_list.push_back(new UndoSterge(repo, d1));

	assert(repo.get_size() == 0);

	undo_list[7]->doUndo();
	assert(repo.get_size() == 1);
	lst = repo.get_all();
	assert(lst[0] == d1);

	undo_list[6]->doUndo();
	assert(repo.get_size() == 2);
	lst = repo.get_all();
	assert(lst[0] == d1);
	assert(lst[1] == d2);

	undo_list[5]->doUndo();
	assert(repo.get_size() == 3);
	lst = repo.get_all();
	assert(lst[0] == d1);
	assert(lst[1] == d2);
	assert(lst[2] == d3);

	undo_list[4]->doUndo();
	assert(repo.get_size() == 4);
	lst = repo.get_all();
	assert(lst[0] == d1);
	assert(lst[1] == d2);
	assert(lst[2] == d3);
	assert(lst[3] == d4);

	for (auto& el : undo_list) {
		delete el;
	}
}

void test_undo_modifica() {
	vector<Disciplina> lst;
	Repository repo;
	Disciplina d1("denumire1", 1, "tip1", "cadru1");
	Disciplina d2("denumire12", 12, "tip12", "cadru12");
	Disciplina d3("denumire13", 13, "tip13", "cadru13");
	Disciplina d4("denumire14", 14, "tip14", "cadru14");
	Disciplina d5("denumire145", 145, "tip145", "cadru145");
	Disciplina d6("denumire146", 146, "tip146", "cadru146");
	Disciplina d7("denumire147", 147, "tip147", "cadru147");
	Disciplina d8("denumire148", 148, "tip148", "cadru148");

	vector<ActiuneUndo*>undo_list;

	repo.adauga(d1);
	undo_list.push_back(new UndoAdauga(repo, d1));
	repo.adauga(d2);
	undo_list.push_back(new UndoAdauga(repo, d2));
	repo.adauga(d3);
	undo_list.push_back(new UndoAdauga(repo, d3));
	repo.adauga(d4);
	undo_list.push_back(new UndoAdauga(repo, d4));

	repo.find(d1.get_denumire()) = d5;
	undo_list.push_back(new UndoModifica(repo, d1, d5));
	repo.find(d2.get_denumire()) = d6;
	undo_list.push_back(new UndoModifica(repo, d2, d6));
	repo.find(d3.get_denumire()) = d7;
	undo_list.push_back(new UndoModifica(repo, d3, d7));
	repo.find(d4.get_denumire()) = d8;
	undo_list.push_back(new UndoModifica(repo, d4, d8));

	undo_list[7]->doUndo();
	lst = repo.get_all();
	assert(repo.get_size() == 4);
	assert(lst[0] == d5);
	assert(lst[1] == d6);
	assert(lst[2] == d7);
	assert(lst[3] == d4);

	undo_list[6]->doUndo();
	lst = repo.get_all();
	assert(repo.get_size() == 4);
	assert(lst[0] == d5);
	assert(lst[1] == d6);
	assert(lst[2] == d3);
	assert(lst[3] == d4);

	undo_list[5]->doUndo();
	lst = repo.get_all();
	assert(repo.get_size() == 4);
	assert(lst[0] == d5);
	assert(lst[1] == d2);
	assert(lst[2] == d3);
	assert(lst[3] == d4);

	undo_list[4]->doUndo();
	lst = repo.get_all();
	assert(repo.get_size() == 4);
	assert(lst[0] == d1);
	assert(lst[1] == d2);
	assert(lst[2] == d3);
	assert(lst[3] == d4);

	for (auto& el : undo_list) {
		delete el;
	}
}