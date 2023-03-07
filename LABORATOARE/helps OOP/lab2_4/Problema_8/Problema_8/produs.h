#pragma once
struct Produs {
	int id,pret,cantitate;
	char tip[20],producator[20],model[20];
};
typedef struct Produs Produs;

Produs creare_produs(int id, int pret, int cantitate, char* tip, char* producator, char* model);
int get_id(Produs pr);
int get_pret(Produs pr);
int get_cantitate(Produs pr);
char* get_tip(Produs pr);
char* get_producator(Produs pr);
char* get_model(Produs pr);
void modificare_pret(Produs* pr, int noul_pret);
void modificare_cantitate(Produs* pr, int noua_cantitate);

