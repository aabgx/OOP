#pragma once
#include <vector>
#include <string>

using namespace std;

class ExceptiiValidare {
private:
	/*
	Aici e reprezentarea interna
	*/
	string errorMsg;

public:
	/*
	Interfata publica
	*/
	ExceptiiValidare(string err) {
		errorMsg = err;
	}

	string get_Msg() {
		return errorMsg;
	}
};

class Validator {
private:
	/*
	Aici e reprezentarea
	*/
public:
	/*
	Interfata publica
	*/
	Validator(){}

	/*
	Valideaza o disciplina
	denumire->string, denumirea disciplinei
	ore_pe_saptamana->string, orele pe saptamana a disciplinei
	tip->string, tipul disciplinei
	cadru_didactic->string, cadrul didactic al disciplinei
	throw:ExceptiiValidare, daca disciplina nu este valida
	*/
	void valideaza_disciplina(const string& denumire, const string& ore_pe_saptamana, const string& tip, const string& cadru_didactic) {
		string de_ret = "";
		try {
			int ore = stoi(ore_pe_saptamana);
			if (ore <= 0) {
				de_ret += "Orele pe saptamana trebuie sa fie un numar mai mare decat 0!\n";
			}
		}
		catch (exception&) {
			de_ret += "Orele pe saptamana trebuie sa fie un numar!\n";
		}
		if (denumire == "")de_ret += "Denumirea trebuie sa fie un nume nevid!\n";
		if (tip == "")de_ret += "Tipul trebuie sa fie un nume nevid!\n";
		if (cadru_didactic == "")de_ret += "Cadrul didactic trebuie sa fie un nume nevid!\n";
		if (de_ret != "")throw(ExceptiiValidare(de_ret));

	}

	/*
	Valideaza daca numarul minim si numarul maxim sunt numere
	nr_minim->string, numarul minim
	nr_maxim->string, numarul maxim
	throw:ExceptiiValidare, daca numerele date nu sunt numere
	*/
	void valideaza_numere(const string& numar_minim, const string& numar_maxim) {
		string de_ret = "";
		try{
			int minim = stoi(numar_minim);
			if (minim < 0)de_ret += "Numarul minim trebuie sa fie mai mare sau egal cu 0!\n";
		}
		catch (exception&) {
			de_ret += "Numarul minim trebuie sa fie un numar!\n";
		}
		try {
			int maxim = stoi(numar_maxim);
			if (maxim < 0)de_ret += "Numarul maxim trebuie sa fie mai mare sau egal cu 0!\n";
		}
		catch (exception&) {
			de_ret += "Numarul maxim trebuie sa fie un numar!\n";

		}
		if (de_ret != "")throw ExceptiiValidare(de_ret);
	}

	/*
	Valideaza numarul de discipline pe care trebuie sa il validam
	n->string, numarul de discipline pe care trebuie sa le validam
	throw::ExceptiiValidare, daca parametrul dat nu este un numar
	*/
	void valideaza_nr_de_generare(const string& n) {
		string de_ret = "";
		try{
			int nr = stoi(n);
			if (nr <= 0) de_ret += "Numarul de discipline generate trebuie sa fie mai mare decat 0!\n";
		}
		catch (exception&) {
			de_ret += "Numarul de discipline generate trebuie sa fie un numar!\n";
		}
		if (de_ret != "")
			throw ExceptiiValidare(de_ret);
	}
};