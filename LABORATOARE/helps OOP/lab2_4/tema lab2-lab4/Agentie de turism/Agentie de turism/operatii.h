#pragma once
#include "oferta.h"
#include "validatori.h"
#include "validatori.h"

typedef struct {
	Oferte list_offer;
} Service;

Oferta creeaza(char tip[20], char destinatie[20], char data[20], int pret);
void adauga(Service* service, char tip[20], char destinatie[20], char data[20], int pret);
void actualizare(Service* service, int poz, char tip[20], char destinatie[20], char data[20], int pret);
void sterge(Service* service, int poz);
Service ordonare_pret_or_dest_cresc_or_descresc(Service service, char crit[20], int dir);
Service filtrare_criteriu(Service service, char tip_crit[20], void* crit);