#include "vector.h"
#include "produs.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INIT_CAPACITY 100

Vector* creazaVectorDinamic() {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->elems = (Produs*)malloc((INIT_CAPACITY) * sizeof(Produs));
	v->cp = INIT_CAPACITY;
	v->n = 0;
	return v;
}

Produs* get_elems(Vector* v) {
	return v->elems;
}

int get_capacity(Vector* v) {
	return v->cp;
}

int get_size(Vector* v) {
	return v->n;
}

void distruge(Vector* v) {
	int i;
	free(get_elems(v));
	free(v);
	v = NULL;
}

void modifica_capacitate(Vector* v,int cp) {
	v->cp = cp;
}

void modifica_size(Vector* v, int n) {
	v->n = n;
}

void modifica_elems(Vector* v, Produs* nElems) {
	v->elems = nElems;
}

void resize(Vector* v){
	int n_cp = (v->cp) * 2;
	Produs* nElems = (Produs*)malloc(n_cp * sizeof(Produs));
	int i;
	for (i = 0; i < get_size(v); ++i)
	{
		nElems[i] = get(v,i);
	}
	free(get_elems(v));
	modifica_capacitate(v, n_cp);
	modifica_elems(v, nElems);
}

void add(Vector* v, Produs pr)
{
	if (get_size(v) == get_capacity(v))resize(v);
	get_elems(v)[v->n] = pr;
	modifica_size(v, get_size(v) + 1);
}

Produs get( Vector* v, int poz) {
	return get_elems(v)[poz];
}
Produs* get_adresa(Vector* v, int poz) {
	Produs* p = &(get_elems(v)[poz]);
	return p;
}

