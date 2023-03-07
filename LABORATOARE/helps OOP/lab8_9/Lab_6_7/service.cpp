#pragma once
#include "repo.h"
#include <vector>
#include <string>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <exception>
#include <algorithm>
#include <iterator>
#include "validator.h"
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

Service::Service() {
	Repository repo_initiat;
	repo = repo_initiat;
}

const Disciplina Service::adauga(const string& denumire, const int& ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina d(denumire, ore_pe_saptamana, tip, cadru_didactic);
	Disciplina d_2 = find(denumire);
	if (d_2.get_denumire() != "null") {
		throw ExceptiiValidare("Denumirea deja exista!");
	}
	this->repo.adauga(d);
	actiuniUndo.push_back(new UndoAdauga(repo, d));
	return d;
}

const Disciplina Service::sterge(const string& denumire)  {
	Disciplina d = this->repo.find(denumire);
	if (d.get_denumire() == "null") {
		throw ExceptiiValidare("Nu exista aceasta disciplina\n");
	}
	this->repo.sterge(d);
	actiuniUndo.push_back(new UndoSterge(repo, d));
	return d;
}

const Disciplina& Service::modifica(const string& denumire, const string& new_denumire, const int& new_ore_pe_saptamana, const string& new_tip, const string& new_cadru_didactic) {
	Disciplina &d = this->repo.find(denumire);
	if (d.get_denumire() == "null") {
		throw ExceptiiValidare("Nu exista aceasta disciplina!\n");
	}
	Disciplina cpy = d;
	Disciplina d_2 = this->repo.find(new_denumire);
	if (d_2.get_denumire() != "null") {
		throw ExceptiiValidare("Denumirea deja exista!\n");
	}

	d.set_denumire(new_denumire);
	d.set_ore_pe_saptamana(new_ore_pe_saptamana);
	d.set_tip(new_tip);
	d.set_cadru_didactic(new_cadru_didactic);

	
	actiuniUndo.push_back(new UndoModifica(repo, cpy,d));
	return d;
}

const string Service::str() const {
	return this->repo.str();
}

const size_t Service::get_size()  {
	return this->repo.get_size();
}

const Disciplina Service::find(const string& denumire) {
	return this->repo.find(denumire);
}

const Repository Service::filtreaza_dupa_nr_ore(const int& nr_minim,const int& nr_maxim) {
	Repository rezultat;
	vector<Disciplina> lst = this->repo.get_all();
	auto func = [nr_minim, nr_maxim](Disciplina el) mutable {
		return el.get_ore_pe_saptamana() >= nr_minim && el.get_ore_pe_saptamana() <= nr_maxim;
	};
	auto it = copy_if(lst.begin(), lst.end(), back_inserter(rezultat.get_all()), func);
	return rezultat;
}

const Repository Service::filtreaza_dupa_cadru_didactic(const string& cadru_didactc) {
	Repository rezultat;
	vector<Disciplina> lst = this->repo.get_all();
	auto func = [cadru_didactc](Disciplina el) mutable {
		return el.get_cadru_didactic() == cadru_didactc;
	};
	auto it = copy_if(lst.begin(), lst.end(), back_inserter(rezultat.get_all()), func);
	return rezultat;
}

/*
Functii de comparare
*/

const bool cmp_denumire(const Disciplina& d2,const Disciplina& d1) {
	return d1.get_denumire() > d2.get_denumire();
}


const bool cmp_ore(const Disciplina& d2,const Disciplina& d1) {
	return d1.get_ore_pe_saptamana() > d2.get_ore_pe_saptamana();
}

const bool cmp_cadru_si_tip(const Disciplina& d2, const Disciplina& d1) {
	return (d1.get_cadru_didactic() > d2.get_cadru_didactic()) || ((d1.get_cadru_didactic() == d2.get_cadru_didactic()) && d1.get_tip() > d2.get_tip());
}

const Repository Service::sorteaza_dupa_denumire() {
	return sorteaza_general(cmp_denumire);
}
const Repository Service::sorteaza_dupa_ore() {
	return sorteaza_general(cmp_ore);
}
const Repository Service::sorteaza_dupa_cadru_didactic_si_tip() {
	return sorteaza_general(cmp_cadru_si_tip);
}


const Repository Service::sorteaza_general(const bool (*cmp)(const Disciplina& d1,const Disciplina& d2)) {
	vector < Disciplina >lst = this->repo.get_all();
	Repository rezultat;
	sort(lst.begin(), lst.end(), cmp);
	auto it = copy(lst.begin(), lst.end(), back_inserter(rezultat.get_all()));
	return rezultat;
}

void Service::goleste() {
	contract.clear();
}

size_t Service::nr_contracte() {
	return contract.size();
}

const Disciplina Service::adauga_in_contract(const string& denumire) {
	Disciplina d = find(denumire);
	if (d.get_denumire() == "null")throw ExceptiiValidare("Disciplina cautata nu exista!\n");
	contract.adauga(d);
	return d;
}

const string Service::str_contract() {
	return contract.str();
}

void Service::genereaza_contracte(int n) {
	vector<Disciplina>lst = repo.get_all();
	if (lst.size() == 0)throw ExceptiiValidare("Numarul de discipline este 0!\n");
	while (n) {
		int rndNr = rand() % lst.size();
		contract.adauga(lst[rndNr]);
		n--;
	}
}

void Service::sterge_tip(const string& tip) {
	vector<Disciplina>&lst = contract.get_all();
	auto func = [tip](Disciplina el) mutable {
		return el.get_tip() == tip;
	};
	auto it = remove_if(lst.begin(), lst.end(), func);

	if (it != lst.end()) {
		lst.erase(it,lst.end());
	}
}

void Service::salveaza_contract(const string& nume_fisier) {
	ofstream fout(nume_fisier);
	fout << "<div>\n";
	vector<Disciplina>lst = contract.get_all();
	for (auto& el : lst) {
		//fout << "	<p>" << el.get_denumire() << " " << el.get_ore_pe_saptamana() << " " << el.get_tip() << " " <<el.get_cadru_didactic()<<" " << "</p>\n";
		fout << "	<p>"<<el.str() << "</p>\n";
	}
	fout << "</div>";
	fout.close();
}

void Service::undo() {
	if (actiuniUndo.size() == 0)
		throw (exception("Nu se poate face undo!"));

	actiuniUndo.back()->doUndo(); // Facem undo
	delete actiuniUndo.back(); // Stergem elementul din memorie
	actiuniUndo.pop_back(); // Stergem elementul din vector efectiv

}