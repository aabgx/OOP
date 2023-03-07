#pragma once
#include "repo.h"
#include <vector>
#include <string>
#include "domain.h"
#include "repo.h"

class Service {

private:
	/*
	Aici e reprezentarea interna
	*/
	Repository repo;

public:
	/*
	Aici e interfata publica
	*/

	/*
	Constructorul implicit
	repo->Repository, repository-ul disciplinelor
	*/
	Service();

	/*
	Nu se poate face copie
	*/
	Service(const Service& srv) = delete;

	/*
	Adauga o disciplina in lista
	denumire->string, denumirea disciplinei care va fi adaugata
	ore_pe_saptamana->int, orele pe saptamana a disciplinei care va fi adaugata
	tip->string, tipul disciplinei care va fi adaugata
	cadru_didactic->string, cadrul didactic al disciplinei respective
	return->Disciplina, disciplina care a fost adaugata
	*/
	const Disciplina adauga(const string& denumire, const int& ore_pe_saptamana, const string& tip, const string& cadru_didactic);

	/*
	Sterge o disciplina din lista
	denumire->string, denumirea disciplinei care va fi stearsa
	return->Disciplina, disciplina care a fost stearsa
	*/
	const Disciplina sterge(const string& denumire);

	/*
	Modifica o disciplina din lista
	denumire->string, denumirea disciplinei care va fi modificata
	new_denumire->string, noua denumire a disciplinei
	new_ore_pe_saptamana->int, noile ore pe saptamana a disciplinei
	new_tip->string, noul tip al disciplinei
	new_cadru_didactic->string, noul cadru didactic al disciplinei
	return->Disciplina, disciplina care a fost modificata
	*/
	const Disciplina modifica(const string& denumire, const string& new_denumire, const int& new_ore_pe_saptamana, const string& new_tip, const string& new_cadru_didactic);

	/*
	Determina un sir care va afisa toate disciplinele la tastatura
	return->string, stringul cu modul in care toate disciplinele vor fi afisate
	*/
	const string str();

	/*
	Determina numarul de entitati adaugate pana la momentul actual
	return->int, numarul de entitati
	*/
	int get_size();

	/*
	Cauta o anumita disciplina in lista cu discipline adaugate
	denumire->string, denumirea disciplinei pe care dorim sa o cautam
	return->Disciplina, disciplina cautata cu o anumita denumire
	*/
	Disciplina find(const string& denumire);

	/*
	Filtreaza o disciplina dupa numarul de ore
	nr_minim->int, numarul minim de ore
	nr_maxim->int, numarul maxim de ore
	return->Repository, repository-ul cu disciplinele filtrate
	*/
	Repository filtreaza_dupa_nr_ore(int nr_minim, int nr_maxim);

	/*
	Filtreaza disciplinele dupa un anumit cadru didactic
	cadru_didactic->string, cadrul didactic dupa care facem filtrarea
	return->Repository, repository-ul cu disciplinele filtrate
	*/
	Repository filtreaza_dupa_cadru_didactic(string cadru_didactc);

	/*
	Sorteaza disciplinele dupa denumire
	return->Repository, repository-ul disciplinelor sortate
	*/
	Repository sorteaza_dupa_denumire();

	/*
	Sorteaza discipinele dupa numarul de ore
	return->Repository, repository-ul disciplinelor sortate
	*/
	Repository sorteaza_dupa_ore();

	/*
	Sorteaza disciplinele dupa cadru didactic si tip
	return->Repository, repository-ul disciplinelor sortate
	*/
	Repository sorteaza_dupa_cadru_didactic_si_tip();
};