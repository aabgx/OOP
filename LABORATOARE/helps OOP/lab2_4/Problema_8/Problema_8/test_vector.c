#include "produs.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
#define INIT_CAPACITY 100

void test_creazaVectorDinamic()
{
	Vector* v = creazaVectorDinamic();
	assert(get_capacity(v) == INIT_CAPACITY);
	assert(get_size(v) == 0);
	distruge(v);
}

void test_distruge()
{
	Vector* v = creazaVectorDinamic();
	assert(get_capacity(v) == INIT_CAPACITY);
	assert(get_size(v) == 0);
	distruge(v);
}

void test_resize()
{
	Vector* v = creazaVectorDinamic();
	assert(get_capacity(v) == INIT_CAPACITY);
	assert(get_size(v) == 0);
	Produs pr;
	for (int i = 0; i <= 100; ++i)
	{
		pr = creare_produs(i * 15, i, 20, "BASIC", "BASIC", "BASIC");
		add(v, pr);
	}
	assert(get_capacity(v) == 2 * INIT_CAPACITY);
	distruge(v);
}

void test_get() {
	Vector* v = creazaVectorDinamic();
	assert(get_capacity(v) == INIT_CAPACITY);
	assert(get_size(v) == 0);
	Produs pr1, pr2;
	//1
	pr1 = creare_produs(1, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	add(v, pr1);
	pr2 = get(v, 0);
	assert(get_id(pr1) == get_id(pr2));
	assert(get_size(v) == 1);
	//2
	pr1 = creare_produs(60, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	add(v, pr1);
	pr2 = get(v, 1);
	assert(get_id(pr1) == get_id(pr2));
	assert(get_size(v) == 2);
	//3
	pr1 = creare_produs(65, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	add(v, pr1);
	pr2 = get(v, 2);
	assert(get_id(pr1) == get_id(pr2));
	assert(get_size(v) == 3);
	//4
	pr1 = creare_produs(66, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	add(v, pr1);
	pr2 = get(v, 3);
	assert(get_id(pr1) == get_id(pr2));
	assert(get_size(v) == 4);
	distruge(v);
}

void test_get_capacity() {
	Vector* v = creazaVectorDinamic();
	Produs pr = creare_produs(66, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	for(int i=0;i<100;++i)
		add(v, pr);
	assert(get_capacity(v) == 100);
	add(v, pr);
	assert(get_capacity(v) == 200);
	distruge(v);
}

void test_modifica_capacitate() {
	Vector* v = creazaVectorDinamic();
	//1
	modifica_capacitate(v, 20);
	assert(get_capacity(v) == 20);
	//2
	modifica_capacitate(v, 32);
	assert(get_capacity(v) == 32);
	//3
	modifica_capacitate(v, 100);
	assert(get_capacity(v) == 100);
}

void test_modifica_size() {
	Vector* v = creazaVectorDinamic();
	//1
	modifica_size(v, 20);
	assert(get_size(v) == 20);
	//2
	modifica_size(v, 12);
	assert(get_size(v) == 12);
	//2
	modifica_size(v, 13);
	assert(get_size(v) == 13);
	distruge(v);
}

void test_get_size() {
	Vector* v = creazaVectorDinamic();
	Produs pr = creare_produs(66, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	for (int i = 0; i < 90; i++)
		add(v, pr);
	assert(get_size(v) == 90);
	distruge(v);
}

void test_get_elems() {
	Vector* v = creazaVectorDinamic();
	Produs pr = creare_produs(66, 2, 3, "TIP", "PRODUCATOR", "MODEL");
	add(v, pr);
	Produs pr2 = get_elems(v)[0];
	assert(get_id(pr) == get_id(pr2));
	assert(get_pret(pr) == get_pret(pr2));
	assert(get_cantitate(pr) == get_cantitate(pr2));
	assert(strcmp(get_tip(pr), get_tip(pr2)) == 0);
	assert(strcmp(get_producator(pr), get_producator(pr2)) == 0);
	assert(strcmp(get_model(pr), get_model(pr2)) == 0);
	distruge(v);
}

void test_modifica_elems() {
	Vector* v = creazaVectorDinamic();
	Vector* v2 = creazaVectorDinamic();
	modifica_elems(v, get_elems(v2));
	assert(get_elems(v) == get_elems(v2));
	distruge(v);
}