#pragma once
#include "produs.h"
#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable : 4996)

void adaugare_produs(Vector* v, int id, int pret, int cantitate, char* tip, char* producator, char* model)
{
	Produs pr;
	pr = creare_produs(id, pret, cantitate, tip, producator, model);
	add(v, pr);
}

Produs get_produs(Vector* v, int poz) {
	return get(v, poz);
}
int get_total_produse(Vector* v) {
	return get_size(v);
}

int cautare_produs(Vector* v, int id) {
	Produs* pr;
	for (int i = 0; i < get_size(v); i++) {
		if (get_id(get(v,i)) == id) {
			return i;
		}
	}
}

void modificare_pret_produs(Vector* v, int id, int pret){
	int poz = cautare_produs(v, id);
	Produs* pr = get_adresa(v, poz);
	modificare_pret(pr, pret);
}

void modificare_cantitate_produs(Vector* v, int id, int cantitate) {
	int poz = cautare_produs(v, id);
	Produs* pr = get_adresa(v, poz);
	modificare_cantitate(pr, cantitate);
}
