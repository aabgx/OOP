//
// Created by Laura on 4/13/2022.
//

#ifndef UNTITLED_COSPROD_H
#define UNTITLED_COSPROD_H
#include "Observer.h"
#include "Entities.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

using std::vector;
class List:public Observable {
private:
    vector<Produs> listproducts;
public:
    List()=default;
    /*
    * Adauga un produs in cos
    * @param s: produsul care se adauga
    *
    * post: mprodusul va fi adaugat la lista
    */
    void addlist(const Produs& s);
    /*
    * Elimina toate produsele  din cos
    * post: lista este goala
    */
    void emptylist();
    /*
    * Adauga un numar random de produse in cos
    *
    * @param originalprod: produsele din care se alege
    * @param howMany: cate produse se adauga (int)
    *
    * post: produsele sunt adaugate in playlist-ul curent
    */
    void addrandomlist(vector<Produs> originalprod, size_t howMany);
    /*
    * Returneaza un vector care contine toate produsele din cos
    */
    const vector<Produs>& getallfromlist();

    //Face export la produsele din cos intr-un fiser dat
    void export_fis(string& fisier);

};
void testeCos();

#endif //UNTITLED_COSPROD_H
