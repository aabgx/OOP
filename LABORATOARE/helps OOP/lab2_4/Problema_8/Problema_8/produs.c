#include "produs.h"
#include <string.h>
#pragma warning(disable : 4996)

Produs creare_produs(int id, int pret, int cantitate, char* tip, char* producator, char* model) {
	Produs pr;
	pr.id = id;
	pr.pret = pret;
	pr.cantitate = cantitate;
	strcpy(pr.tip, tip);
	strcpy(pr.producator, producator);
	strcpy(pr.model, model);
	return pr;
}

int get_id(Produs pr) {
	return pr.id;
}
int get_pret(Produs pr) {
	return pr.pret;
}
int get_cantitate(Produs pr) {
	return pr.cantitate;
}
char* get_tip(Produs pr) {
	return pr.tip;
}
char* get_producator(Produs pr) {
	return pr.producator;
}
char* get_model(Produs pr) {
	return pr.model;
}

void modificare_pret(Produs* pr, int noul_pret) {
	pr->pret = noul_pret;
}

void modificare_cantitate(Produs* pr, int noua_cantitate) {
	pr->cantitate = noua_cantitate;
}