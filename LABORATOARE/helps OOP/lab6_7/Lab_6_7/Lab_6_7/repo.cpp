#pragma once
#include "repo.h"
#include "vector_dinamic.h"
#include <string>
#include "domain.h"
using namespace std;

Repository::Repository() {
	VectorDinamic<Disciplina>lst;
	lista = lst;
}

VectorDinamic<Disciplina> Repository::get_all() {
	return this->lista;
}

void Repository::adauga(const Disciplina& d) {

	this->lista.push_back(d);
}

void Repository::sterge(Disciplina d) {
	VectorDinamic<Disciplina> lst = this->lista;

	for(int i=0;i<lst.size();++i)
		if (d.egale(lst[i]) == true) {
			this->lista.erase(this->lista.begin() + i);
			break;
		}
}

Disciplina Repository::find(const string& denumire) {
	VectorDinamic<Disciplina> lst = this->lista;
	for (int i = 0; i < lst.size(); ++i) {
		if (lst[i].get_denumire() == denumire) {
			return this->lista[i];
		}
	}
	Disciplina d_null("null", -1, "null", "null");
	return d_null;
}

int Repository::get_size() {
	return this->lista.size();
}

const string Repository::str() {
	string de_afisat = "";
	VectorDinamic<Disciplina>lst = this->lista;

	for (int i = 0; i < lst.size(); ++i)
	{
		de_afisat = de_afisat + lst[i].str()+"\n";
	}
	return de_afisat;
}