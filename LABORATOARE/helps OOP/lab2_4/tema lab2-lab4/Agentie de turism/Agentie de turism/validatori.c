#include <stdbool.h>
#include <string.h>
#include "operatii.h"

bool valid_cuvant(char cuv[]) {
	for (int i = 0; i < strlen(cuv); i++)
		if (!isalpha(cuv[i]) || cuv[i] != ' ') {
			printf("Un cuvant trebuie sa contina doar litere si spatii!\n");
			return false;
		}
	return true;
}

void completare(char cuv[], int *poz, char data[]) {
	int cont_cuv = 0;

	while (*poz < strlen(data) && data[*poz] != '/') {
		cuv[cont_cuv] = data[*poz];
		poz++;
		cont_cuv++;
	}
	cuv[cont_cuv] = '\0';
}


bool valid_data(char data[]) {
	if (strlen(data) > 10) {
		printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
		return false;
	}

	int i = 0, cont_sep = 0;
	char zi[20], luna[20], an[20];
	while (i < strlen(data)) {
		if (cont_sep == 0) {
			completare(zi, i, data);
			if (i >= strlen(data) || strlen(zi) > 2 || strlen(zi) < 1) {
				printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
				return false;
			}
		}
		else if(cont_sep == 1){
			completare(luna, i, data);
			if (i >= strlen(data) || strlen(luna) > 2 || strlen(luna) < 1) {
				printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
				return false;
			}
		}
		else if(cont_sep == 2){
			completare(an, i, data);
			if (strlen(an) != 4) {
				printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
				return false;
			}
		}
		
		if (i < strlen(data) && data[i] == '/')
			cont_sep++;

		i++;
	}

	for(i = 0; i <strlen(zi); i++)
		if(!isdigit(zi[i])) {
			printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
			return false;
		}
	
	for (i = 0; i < strlen(luna); i++)
		if (!isdigit(zi[i])) {
			printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
			return false;
		}
	
	for (i = 0; i < strlen(an); i++)
		if (!isdigit(zi[i])) {
			printf("Formatul datei nu corespunde cu dd/mm/yyyy.");
			return false;
		}
}

bool valid_poz(Service* service, int poz) {
	if (poz > service->list_offer.lng) {
		printf("Pozitia introdusa este mai mare decat lungimea listei de oferte.");
		return false;
	}
}