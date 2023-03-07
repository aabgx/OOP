#pragma once
#include "produs.h"
#include "service.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>

void test_adaugare_produs() {
	Vector* v = creazaVectorDinamic();
	Produs pr, prr;
	//1
	pr = creare_produs(15, 1, 20, "BASIC", "BASIC", "BASIC");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	assert(get_total_produse(v) == 1);
	//2
	pr = creare_produs(12, 12, 230, "BASIC2", "BASIC2", "BASIC2");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	assert(get_total_produse(v) == 2);
	//3
	pr = creare_produs(31, 1242, 31312, "BASIC3", "BASIC3", "BASIC3");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	assert(get_total_produse(v) == 3);

}

void test_get_produs() {
	Vector* v = creazaVectorDinamic();
	Produs pr,prr;
	//1
	pr = creare_produs(15, 1, 20, "BASIC", "BASIC", "BASIC");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	prr = get_produs(v, 0);
	assert(get_id(pr) == get_id(prr));
	assert(get_pret(pr) == get_pret(prr));
	assert(get_cantitate(pr) == get_cantitate(prr));
	assert(strcmp(get_tip(pr), get_tip(prr)) == 0);
	assert(strcmp(get_producator(pr), get_producator(prr)) == 0);
	assert(strcmp(get_model(pr), get_model(prr)) == 0);
	//2
	pr = creare_produs(312, 1132, 32131, "BASIC2", "BASIC2", "BASIC2");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	prr = get_produs(v, 1);
	assert(get_id(pr) == get_id(prr));
	assert(get_pret(pr) == get_pret(prr));
	assert(get_cantitate(pr) == get_cantitate(prr));
	assert(strcmp(get_tip(pr), get_tip(prr)) == 0);
	assert(strcmp(get_producator(pr), get_producator(prr)) == 0);
	assert(strcmp(get_model(pr), get_model(prr)) == 0);
	//3
	pr = creare_produs(3123, 1412, 2311, "BASIC3", "BASIC3", "BASIC3");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	prr = get_produs(v, 2);
	assert(get_id(pr) == get_id(prr));
	assert(get_pret(pr) == get_pret(prr));
	assert(get_cantitate(pr) == get_cantitate(prr));
	assert(strcmp(get_tip(pr), get_tip(prr)) == 0);
	assert(strcmp(get_producator(pr), get_producator(prr)) == 0);
	assert(strcmp(get_model(pr), get_model(prr)) == 0);
}

void test_get_total_produse() {
	Vector* v = creazaVectorDinamic();
	Produs pr, prr;
	for (int i = 1; i <= 80; i++)
	{
	pr = creare_produs(15, 1, 20, "BASIC", "BASIC", "BASIC");
	adaugare_produs(v, get_id(pr), get_pret(pr), get_cantitate(pr), get_tip(pr), get_producator(pr), get_model(pr));
	}
	assert(get_total_produse(v) == 80);
	distruge(v);
}

void test_cautare_produs() {
	Vector* v = creazaVectorDinamic();
	Produs pr;
	//1
	pr = creare_produs(1, 1, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	assert(cautare_produs(v,get_id(pr)) == 0);
	//2
	pr = creare_produs(2, 1, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	assert(cautare_produs(v,get_id(pr)) == 1);
	//3
	pr = creare_produs(3, 1, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	assert(cautare_produs(v,get_id(pr)) == 2);
	//4
	pr = creare_produs(4, 1, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	assert(cautare_produs(v,get_id(pr)) == 3);
	//5
	pr = creare_produs(5, 1, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	assert(cautare_produs(v, get_id(pr)) == 4);
	distruge(v);
}

void test_modificare_pret_produs() {
	Vector* v = creazaVectorDinamic();
	Produs pr;
	//1
	pr = creare_produs(1, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v,pr);
	modificare_pret_produs(v, get_id(pr), 10);
	assert(get_pret(get(v,0)) == 10);
	//2
	pr = creare_produs(2, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	modificare_pret_produs(v, pr.id, 32);
	assert(get_pret(get(v, 1)) == 32);
	//3
	pr = creare_produs(3, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	modificare_pret_produs(v, pr.id, 1015);
	assert(get_pret(get(v, 2)) == 1015);
	distruge(v);
}
void test_modificare_cantitate_produs() {
	Vector* v = creazaVectorDinamic();
	Produs pr;
	//1
	pr = creare_produs(1, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	modificare_cantitate_produs(v, 1, 20);
	assert(get_cantitate(get(v, 0)) == 20);
	//2
	pr = creare_produs(2, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	modificare_cantitate_produs(v, 2, 30);
	assert(get_cantitate(get(v, 1)) == 30);
	//3
	pr = creare_produs(3, 5, 20, "BASIC", "BASIC", "BASIC");
	add(v, pr);
	modificare_cantitate_produs(v, 3, 40);
	assert(get_cantitate(get(v, 2)) == 40);
}