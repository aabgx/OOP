#include "oferta.h"
#include "operatii.h"
#include <assert.h>
#include <string.h>
#pragma warning(disable:4996)

Oferta creeaza(char tip[20], char destinatie[20], char data[20], int pret) {
	/*
	Creeaza un obiect de tip Oferta.
	pre: True
	post: obiectul a fost creat
	tip - tipul ofertei
	destinatie - destinatia 
	data - data de plecare
	pret - pretul ofertei
	return - oferta creata
	rtype - Oferta
	*/
	Oferta offer;
	strcpy(offer.data, data);
	strcpy(offer.destinatie, destinatie);
	strcpy(offer.tip, tip);
	offer.pret = pret;
	
	return offer;
}

void adauga(Service* service, char tip[20], char destinatie[20], char data[20], int pret) {
	/*
	Adauga o oferta in lista de oferte.
	pre: True
	post: oferta a fost adaugata
	service - spatiul in care se afla lista de oferte
	tip - tipul ofertei
	destinatie - destinatia
	data - data de plecare
	pret - pretul ofertei
	*/
	service->list_offer.lista_0ferte[service->list_offer.lng + 1] = creeaza(tip, destinatie, data, pret);
	service->list_offer.lng += 1;
}

void actualizare(Service* service, int poz, char tip[20], char destinatie[20], char data[20], int pret) {
	/*
	Actualizeaza o anumita oferta din lista.
	pre: pozitia sa fie una valida
	post: oferta a fost actualizata
	service - spatiul in care se afla lista de oferte
	poz - pozitia ofertei de actualizat
	tip - tipul ofertei
	destinatie - destinatia
	data - data de plecare
	pret - pretul ofertei
	*/
	service->list_offer.lista_0ferte[poz] = creeaza(tip, destinatie, data, pret);
}

void sterge(Service *service, int poz) {
	/*
	Sterge o oferta din lista de oferte.
	pre: pozitia sa fie una valida
	post: oferta a fost stearsa
	service - spatiul in care se afla lista de oferte
	poz - pozitia ofertei de actualizat
	*/
	for (int i = poz + 1; i <= service->list_offer.lng; i++)
		service->list_offer.lista_0ferte[i - 1] = service->list_offer.lista_0ferte[i];
	service->list_offer.lng -= 1;
}

Service ordonare_pret_or_dest_cresc_or_descresc(Service service, char crit[20], int dir) {
	/*
	Ordoneaza lista de oferte dupa un criteriu, crescator sau descrescator.
	pre: criteriul sa fie unul valid
	post: lista este ordonata
	service - spatiul in care se afla lista de oferte
	crit - criteriul dupa care se realizeaza ordonarea
	dir - indica daca ordonarea este crescatoare sau descrescatoare
	*/
	Service lista_noua = service;

	if (strcmp(crit, "destinatie") == 0)
	{
		for (int i = 1; i < lista_noua.list_offer.lng; i++)
			for (int j = i + 1; j <= lista_noua.list_offer.lng; j++)
				if ((strcmp(lista_noua.list_offer.lista_0ferte[i].destinatie, lista_noua.list_offer.lista_0ferte[j].destinatie) < 0 && dir == -1) ||
					(strcmp(lista_noua.list_offer.lista_0ferte[i].destinatie, lista_noua.list_offer.lista_0ferte[j].destinatie) > 0 && dir == 1))
				{
					Oferta aux = lista_noua.list_offer.lista_0ferte[i];
					lista_noua.list_offer.lista_0ferte[i] = lista_noua.list_offer.lista_0ferte[j];
					lista_noua.list_offer.lista_0ferte[j] = aux;
				}
	}
	else {
		for (int i = 1; i < lista_noua.list_offer.lng; i++)
			for (int j = i + 1; j <= lista_noua.list_offer.lng; j++)
				if ((lista_noua.list_offer.lista_0ferte[i].pret < lista_noua.list_offer.lista_0ferte[j].pret && dir == -1) ||
					(lista_noua.list_offer.lista_0ferte[i].pret > lista_noua.list_offer.lista_0ferte[j].pret && dir == 1))
				{
					Oferta aux = lista_noua.list_offer.lista_0ferte[i];
					lista_noua.list_offer.lista_0ferte[i] = lista_noua.list_offer.lista_0ferte[j];
					lista_noua.list_offer.lista_0ferte[j] = aux;
				}
	}

	return lista_noua;
}

Service filtrare_criteriu(Service service, char tip_crit[20], void* crit) {
	/*
	Filtreaza lista dupa un criteriu.
	pre: criteriul sa fie valid
	post: lista a fost filtrata
	service - spatiul in care se afla lista de oferte
	tip_crit - tipul criteriului
	crit - criteriul
	*/
	Service lista_noua;
	char *char_ptr;
	char crit_str[20] = "";
	int cont = 0;
	if (strcmp(tip_crit, "destinatie") == 0 || strcmp(tip_crit, "tip") ==0)
	{
		char_ptr = (char*)crit;
		while (*char_ptr != '\0') {
			crit_str[cont] = *char_ptr;
			char_ptr ++;
			cont++;
		}
		crit_str[cont] = '\0';
	}
	lista_noua.list_offer.lng = 0;
	for (int i = 1; i <= service.list_offer.lng; i++)
		if ((strcmp(tip_crit, "destinatie") == 0 && strcmp(service.list_offer.lista_0ferte[i].destinatie, crit_str) == 0) ||
			(strcmp(tip_crit, "tip") == 0 && strcmp(service.list_offer.lista_0ferte[i].tip, crit_str) == 0) ||
			(strcmp(tip_crit, "pret") == 0 && service.list_offer.lista_0ferte[i].pret == *(int*)crit))
		{
			lista_noua.list_offer.lista_0ferte[lista_noua.list_offer.lng + 1] = service.list_offer.lista_0ferte[i];
			lista_noua.list_offer.lng += 1;
		}

	return lista_noua;
}


void test_creeaza() {
	char destinatie[20] = "Grecia";
	char tip[20] = "munte";
	char data[20] = "12/02/2021";
	int pret = 1000;
	Oferta offer = creeaza(tip, destinatie, data, pret);

	assert(strcmp(offer.destinatie, destinatie) == 0);
	assert(strcmp(offer.tip, tip) == 0);
	assert(strcmp(offer.data, data) == 0);
	assert(offer.pret == pret);
}

void test_adauga() {
	Service service_test;
	service_test.list_offer.lng = 0;
	Service *service_aux = &service_test;
	adauga(service_aux, "mare", "Italia", "12/09/2012", 2300);
	adauga(service_aux, "munte", "Spania", "13/08/2021", 8100);

	assert(service_test.list_offer.lng == 2);
	assert(strcmp(service_test.list_offer.lista_0ferte[2].data, "13/08/2021") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[2].destinatie, "Spania") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[2].tip, "munte") == 0);
	assert(service_test.list_offer.lista_0ferte[2].pret == 8100);
}

void test_actualizare() {
	Service service_test;
	service_test.list_offer.lng = 0;
	Service* service_aux = &service_test;
	adauga(service_aux, "mare", "Italia", "12/09/2012", 2300);
	actualizare(service_aux, 1, "munte", "Spania", "13/08/2021", 8100);

	assert(strcmp(service_test.list_offer.lista_0ferte[1].data, "13/08/2021") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[1].destinatie, "Spania") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[1].tip, "munte") == 0);
	assert(service_test.list_offer.lista_0ferte[1].pret == 8100);
}

void test_sterge() {
	Service service_test;
	service_test.list_offer.lng = 0;
	Service* service_aux = &service_test;
	adauga(service_aux, "mare", "Italia", "12/09/2012", 2300);
	adauga(service_aux, "munte", "Spania", "13/08/2021", 8100);

	sterge(service_aux, 1);
	assert(strcmp(service_test.list_offer.lista_0ferte[1].data, "13/08/2021") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[1].destinatie, "Spania") == 0);
	assert(strcmp(service_test.list_offer.lista_0ferte[1].tip, "munte") == 0);
	assert(service_test.list_offer.lista_0ferte[1].pret == 8100);
}

void test_ordonare_pret_or_dest_cresc_or_descresc() {
	Service service_test;
	service_test.list_offer.lng = 0;
	Service* service_aux = &service_test;
	adauga(service_aux, "mare", "Italia", "12/09/2012", 2300);
	adauga(service_aux, "munte", "Spania", "13/08/2021", 8100);
	adauga(service_aux, "city break", "Turcia", "17/05/2021", 3600);

	int pret1, pret2;
	Service list_nou = ordonare_pret_or_dest_cresc_or_descresc(service_test, "pret", 1);
	for (int i = 1; i < list_nou.list_offer.lng; i++)
	{
		pret1 = list_nou.list_offer.lista_0ferte[i].pret;
		pret2 = list_nou.list_offer.lista_0ferte[i + 1].pret;
		assert(pret1 <= pret2);
	}

	list_nou = ordonare_pret_or_dest_cresc_or_descresc(service_test, "pret", -1);
	for (int i = 1; i < list_nou.list_offer.lng; i++)
	{
		pret1 = list_nou.list_offer.lista_0ferte[i].pret;
		pret2 = list_nou.list_offer.lista_0ferte[i + 1].pret;
		assert(pret1 >= pret2);
	}

	char dest1[20], dest2[20];
	list_nou = ordonare_pret_or_dest_cresc_or_descresc(service_test, "destinatie", 1);
	for (int i = 1; i < list_nou.list_offer.lng; i++)
	{
		strcpy(dest1, list_nou.list_offer.lista_0ferte[i].destinatie);
		strcpy(dest2, list_nou.list_offer.lista_0ferte[i + 1].destinatie);
		assert(strcmp(dest1, dest2) <= 0);
	}

	list_nou = ordonare_pret_or_dest_cresc_or_descresc(service_test, "destinatie", -1);
	for (int i = 1; i < list_nou.list_offer.lng; i++)
	{
		strcpy(dest1, list_nou.list_offer.lista_0ferte[i].destinatie);
		strcpy(dest2, list_nou.list_offer.lista_0ferte[i + 1].destinatie);
		assert(strcmp(dest1, dest2) >= 0);
	}
}

void test_filtrare_criteriu() {
	Service service_test;
	service_test.list_offer.lng = 0;
	Service* service_aux = &service_test;
	adauga(service_aux, "mare", "Italia", "12/09/2012", 2300);
	adauga(service_aux, "munte", "Spania", "13/08/2021", 8100);
	adauga(service_aux, "city break", "Turcia", "17/05/2021", 3600);
	adauga(service_aux, "mare", "Olanda", "13/11/2015", 7812);
	adauga(service_aux, "munte", "Italia", "17/10/2020", 8100);
	adauga(service_aux, "city break", "Suedia", "21/02/2022", 1238);

	char destinatie[20] = "Italia", tip[20] = "mare";
	int pret = 8100;
	
	Service list_nou = filtrare_criteriu(service_test, "destinatie", &destinatie);
	for (int i = 1; i <= list_nou.list_offer.lng; i++)
		assert(strcmp(list_nou.list_offer.lista_0ferte[i].destinatie, destinatie) == 0);

	list_nou = filtrare_criteriu(service_test, "tip", &tip);
	for (int i = 1; i <= list_nou.list_offer.lng; i++)
		assert(strcmp(list_nou.list_offer.lista_0ferte[i].tip, tip) == 0);

	list_nou = filtrare_criteriu(service_test, "pret", &pret);
	for (int i = 1; i <= list_nou.list_offer.lng; i++)
		assert(list_nou.list_offer.lista_0ferte[i].pret == pret);
}


void testare() {
	test_creeaza();
	test_adauga();
	test_actualizare();
	test_sterge();
	test_ordonare_pret_or_dest_cresc_or_descresc();
	test_filtrare_criteriu();
}