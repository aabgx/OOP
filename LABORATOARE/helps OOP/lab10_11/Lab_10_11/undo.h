#pragma once
#include "domain.h"
#include "repo.h"
#include <iostream>

using namespace std;

class ActiuneUndo {
public:
	virtual void doUndo() = 0; // functie pur virtuala deci clasa e abstracta
	//Deconstruco
	virtual ~ActiuneUndo() = default;
};


class UndoAdauga:public ActiuneUndo{
private:
	Repository& repo; // Repository-ul disciplinelir
	Disciplina d_adaugata; // Disciplina adaugata
public:
	/*
	Constructorul
	*/
	UndoAdauga(Repository& r,Disciplina d): repo{r},d_adaugata{d}{}
	void doUndo() {
		repo.sterge(d_adaugata);
	}
};

class UndoSterge:public ActiuneUndo {
private:
	Repository& repo; // Repository-ul disciplinelir
	Disciplina d_stearsa; // Disciplina stearsa
public:
	/*
	Constructorul
	*/
	UndoSterge(Repository& r, Disciplina d) : repo{ r }, d_stearsa{ d }{}

	void doUndo() {
		repo.adauga(d_stearsa);
	}
};

class UndoModifica :public ActiuneUndo {
private:
	Repository& repo; // Repository-ul disciplinelir
	Disciplina d_inainte; // Disciplina de dinainte de stergere
	Disciplina d_dupa; // Disciplina de dupa stergere
public:
	/*
	Constructorul
	*/
	UndoModifica(Repository& r, Disciplina d1, Disciplina d2) : repo{ r }, d_inainte{ d1 }, d_dupa{ d2 }{}

	void doUndo() {
		repo.find(d_dupa.get_denumire()) = d_inainte;
	}
};