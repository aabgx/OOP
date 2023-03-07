#include "repository.h"
#include "vector_dinamic.h"
#include <assert.h>

bool ActivitateRepository::exists(const Activitate& a) {
	try {
		find(a.get_titlu());
		return true;
	}
	catch (RepoException) {
		return false;
	}}

const Activitate& ActivitateRepository::find(std::string titlu) {
	for (int i = 0;i< lista_activitati.size();i++) {
		if (lista_activitati[i].get_titlu() == titlu)
			return lista_activitati[i];
	}
	throw RepoException("Activitatea cu titlul "+titlu +" nu exista in lista!");}

const VectorDinamic<Activitate>& ActivitateRepository::get_all_activities() {
	return this->lista_activitati;
}

void ActivitateRepository::add(const Activitate& a) {
	if (exists(a)) {
		throw RepoException("Activitatea cu titlul " + a.get_titlu() + "nu exista in lista!");
	}
	this->lista_activitati.push_back(a);
}

void ActivitateRepository::dell(Activitate& a) {
	for (int i = 0; i < this->lista_activitati.size(); i++) {
		if (a.eq(this->lista_activitati[i]) == true) {
			this->lista_activitati.erase(this->lista_activitati.begin() + i);
			break;
		}
	}
}

void ActivitateRepository::modify(Activitate& a) {
	Activitate aux = find(a.get_titlu());
	if (!exists(a)) {
		throw RepoException("Activitatea cu titlul " + aux.get_titlu() + "nu exista in lista!");}
	else {
		for (int i = 0; i < this->lista_activitati.size(); i++) {
			if (a.get_titlu() == lista_activitati[i].get_titlu()) {
				this->lista_activitati[i].set_descriere(a.get_descriere());
				this->lista_activitati[i].set_tip(a.get_tip());
				this->lista_activitati[i].set_durata(a.get_durata());
				break;}}}
}

int ActivitateRepository::get_dim() {
	return this->lista_activitati.size();
}


//Teste 


void test_get_all_activities() {

	ActivitateRepository test_repo;
	VectorDinamic<Activitate> lista = test_repo.get_all_activities();
	assert(lista.size() == 0);
}

void test_find_repo() {
	ActivitateRepository test_repo;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	test_repo.add(activity1);
	test_repo.add(activity2);

	Activitate activity3{ "Stand-up Dan Badea", "Casa de cultura", "Stand-ul comedy", 3 };
	assert(test_repo.exists(activity1));
	assert(!test_repo.exists(activity3));

	auto activitate_gasita = test_repo.find("Zilele orasului");
	assert(activitate_gasita.get_titlu() == "Zilele orasului");
	assert(activitate_gasita.get_descriere() == "In centrul orasului");
	assert(activitate_gasita.get_tip() == "Concert");
	assert(activitate_gasita.get_durata() == 72);

	try {
		test_repo.find("Stand-up");
		//assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		test_repo.find("Stand");
		//assert(false);
	}
	catch (RepoException& ve) {
		std::cout << ve.get_errors();
		assert(ve.get_errors() == "");
	}
}


void test_add_repo() {
	ActivitateRepository test_repo;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	test_repo.add(activity1);
	assert(test_repo.get_dim() == 1);

	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	test_repo.add(activity2);
	assert(test_repo.get_dim() == 2);

	Activitate activity3{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	try {
		test_repo.add(activity3);
		//assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}

void test_dell_repo() {

	ActivitateRepository repo;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	repo.add(activity1);
	repo.add(activity2);

	assert(repo.get_dim() == 2);
	VectorDinamic<Activitate> lista = repo.get_all_activities();
	assert(lista.size() == 2);
	assert(activity1.eq(lista[0]) == true);
	assert(activity2.eq(lista[1]) == true);

	repo.dell(activity2);
	assert(repo.get_dim() == 1);
	lista = repo.get_all_activities();
	assert(activity1.eq(lista[0]) == true);

	repo.dell(activity1);
	assert(repo.get_dim() == 0);
}

void test_modify_repo() {
	ActivitateRepository test_repo;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	test_repo.add(activity1);
	test_repo.add(activity2);

	Activitate activity3{ "Zilele orasului", "Casa de cultura", "Stand-ul comedy", 3 };
	test_repo.modify(activity3);
	VectorDinamic <Activitate> lista = test_repo.get_all_activities();
	assert(lista[0].get_titlu() == "Zilele orasului");
	assert(lista[0].get_descriere() == "Casa de cultura");
	assert(lista[0].get_tip() == "Stand-ul comedy");
	assert(lista[0].get_durata() == 3);

	Activitate activity4{ "Zilele", "Casa de cultura", "Stand-ul comedy", 3 };
	try {
		test_repo.modify(activity4);
		//assert(false);
	}
	catch (RepoException&) {
		assert(true);}

	Activitate a{ "Zile", "In centrul orasului", "Concert", 72 };
	try {
		test_repo.modify(a);
		//assert(false);
	}
	catch (RepoException& ve) {
		std::cout << ve.get_errors();
		assert(ve.get_errors() == "");}
}

void test_resize() {
	VectorDinamic<int> v;
	for (int i = 0; i <= 200; i++)
		v.push_back(2 * i);
	for (int i = 0; i <= 200; i++)
		assert(v[i] == 2 * i);

	assert(v.size() == 201);

}

void teste_repo() {
	test_get_all_activities();
	test_add_repo();
	test_find_repo();
	test_dell_repo();
	test_modify_repo();
	test_resize();
}
