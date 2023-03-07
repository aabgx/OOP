#include <stdio.h>
#include "ui.h"
#include "operatii.h"
#include <string.h>
#include "validatori.h"
#pragma warning(disable:4996)

void print_menu() {
	printf("1. Adauga oferta.\n");
	printf("2. Actualizeaza oferta.\n");
	printf("3. Sterge oferta.\n");
	printf("4. Vizualizare oferte ordonate dupre pret sau destinatie, crescator sau descrescator.\n");
	printf("5. Vizualizare oferte filtrate dupa un criteriu: destinatie, tip, pret.\n");
	printf("6. Iesire din aplicatie.\n");
}

void opt_1(Service* service) {
	char tip[20] = "", destinatie[20] = "", data[20] = "";
	int pret;

	do {
		printf("Introdu tipul ofertei(mare, munte, city break): ");
		scanf("%s", tip);
	} while (valid_cuvant(tip) == false);

	do {
		printf("Introdu destinatia: ");
		scanf("%s", destinatie);
	} while (valid_cuvant(destinatie) == false);

	do {
		printf("Introdu data de plecare: ");
		scanf("%s", data);
	} while (valid_cuvant(data) == false);
	printf("Introdu costul ofertei: ");
	scanf("%d", &pret);
	
	Oferta offer;
	strcpy(offer.data, data);
	strcpy(offer.destinatie, destinatie);
	strcpy(offer.tip, tip);
	offer.pret = pret;
	Service* nou_service = service;
	
	adauga(nou_service, tip, destinatie, data, pret);
}

void opt_2(Service* service) {
	char tip[20] = "", destinatie[20] = "", data[20] = "";
	int pret;
	int poz;

	do {
		printf("Introdu pozitia ofertei: ");
		scanf("%d", &poz);
	} while (valid_poz(&(service), poz) == false);

	do {
		printf("Introdu tipul ofertei(mare, munte, city break): ");
		scanf("%s", tip);
	} while (valid_cuvant(tip) == false);
	
	do {
		printf("Introdu destinatia: ");
		scanf("%s", destinatie);
	} while (valid_cuvant(destinatie) == false);

	do {
		printf("Introdu data de plecare: ");
		scanf("%s", data);
	} while (valid_cuvant(data) == false);

	printf("Introdu costul ofertei: ");
	scanf("%d", &pret);

	Oferta offer;
	strcpy(offer.data, data);
	strcpy(offer.destinatie, destinatie);
	strcpy(offer.tip, tip);
	offer.pret = pret;
	Service* nou_service = service;

	actualizare(nou_service, poz, tip, destinatie, data, pret);
}

void opt_3(Service* service) {
	int poz;

	do {
		printf("Introdu pozitia ofertei: ");
		scanf("%d", &poz);
	} while (valid_poz(&(service), poz) == false);

	Service* nou_service = service;

	sterge(nou_service, poz);
}

void opt_4(Service service) {
	char crit[20];
	int dir = 0;
	Service lista_noua;

	printf("Criteriul dupa care se ordoneaza: ");
	scanf("%s", crit);
	printf("1 pentru crescator, -1 pt descrescator: ");
	scanf("%d", &dir);
	lista_noua = ordonare_pret_or_dest_cresc_or_descresc(service, crit, dir);

	for (int i = 1; i <= lista_noua.list_offer.lng; i++)
		printf("%d%c %s %s %s %d\n", i, '.', lista_noua.list_offer.lista_0ferte[i].tip, lista_noua.list_offer.lista_0ferte[i].destinatie,
			lista_noua.list_offer.lista_0ferte[i].data, lista_noua.list_offer.lista_0ferte[i].pret);
}

void opt_5(Service service) {
	Service lista_noua;
	char tip_crit[20] = "";
	char sir[20];
	int pret;
	void* crit = 0;

	printf("Tipul criteriului: ");
	scanf("%s", tip_crit);
	printf("Criteriul: ");
	if (strcmp(tip_crit, "pret") == 0)
	{
		scanf("%d", &pret);
		crit = &pret;
	}
	else { 
		scanf("%s", sir);
		crit = &sir;
	}
	lista_noua = filtrare_criteriu(service, tip_crit, crit);

	for (int i = 1; i <= lista_noua.list_offer.lng; i++)
		printf("%d%c %s %s %s %d\n", i, '.', lista_noua.list_offer.lista_0ferte[i].tip, lista_noua.list_offer.lista_0ferte[i].destinatie,
			lista_noua.list_offer.lista_0ferte[i].data, lista_noua.list_offer.lista_0ferte[i].pret);
}

void run(UI prg) {
	int cmd;
	testare();
	while (1)
	{
		print_menu();
		if(prg.service.list_offer.lng > 0)
			for(int i = 1; i <= prg.service.list_offer.lng; i ++)
				printf("%d%c %s %s %s %d\n", i, '.', prg.service.list_offer.lista_0ferte[i].tip, prg.service.list_offer.lista_0ferte[i].destinatie,
					prg.service.list_offer.lista_0ferte[i].data, prg.service.list_offer.lista_0ferte[i].pret);
		printf("Comanda este: ");
		scanf_s("%d", &cmd);
		switch (cmd)
		{
		case 1:
			opt_1(&prg.service);
			break;

		case 2:
			opt_2(&prg.service);
			break;

		case 3:
			opt_3(&prg.service);
			break;

		case 4:
			opt_4(prg.service);
			break;

		case 5:
			opt_5(prg.service);
			break;

		case 6:
			return;
		}
	}
}