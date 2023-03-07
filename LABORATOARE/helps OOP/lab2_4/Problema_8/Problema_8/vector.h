#pragma once
#include "produs.h"


struct Vector{
	Produs* elems;
	int n;//nr de elemente din vectorul dinamic
	int cp;//capacitate
};
typedef struct Vector Vector;

Produs* get_elems(Vector* v);
int get_capacity(Vector* v);
int get_size(Vector* v);
void modifica_capacitate(Vector* v, int cp);
void modifica_size(Vector* v, int n);
void modifica_elems(Vector* v, Produs* nElems);
Vector* creazaVectorDinamic();
void distruge(Vector* v);
void add(Vector* v, Produs pr);
Produs get(Vector* v, int poz);
void resize(Vector* v);
Produs* get_adresa(Vector* v, int poz);
