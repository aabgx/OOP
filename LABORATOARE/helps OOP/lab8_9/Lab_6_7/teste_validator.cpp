#include "validator.h"
#include <string>
#include <cassert>

using namespace std;

void test_valideaza_disciplina() {
	Validator v;
	//1
	string denumire = "";
	string ore = "";
	string tip = "";
	string cadru = "";
	bool ok = false;
	try {
		v.valideaza_disciplina(denumire, ore, tip, cadru);
	}
	catch (ExceptiiValidare& ) {
		ok = true;
	}
	assert(ok);
	//2
	ok = false;
	denumire = "p";
	ore = "p";
	tip = "p";
	cadru = "p";
	try {
		v.valideaza_disciplina(denumire, ore, tip, cadru);
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);
	//3
	ok = false;
	denumire = "p";
	ore = "-1";
	tip = "p";
	cadru = "p";
	try {
		v.valideaza_disciplina(denumire, ore, tip, cadru);
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);
	//4
	denumire = "p";
	ore = "1";
	tip = "p";
	cadru = "p";
	v.valideaza_disciplina(denumire, ore, tip, cadru);
}

void test_valideaza_numere() {
	Validator v;
	//1
	string nr_minim = "p";
	string nr_maxim = "p";
	bool ok=false;
	try {
		v.valideaza_numere(nr_minim, nr_maxim);
		
	}
	catch (ExceptiiValidare&) {
		ok = true;
	}
	assert(ok);
	//2
	nr_minim = "-1";
	nr_maxim = "-1";
	try {
		v.valideaza_numere(nr_minim, nr_maxim);
	}
	catch (ExceptiiValidare& el) {
		assert(el.get_Msg() != "");
	}
	//3
	nr_minim = "2";
	nr_maxim = "3";

	v.valideaza_numere(nr_minim, nr_maxim);
}

void test_valideaza_nr_de_generare() {
	Validator v;
	//1
	string p = "asdad";
	bool ok = false;
	try {
		v.valideaza_nr_de_generare(p);
	}
	catch (ExceptiiValidare& el) {
		assert(el.get_Msg() != "");
		ok = true;
	}
	assert(ok);
	//2
	p = "-1";
	ok = false;
	try {
		v.valideaza_nr_de_generare(p);
	}
	catch (ExceptiiValidare& el) {
		assert(el.get_Msg() != "");
		ok = true;
	}
	assert(ok);
	//3
	p = "3";
	v.valideaza_nr_de_generare(p);

}