#pragma once
#include "repo.h"
#include <vector>
#include <string>
#include "domain.h"
#include "repo.h"
#include "contract_repo.h"
#include "undo.h"

class Service {

private:
	/*
	Aici e reprezentarea interna
	*/
	Repository repo;
	ContractRepo contract;
	vector<ActiuneUndo*>actiuniUndo;

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
	Arunca eroare daca gaseste deja o disciplina cu respectiva denumire
	*/
	const Disciplina adauga(const string& denumire, const int& ore_pe_saptamana, const string& tip, const string& cadru_didactic) ;

	/*
	Sterge o disciplina din lista
	denumire->string, denumirea disciplinei care va fi stearsa
	return->Disciplina, disciplina care a fost stearsa
	Arunca eroare daca nu gaseste o disciplina cu respectiva denumire
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
	Arunca eroare daca nu gaseste o disciplina cu respectiva denumire, sau gaseste o disciplina cu noua denumire
	*/
	const Disciplina& modifica(const string& denumire, const string& new_denumire, const int& new_ore_pe_saptamana, const string& new_tip, const string& new_cadru_didactic);

	/*
	Determina un sir care va afisa toate disciplinele la tastatura
	return->string, stringul cu modul in care toate disciplinele vor fi afisate
	*/
	const string str() const;

	/*
	Determina numarul de entitati adaugate pana la momentul actual
	return->int, numarul de entitati
	*/
	const size_t get_size() ;

	/*
	Cauta o anumita disciplina in lista cu discipline adaugate
	denumire->string, denumirea disciplinei pe care dorim sa o cautam
	return->Disciplina, disciplina cautata cu o anumita denumire
	*/
	const Disciplina find(const string& denumire);

	/*
	Filtreaza o disciplina dupa numarul de ore
	nr_minim->int, numarul minim de ore
	nr_maxim->int, numarul maxim de ore
	return->Repository, repository-ul cu disciplinele filtrate
	*/
	const Repository filtreaza_dupa_nr_ore(const int& nr_minim,const int& nr_maxim);

	/*
	Filtreaza disciplinele dupa un anumit cadru didactic
	cadru_didactic->string, cadrul didactic dupa care facem filtrarea
	return->Repository, repository-ul cu disciplinele filtrate
	*/
	const Repository filtreaza_dupa_cadru_didactic(const string& cadru_didactc);

	/*
	Sorteaza disciplinele dupa denumire
	return->Repository, repository-ul disciplinelor sortate
	*/
	const Repository sorteaza_dupa_denumire();

	/*
	Sorteaza discipinele dupa numarul de ore
	return->Repository, repository-ul disciplinelor sortate
	*/
	const Repository sorteaza_dupa_ore();

	/*
	Sorteaza disciplinele dupa cadru didactic si tip
	return->Repository, repository-ul disciplinelor sortate
	*/
	const Repository sorteaza_dupa_cadru_didactic_si_tip();

	/*
	Sorteaza discipline la modul general
	cmp->functia de comparare
	*/
	const Repository sorteaza_general(const bool (*cmp)(const Disciplina& d1,const Disciplina& d2));

	/*
	Goleste contractul
	*/
	void goleste();

	/*
	Determina numarul de elemente din contract
	*/
	size_t nr_contracte();

	/*
	Adauga o disciplina in contract dupa denumire
	denumire->string, denumirea disciplinei care se va adauga in contract
	*/
	const Disciplina adauga_in_contract(const string& denumire);

	/*
	Determina un sir cu disciplinele din contract
	*/
	const string str_contract();

	/*
	Genereaza contracte cu discimpline la intamplare
	n->int, numarul total de discipline
	*/
	void genereaza_contracte(int n);

	/*
	Sterge toate disciplinele gasita cu un anumit tip
	*/
	void sterge_tip(const string& tip);

	/*
	Salveaza toate disciplinele din contract
	nume_fisier->string, numele fisierului in care se va face salvarea
	*/
	void salveaza_contract(const string& nume_fisier);

	/*
	Face undo la lista
	*/
	void undo();

	/*
	Deconstrucotr
	*/
	~Service() {
		for (auto& el : actiuniUndo) {
			delete el;
		}
	}

};