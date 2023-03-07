#pragma once
#include "produs.h"
#include "vector.h"

void adaugare_produs(Vector* v, int id, int pret, int cantitate, char* tip, char* producator, char* model);
Produs get_produs(Vector* v, int poz);
int get_total_produse(Vector* v);
int cautare_produs(Vector* v, int id);
void modificare_pret_produs(Vector* v, int id, int pret);
void modificare_cantitate_produs(Vector* v, int id, int cantitate);
