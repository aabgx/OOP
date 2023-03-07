#pragma once
#include "service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
using std::sort;

void ActivitateStore::add_activity(std::string titlu, std::string descriere, std::string tip, double durata) {
	Activitate a{ titlu, descriere, tip, durata };
	val.valideaza(a);
	repo.add(a);
}

//int ActivitateStore::find_poz(const Activitate& a) {
//	const VectorDinamic<Activitate>& activitati = repo.get_all_activities();
//	for (int i = 0; i < activitati.size(); i++) {
//		if (activitati[i].get_titlu() == a.get_titlu())
//			return i;
//	}
//	return -1;
//}

void ActivitateStore::delete_activity(std::string titlu) {
	Activitate a = repo.find(titlu);
	repo.dell(a);
}

void ActivitateStore::modify_activity(std::string titlu, std::string descriere, std::string tip, double durata) {
	Activitate a{ titlu, descriere, tip, durata };
	val.valideaza(a);
	repo.modify(a);
}

Activitate ActivitateStore::find_activity(std::string titlu) {
	Activitate a = repo.find(titlu);
	return a;
}

VectorDinamic<Activitate> ActivitateStore::filter(function<bool(const Activitate&)> fct) {
	VectorDinamic<Activitate> filteredActivities;
	VectorDinamic<Activitate> lst = repo.get_all_activities();
	for (int i = 0;i< repo.get_dim();i++) {
		if (fct(lst[i])) {
			filteredActivities.push_back(lst[i]);
		}
	}
	return filteredActivities;
}

VectorDinamic<Activitate> ActivitateStore::filtrareDescriere(std::string descriere) {
	return filter([descriere](const Activitate& a) {
		return a.get_descriere() == descriere;
		});
}

VectorDinamic<Activitate> ActivitateStore::filtrareTip(std::string tip) {
	return filter([tip](const Activitate& a) {
		return a.get_tip() == tip;
		});
}

VectorDinamic<Activitate> ActivitateStore::sortGenerala(bool(*maiMicF)(const Activitate&, const Activitate&)) {
	VectorDinamic<Activitate> v{ repo.get_all_activities() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				Activitate aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

VectorDinamic<Activitate> ActivitateStore::sortareTitlu() {
	/*auto sortedCopy = repo.get_all_activities();
	sort(sortedCopy.begin(), sortedCopy.end(), cmpTitlu);*/
	return sortGenerala(cmpTitlu);
}

VectorDinamic<Activitate> ActivitateStore::sortareDescriere() {
	//auto sortedCopy = repo.get_all_activities();
	//sort(sortedCopy.begin(), sortedCopy.end(), cmpDescriere);
	return sortGenerala(cmpDescriere);
}

VectorDinamic<Activitate> ActivitateStore::sortareTipDurata() {
	return sortGenerala(cmpTipDurata);
}


//Teste

void test_add_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	ActivitateStore test_srv{ test_repo, test_val };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);
	VectorDinamic<Activitate>v = test_srv.get_all_activities();
	assert(v.size() == 2);

	try {
		test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
		//assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("", "In centrul orasului", "Concert", 72);
		//assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.get_errors();
		assert(ve.get_errors() == "Titlul trebuie sa aiba cel putin 2 caractere!\n");
	}

	try {
		test_srv.add_activity("Zilele orasului", "", "Concert", 72);
		//assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("Zilele orasului", "In centru", "", 72);
		//assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("Zilele orasului", "In centru", "Concert", 72.80);
		//assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}
}

void test_dell_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	ActivitateStore test_srv{ test_repo, test_val };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	assert(test_repo.get_dim() == 2);
	test_srv.delete_activity("Zilele orasului");
	assert(test_repo.get_dim() == 1);

	test_srv.delete_activity("Stand-up Micutzu");
	assert(test_repo.get_dim() == 0);
}

void test_modify_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	ActivitateStore test_srv{ test_repo, test_val };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	Activitate a1 = test_repo.find("Zilele orasului");
	assert(a1.get_descriere() == "In centrul orasului");
	assert(a1.get_durata() == 72);

	test_srv.modify_activity("Zilele orasului", "In parc", "Muzica", 24);
	Activitate a1_modificat = test_repo.find("Zilele orasului");
	assert(a1_modificat.get_descriere() == "In parc");
	assert(a1_modificat.get_durata() == 24);

}

void test_find_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	ActivitateStore test_srv{ test_repo, test_val };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	Activitate a = test_srv.find_activity("Zilele orasului");
	assert(a.get_titlu() == "Zilele orasului");
	assert(a.get_descriere() == "In centrul orasului");
	assert(a.get_tip() == "Concert");
	assert(a.get_durata() == 72);
}


void test_filter_srv() {
	ActivitateRepository testRepo;
	ActivitateValidator testVal;
	ActivitateStore testService{ testRepo,testVal };

	testService.add_activity("titlu1", "descriere1", "tip1", 3.42);
	testService.add_activity("titlu2", "descriere2", "tip1", 8.31);
	testService.add_activity("titlu3", "descriere2", "tip3", 5.27);
	testService.add_activity("titlu4", "descriere4", "tip4", 4.52);
	testService.add_activity("titlu5", "descriere5", "tip5", 3.45);
	testService.add_activity("titlu6", "descriere6", "tip6", 3.2);

	VectorDinamic<Activitate> activitati1 = testService.filtrareDescriere("descriere2");
	assert(activitati1.size() == 2);
	VectorDinamic<Activitate> activitati2 = testService.filtrareDescriere("descriere0");
	assert(activitati2.size() == 0);


	VectorDinamic<Activitate> activitati3 = testService.filtrareTip("tip1");
	assert(activitati3.size() == 2);
	VectorDinamic<Activitate> activitati4 = testService.filtrareTip("tip4");
	assert(activitati4.size() == 1);

}

void test_sort_srv() {
	ActivitateRepository testRepo;
	ActivitateValidator testVal;
	ActivitateStore testService{ testRepo,testVal };

	testService.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	testService.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-up comedy", 3);
	testService.add_activity("Teambuilding", "La cabana", "Teambuilding", 72);
	testService.add_activity("Titlu4", "Descriere4", "Teambuilding", 4.52);

	VectorDinamic<Activitate> sortedByTitlu = testService.sortareTitlu();
	assert(sortedByTitlu[0].get_titlu() == "Stand-up Micutzu");
	assert(sortedByTitlu[1].get_titlu() == "Teambuilding");
	assert(sortedByTitlu[2].get_titlu() == "Titlu4");
	assert(sortedByTitlu[3].get_titlu() == "Zilele orasului");

	VectorDinamic<Activitate> sortedByDescriere = testService.sortareDescriere();
	assert(sortedByDescriere[0].get_descriere() == "Casa de cultura");
	assert(sortedByDescriere[2].get_descriere() == "In centrul orasului");

	VectorDinamic<Activitate> sortedByTipDurata = testService.sortareTipDurata();
	assert(sortedByTipDurata[0].get_tip() == "Concert");
	assert(sortedByTipDurata[0].get_durata() == 72);
	assert(sortedByTipDurata[2].get_tip() == "Teambuilding");
	assert(sortedByTipDurata[2].get_durata() == 4.52);
	assert(sortedByTipDurata[3].get_tip() == "Teambuilding");
	assert(sortedByTipDurata[3].get_durata() == 72);
}

void teste_srv() {
	test_add_srv();
	test_dell_srv();
	test_modify_srv();
	test_find_srv();
	test_filter_srv();
	test_sort_srv();
}