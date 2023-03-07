#pragma once
#include <string>
#include "domain.h"
#include <vector>

using namespace std;

class Repository {
private:
	/*
	Reprezentarea interna
	*/
	vector<Disciplina> lista;
	Disciplina d_null;

public:
	/*
	Aici e interfata publica
	*/

	/*
	Constructorul
	*/
	Repository();

	/*
	Nu se poate face compie
	Repository(const Repository& repo) = delete;
	*/

	/*
	Determina lista cu toate Disciplinele
	return->vector<Disciplina>, lista cu toate disciplinele
	*/
	vector<Disciplina>& get_all();

	/*
	Adauga o disciplina in repository
	d->Disciplina, disciplina care va fi adaugata
	*/
	void adauga(const Disciplina& d);

	/*
	Sterge o anumita disciplina din repository
	d->Disciplina, disciplina care va fi stearsa
	*/
	void sterge(const Disciplina& d);

	/*
	Gaseste o anumita disciplina dupa denumirea ei
	denumire->string, denumirea disciplinei cautate
	return->Disciplina, disciplina cautata
	*/
	Disciplina& find(const string& deumire) ;

	/*
	Returneaza numarul de elemente din repository-ul curent
	return->int, numarul de discipline din repo-ul curent
	*/
	const size_t get_size();

	/*
	Determina un sir cu lista care trebuie afisata la tastatura
	return->string, lista care trebuie afisata la tastatura
	*/
	const string str() const;


};