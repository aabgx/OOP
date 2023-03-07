//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_ENTITIES_H
#define UNTITLED_ENTITIES_H

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Produs {
private:
    string nume;
    string tip;
    string producator;
    double pret;
public:
    Produs() = default;
    Produs(string nume, string tip, string producator, double pret) : nume{ nume }, tip{ tip }, producator{ producator }, pret{ pret }{};
    Produs(const Produs& ot): nume{ ot.nume},tip{ot.tip},producator{ot.producator},pret{ot.pret}
    { //this->nume=ot.nume;
        //this->tip=ot.tip;
        //this->producator=ot.producator;
        //this->pret=ot.pret;
        cout << "[Produs] Copy constructor called." << endl;
    }
    Produs& operator=(const Produs& ot)=default;
    string getNume() const;
    string getTip() const;
    string getProd() const;
    double getPret() const noexcept;

    void setPret(double pretnou) noexcept;

};

/*functie de comparare a numelor a 2 produse
p1,p2-produsele de comparat valide
post: de tip bool true/false
*/
bool cmpnume(  Produs& p1,  Produs& p2);

/*functie de comparare a preturilor a 2 produse
p1,p2-produsele de comparat valide
post: de tip bool true/false
*/
bool cmppret( Produs& p1,  Produs& p2) noexcept;

/*functie de comparare a tipului a 2 produse
p1,p2-produsele de comparat valide
post: de tip bool true/false
*/
bool cmptip( Produs& p1,  Produs& p2);

bool cmpNumeTip(  Produs& m1,  Produs& m2);


void testeEnt();
void testecmp();

#endif //UNTITLED_ENTITIES_H
