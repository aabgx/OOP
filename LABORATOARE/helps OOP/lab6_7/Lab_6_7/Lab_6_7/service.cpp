#pragma once
#include "repo.h"
#include <vector>
#include <string>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <exception>

Service::Service() {
	Repository repo_initiat;
	repo = repo_initiat;
}

const Disciplina Service::adauga(const string& denumire, const int& ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
	Disciplina d(denumire, ore_pe_saptamana, tip, cadru_didactic);
	Disciplina d_2 = find(denumire);
	if (d_2.get_denumire() != "null") {
		throw exception("Denumirea deja exista!");
	}
	this->repo.adauga(d);
	return d;
}

const Disciplina Service::sterge(const string& denumire) {
	Disciplina d = this->repo.find(denumire);
	if (d.get_denumire() == "null") {
		throw exception("Nu exista aceasta disciplina");
	}
	this->repo.sterge(d);
	return d;
}

const Disciplina Service::modifica(const string& denumire, const string& new_denumire, const int& new_ore_pe_saptamana, const string& new_tip, const string& new_cadru_didactic) {
	Disciplina d = this->repo.find(denumire);
	if (d.get_denumire() == "null") {
		throw exception("Nu exista aceasta disciplina");
	}
	Disciplina d_2 = this->repo.find(new_denumire);
	if (d_2.get_denumire() != "null") {
		throw exception("Denumirea deja exista!");
	}
	this->repo.sterge(d);

	d.set_denumire(new_denumire);
	d.set_ore_pe_saptamana(new_ore_pe_saptamana);
	d.set_tip(new_tip);
	d.set_cadru_didactic(new_cadru_didactic);

	this->repo.adauga(d);

	
	return d;
}

const string Service::str() {
	return this->repo.str();
}

int Service::get_size() {
	return this->repo.get_size();
}

Disciplina Service::find(const string& denumire) {
	return this->repo.find(denumire);
}

Repository Service::filtreaza_dupa_nr_ore(int nr_minim, int nr_maxim) {
	Repository rezultat;
	VectorDinamic<Disciplina> lst = this->repo.get_all();
	for (int i = 0; i < lst.size(); i++)
	{
		if (lst[i].get_ore_pe_saptamana() >= nr_minim && lst[i].get_ore_pe_saptamana() <= nr_maxim)
			rezultat.adauga(lst[i]);
	}
	return rezultat;
}

Repository Service::filtreaza_dupa_cadru_didactic(string cadru_didactc) {
	Repository rezultat;
	VectorDinamic<Disciplina> lst = this->repo.get_all();
	for (int i = 0; i < lst.size(); i++)
	{
		if (lst[i].get_cadru_didactic()==cadru_didactc)
			rezultat.adauga(lst[i]);
	}
	return rezultat;
}

Repository Service::sorteaza_dupa_denumire() {
	VectorDinamic < Disciplina >lst = this->repo.get_all();
	int n = lst.size(), i, j;
	for(i=0;i<n-1;i++)
		for (j = i+1; j < n; j++)
		{
			if (lst[i].get_denumire() > lst[j].get_denumire()) {
				Disciplina aux = lst[i];
				lst[i] = lst[j];
				lst[j] = aux;
			}
		}
	Repository rezultat;
	for (i = 0; i < n; i++)
		rezultat.adauga(lst[i]);
	return rezultat;
}
Repository Service::sorteaza_dupa_ore() {
	VectorDinamic < Disciplina >lst = this->repo.get_all();
	int n = lst.size(), i, j;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
		{
			if (lst[i].get_ore_pe_saptamana() > lst[j].get_ore_pe_saptamana()) {
				Disciplina aux = lst[i];
				lst[i] = lst[j];
				lst[j] = aux;
			}
		}
	Repository rezultat;
	for (i = 0; i < n; i++)
		rezultat.adauga(lst[i]);
	return rezultat;
}
Repository Service::sorteaza_dupa_cadru_didactic_si_tip() {
	VectorDinamic < Disciplina >lst = this->repo.get_all();
	int n = lst.size(), i, j;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
		{
			if ((lst[i].get_cadru_didactic() > lst[j].get_cadru_didactic() ) || ((lst[i].get_cadru_didactic() == lst[j].get_cadru_didactic()) && lst[i].get_tip()>lst[j].get_tip())) {
				Disciplina aux = lst[i];
				lst[i] = lst[j];
				lst[j] = aux;
			}
		}
	Repository rezultat;
	for (i = 0; i < n; i++)
		rezultat.adauga(lst[i]);
	return rezultat;
}
