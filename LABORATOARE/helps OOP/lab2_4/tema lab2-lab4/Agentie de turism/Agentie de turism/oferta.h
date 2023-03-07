#pragma once
typedef struct {
	char tip[20];
	char destinatie[20];
	char data[20];
	int pret;
}Oferta;

typedef struct {
	Oferta lista_0ferte[100];
	int lng;
}Oferte;