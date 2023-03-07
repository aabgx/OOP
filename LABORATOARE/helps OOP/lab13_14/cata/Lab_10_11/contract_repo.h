#pragma once
#include <vector>
#include <string>
#include "domain.h"

using namespace std;

class ContractRepo {
private:
	/*
	Aici e reprezentarea interna
	*/
	vector <Disciplina> lista;
public:
	/*
	Aici e interfata
	*/

	/*
	Determina un sir cu toate disciplinele
	*/
	vector<Disciplina>& get_all() {
		return lista;
	}

	/*
	Adauga o disciplina in repository
	d->Disciplina, disciplina care va fi adaugata
	*/
	void adauga(const Disciplina d);

	/*
	Goleste lista de discipline
	*/
	void clear();

	/*
	Determina numarul de entitati din contract
	*/
	size_t size();

	/*
	Determina un sir cu lista care trebuie afisata la tastatura
	return->string, lista care trebuie afisata la tastatura
	*/
	const string str() const;
};

