#pragma once
#include <string>

using namespace std;

class Disciplina {
private:
	/*
	Reprezentarea interna
	*/
	string denumire;
	int ore_pe_saptamana;
	string tip;
	string cadru_didactic;
public:
	/*
	Aici e interfata publica
	*/
	Disciplina(const string denumire,int ore_pe_saptamana,const string tip, const string cadru_didactic);

	/*
	Constructor default
	*/
	Disciplina(){};

	/*
	Constructor
	*/
	Disciplina(const Disciplina& d);



	/*
	Returneaza denumirea Disciplinei actuale
	return->string, denumirea disciplinei
	*/
	string get_denumire();

	/*
	Returneaza orele pe saptamana Disciplinei acutale
	return->int, orele pe saptamana
	*/
	int get_ore_pe_saptamana();

	/*
	Returneaza tipul Disciplinei actuale
	return->string, tip-ul disciplinei
	*/
	string get_tip();

	/*
	Returneaza cadrul didactic al disciplinei
	return->string, cadrul didactic al curentei Discipline
	*/
	string get_cadru_didactic();

	/*
	Seteaza o anumita denumire pentru Disciplina actuala
	denumire->string, noul nume al disciplinei
	*/
	void set_denumire(const string& denumire);

	/*
	Seteaza orele pe saptamana al Disciplinei actuale
	ore_pe_saptamana->int, noile ore pe saptamana ale saptamanii actuale
	*/
	void set_ore_pe_saptamana(const int& ore_pe_saptamana);

	/*
	Seteaza un nou tip al Disciplinei actuale
	tip->string, noul tip al disciplinei actuale
	*/
	void set_tip(const string& tip);

	/*
	Seteaza un nou cadru didactic Disciplinei actuale
	cadru_didactic->string, noul cadru didactic al Disciplinei actuale
	*/
	void set_cadru_didactic(const string& cadru_didactic);

	/*
	Verifica daca disciplina actuala este egala cu o alta disciplina
	d->Disciplina, disciplina de comparare
	return->true, daca cele 2 sunt egale, si false altfel
	*/
	bool egale(Disciplina d);

	/*
	Suprascire operatorul "=="
	*/
	bool operator==(const Disciplina& d) {
		return this->egale(d);
	}

	/*
	Determina sirul care poate sa afiseze o disciplina la tastatura
	return->string, string-ul care va; fi afisat la tastatura
	*/
	string str();
};