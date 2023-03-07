#pragma once
#include "repo.h"
#include "vector_dinamic.h"
#include <string>
#include "domain.h"
#include <algorithm>
#include <iterator>
using namespace std;

Repository::Repository() {
	vector<Disciplina>lst;
	lista = lst;
	Disciplina d("null", -1, "null", "null");
	d_null = d;
}

vector<Disciplina>& Repository::get_all() {
	return this->lista;
}

void Repository::adauga(const Disciplina& d) {

	this->lista.push_back(d);
}

void Repository::sterge(const Disciplina& d) {
	auto func = [d](Disciplina el) mutable {
		return d.egale(el);
	};
	auto it = find_if(this->lista.begin(), this->lista.end(), func);
	if (it != this->lista.end()) {
		this->lista.erase(it);
	}
}

Disciplina& Repository::find(const string& denumire) {
	auto func = [denumire](Disciplina el) mutable {
		return el.get_denumire() == denumire;
	};
	auto it = find_if(this->lista.begin(), this->lista.end(), func);
	if(it!=this->lista.end())
		return *it;
	return d_null;
}

const size_t Repository::get_size() {
	return this->lista.size();
}

const string Repository::str() const {
	string de_afisat = "";
	
	for (auto& el : this->lista)
	{
		de_afisat = de_afisat + el.str()+"\n";
	}
	return de_afisat;
}
