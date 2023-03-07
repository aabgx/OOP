//
// Created by Laura on 4/8/2022.
//

#include "Entities.h"
#include <assert.h>


string Produs::getNume() const {
    return this->nume;
}
string Produs::getTip() const {
    return this->tip;
}
string Produs::getProd() const {
    return this->producator;
}
double Produs::getPret() const noexcept {
    return this->pret;
}
void Produs::setPret(double pretnou) noexcept {
    this->pret = pretnou;
}

bool cmpnume(Produs& p1,  Produs& p2) {
    return p1.getNume() < p2.getNume();
}

bool cmppret(Produs& p1,  Produs& p2) noexcept {
    return p1.getPret() < p2.getPret();
}

bool cmptip(Produs& p1,  Produs& p2) {
    return p1.getTip() < p2.getTip();
}

bool cmpNumeTip(  Produs& m1,  Produs& m2) {
    if (m1.getNume() == m2.getNume())
        return m1.getTip() < m2.getTip();
    else
        return m1.getNume() < m2.getNume();
}

void testeEnt()
{
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    assert(prod1.getNume() == "aaa");
    assert(prod1.getTip() == "bbb");
    assert(prod1.getProd() == "ccc");
    assert(prod1.getPret() == 38.5);

    prod1.setPret(40);
    assert(prod1.getPret() == 40);
}

void testecmp()
{
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    Produs prod2{ "acr","ngv","gfg",56 };
    Produs prod3{"aaa","vfc","hgsa",53.5};
    const int  var1 = cmpnume(prod1, prod2);
    assert(var1== 1);
    const int var2 = cmppret(prod1, prod2);
    assert( var2== 1);
    const int var3 = cmptip(prod1, prod2);
    assert(var3 == 1);
    const int var4= cmpNumeTip(prod1,prod3);
    assert(var4==1);
    const int var5= cmpNumeTip(prod1,prod2);
    assert(var5==1);

}
