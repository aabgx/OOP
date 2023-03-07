#pragma once
#include "repository.h"
#include "validators.h"
#include <functional>
using std::function;

class SrvException {
private:
	std::string errors;
public:
	SrvException(std::string) :errors{ errors } {};
	std::string get_errors() {
		return this->errors;
	}
};


class ActivitateStore {
private: 
	ActivitateRepository& repo;
	ActivitateValidator& val;

	VectorDinamic<Activitate> filter(function<bool(const Activitate&)> fct);

	VectorDinamic<Activitate> sortGenerala(bool(*maiMicF)(const Activitate&, const Activitate&));

public:
	ActivitateStore(ActivitateRepository& activitate_repo, ActivitateValidator& val) : repo{ activitate_repo }, val{ val }{};

	ActivitateStore(const ActivitateStore& ot) = delete;
	
	void add_activity(std::string titlu, std::string descriere, std::string tip, double durata);

	//int find_poz(const Activitate& a);

	void delete_activity(std::string titlu);

	void modify_activity(std::string titlu, std::string descriere, std::string tip, double durata);

	Activitate find_activity(std::string titlu);

	VectorDinamic<Activitate> filtrareDescriere(std::string gen);

	VectorDinamic<Activitate> filtrareTip(std::string tip);

	VectorDinamic<Activitate> sortareTitlu();

	VectorDinamic<Activitate> sortareDescriere();

	VectorDinamic<Activitate> sortareTipDurata();

	const VectorDinamic<Activitate>& get_all_activities() {
		return this->repo.get_all_activities();
	}
};

void teste_srv();