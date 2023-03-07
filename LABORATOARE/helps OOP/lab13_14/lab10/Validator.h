//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_VALIDATOR_H
#define UNTITLED_VALIDATOR_H



#include "Entities.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
class ValidationExcep {
    vector<string> errormsg;
public:
    ValidationExcep(vector<string> errorMessages) :errormsg{ errorMessages } {};

    string getErrorMessages() {
        string fullMsg = "";
        for (const string &e : errormsg) {
            fullMsg += e + "\n";
        }
        return fullMsg;
    }
};
/*
Clasa pentru validarea produselor
Un produs este valid daca:
	are tnumele format din mai mult de 2 caractere
	are tip format din mai mult de 2 caractere
	are producator format din mai mult de 2 caractere
	pretul produsului >0
*/
class ProdValidator {

public:
    void valideaza(const Produs& p) {
        vector<string> errors;
        if (p.getNume().length() < 2)
            errors.push_back("Numele trebuie sa aiba cel putin 2 caractere.");
        if (p.getProd().length() < 2)
            errors.push_back("Producatorul trebuie sa aiba cel putin 2 caractere.");
        if (p.getPret() < 0)
            errors.push_back("Pretul trebuie mai mare decat 0.");
        if (p.getTip().length() < 2)
            errors.push_back("Tipul trebuie sa aiba cel putin 2 caractere.");

        if (errors.size() > 0)
            throw ValidationExcep(errors);
    }
};



#endif //UNTITLED_VALIDATOR_H
