#pragma warning(suppress : 4996)
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "produs.h"

void test_creare_produs() {
	//1
	Produs pr = creare_produs(1, 10, 20, "tip", "producator", "model");
	assert(get_id(pr) == 1);
	assert(get_pret(pr) == 10);
	assert(get_cantitate(pr) == 20);
	assert(strcmp(get_tip(pr),"tip") == 0);
	assert(strcmp(get_producator(pr),"producator") == 0);
	assert(strcmp(get_model(pr),"model") == 0);
	//2
	pr = creare_produs(5, 32, 42, "tip2", "producator2", "model2");
	assert(get_id(pr) == 5);
	assert(get_pret(pr) == 32);
	assert(get_cantitate(pr) == 42);
	assert(strcmp(get_tip(pr), "tip2") == 0);
	assert(strcmp(get_producator(pr), "producator2") == 0);
	assert(strcmp(get_model(pr), "model2") == 0);
	//3
	pr = creare_produs(13, 103, 203, "tip3", "producator3", "model3");
	assert(get_id(pr) == 13);
	assert(get_pret(pr) == 103);
	assert(get_cantitate(pr) == 203);
	assert(strcmp(get_tip(pr), "tip3") == 0);
	assert(strcmp(get_producator(pr), "producator3") == 0);
	assert(strcmp(get_model(pr), "model3") == 0);
}

void test_modificare_pret() {
	//1
	Produs pr = creare_produs(1, 10, 20, "tip", "producator", "model");
	modificare_pret(&pr, 55);
	assert(get_pret(pr) == 55);
	//2
	modificare_pret(&pr, 3921);
	assert(get_pret(pr) == 3921);
	//3
	modificare_pret(&pr, 5213125);
	assert(get_pret(pr) == 5213125);
}

void test_modificare_cantitate() {
	//1
	Produs pr = creare_produs(1, 10, 20, "tip", "producator", "model");
	modificare_cantitate(&pr, 55);
	assert(get_cantitate(pr) == 55);
	//2
	modificare_cantitate(&pr, 3921);
	assert(get_cantitate(pr) == 3921);
	//3
	modificare_cantitate(&pr, 5213125);
	assert(get_cantitate(pr) == 5213125);
}


void test_get_id() {
	//1
	Produs pr = creare_produs(1, 10, 20, "tip", "producator", "model");
	assert(get_id(pr) == 1);
	//2
	pr = creare_produs(2, 10, 20, "tip", "producator", "model");
	assert(get_id(pr) == 2);
	//3
	pr = creare_produs(2, 10, 20, "tip", "producator", "model");
	assert(get_id(pr) == 2);
}
void test_get_pret() {
	//1
	Produs pr = creare_produs(1, 10, 20, "tip", "producator", "model");
	assert(get_pret(pr) == 10);
	//2
	pr = creare_produs(2, 11, 20, "tip", "producator", "model");
	assert(get_pret(pr) == 11);
	//3
	pr = creare_produs(2, 12, 20, "tip", "producator", "model");
	assert(get_pret(pr) == 12);
}
void test_get_cantitate() {
	//1
	Produs pr = creare_produs(1, 1, 10, "tip", "producator", "model");
	assert(get_cantitate(pr) == 10);
	//2
	pr = creare_produs(2, 10, 11, "tip", "producator", "model");
	assert(get_cantitate(pr) == 11);
	//3
	pr = creare_produs(2, 10, 12, "tip", "producator", "model");
	assert(get_cantitate(pr) == 12);
}
void test_get_tip() {
	//1
	Produs pr = creare_produs(1, 1, 10, "tip", "producator", "model");
	assert(strcmp(get_tip(pr),"tip")==0);
	//2
	pr = creare_produs(2, 10, 11, "tip1", "producator", "model");
	assert(strcmp(get_tip(pr), "tip1") == 0);
	//3
	pr = creare_produs(2, 10, 12, "tip2", "producator", "model");
	assert(strcmp(get_tip(pr), "tip2") == 0);
}
void test_get_producator() {
	//1
	Produs pr = creare_produs(1, 1, 10, "tip", "producator", "model");
	assert(strcmp(get_producator(pr), "producator") == 0);
	//2
	pr = creare_produs(2, 10, 11, "tip1", "producator1", "model");
	assert(strcmp(get_producator(pr), "producator1") == 0);
	//3
	pr = creare_produs(2, 10, 12, "tip2", "producator2", "model");
	assert(strcmp(get_producator(pr), "producator2") == 0);
}
void test_get_model() {
	//1
	Produs pr = creare_produs(1, 1, 10, "tip", "producator", "model");
	assert(strcmp(get_model(pr), "model") == 0);
	//2
	pr = creare_produs(2, 10, 11, "tip1", "producator1", "model1");
	assert(strcmp(get_model(pr), "model1") == 0);
	//3
	pr = creare_produs(2, 10, 12, "tip2", "producator2", "model2");
	assert(strcmp(get_model(pr), "model2") == 0);
}