#pragma once
#include "domain.h"
#include "vector_dinamic.h"


/*
Clasa de exceptii a repozitoriului
*/
class RepoException {
private: 
	std::string errors;
public:
	RepoException(std::string) :errors{ errors } {};
	std::string get_errors() {
		return this->errors;
	}
};

/*
Clasa repo a activitatii.
*/
class ActivitateRepository {
private: 
	VectorDinamic<Activitate> lista_activitati;
public:

	ActivitateRepository() {
		VectorDinamic<Activitate> lst;
		lista_activitati = lst;
	}
	
	//nu se poate face copie
	ActivitateRepository(const ActivitateRepository& ot) = delete;

	//functia care adauga o activitate
	void add(const Activitate& a);

	//functia care sterge o activitate
	void dell(Activitate& a);

	//functia modifica o activitate
	void modify(Activitate& a);

	//functia care returneaza lista de activitati
	const VectorDinamic<Activitate>& get_all_activities();
	
	//functia care cauta o activitate dupa titlu
	const Activitate& find(std::string titlu);
	
	//functia care returneaza dimensiunea listei de activitati
	int get_dim();

	//functia care verifica daca o activitate exista sau nu in lista
	bool exists(const Activitate& a);
};

void teste_repo();
void test_resize();