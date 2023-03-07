#include <stdio.h>
#include "vector.h"
#include "test_vector.h"
#include "test_service.h"
#include "test_produs.h"

void test_all() {
	//PRODUS
	test_creare_produs();
	test_modificare_pret();
	test_modificare_cantitate();
	test_modificare_pret();
	test_get_id();
	test_get_pret();
	test_get_cantitate();
	test_get_tip();
	test_get_producator();
	test_get_model();
	//END PRODUS

	//VECTOR
	test_creazaVectorDinamic();
	test_distruge();
	test_resize();
	test_get();
	test_get_capacity();
	test_modifica_capacitate();
	test_get_size();
	test_modifica_size();
	test_get_elems();
	test_modifica_elems();
	//END VECTOR

	//SERVICE
	test_adaugare_produs();
	test_get_total_produse();
	test_get_produs();
	test_cautare_produs();
	test_modificare_pret_produs();
	test_modificare_cantitate_produs();
	//END SERVICE
}
int main() {
	test_all();
	return 0;
}