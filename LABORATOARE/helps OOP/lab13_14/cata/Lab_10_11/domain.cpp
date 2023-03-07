#pragma once
#include "domain.h"
using namespace std;

Disciplina::Disciplina(const string denumire, int ore_pe_saptamana, const string tip, const string cadru_didactic) {
	this->denumire = denumire;
	this->ore_pe_saptamana = ore_pe_saptamana;
	this->tip = tip;
	this->cadru_didactic = cadru_didactic;
}

string Disciplina::get_denumire() const {
	return denumire;
}

int Disciplina::get_ore_pe_saptamana() const {
	return this->ore_pe_saptamana;
}

string Disciplina::get_tip() const {
	return this->tip;
}

string Disciplina::get_cadru_didactic() const{
	return this->cadru_didactic;
}

void Disciplina::set_denumire(const string& denumire2) {
	this->denumire = denumire2;
}

void Disciplina::set_ore_pe_saptamana(const int& ore_pe_saptamana2) {
	this->ore_pe_saptamana = ore_pe_saptamana2;
}

void Disciplina::set_tip(const string& tip2) {
	this->tip = tip2;
}

void Disciplina::set_cadru_didactic(const string& cadru_didactic2) {
	this->cadru_didactic = cadru_didactic2;
}

bool Disciplina::egale(Disciplina d) const {
	return this->get_denumire() == d.get_denumire();
}

string Disciplina::str() const {
	string ore_pe_saptamana2 = to_string(this->ore_pe_saptamana);

	return "DENUMIRE: " + this->denumire + " | ORE PE SAPTAMANA: " + ore_pe_saptamana2 + " | TIP: " + this->tip + " | CADRU DIDACTIC: " + this->cadru_didactic;
}

Disciplina::Disciplina(const Disciplina& d) {
	this->denumire = d.denumire;
	this->ore_pe_saptamana = d.ore_pe_saptamana;
	this->tip = d.tip;
	this->cadru_didactic = d.cadru_didactic;
}