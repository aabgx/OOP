#pragma once
#include "contract_repo.h"
#include <string>
#include "domain.h"
#include <algorithm>
#include <iterator>
using namespace std;

void ContractRepo::adauga(const Disciplina d) {

	this->lista.push_back(d);
}

void ContractRepo::clear() {
	this->lista.clear();
}

size_t ContractRepo::size() {
	return this->lista.size();
}

const string ContractRepo::str() const {
	string de_afisat = "";

	for (auto& el : this->lista)
	{
		de_afisat = de_afisat + el.str() + "\n";
	}
	return de_afisat;
}