//
// Created by Laura on 4/13/2022.
//

#include "CosProd.h"
#include <fstream>
#include <assert.h>
#include <string>
using std::shuffle;
using std:: ofstream;

void List::addlist(const Produs& s) {
    this->listproducts.push_back(s);
    notify();
}
void List::emptylist() {
    this->listproducts.clear();
    notify();
}

void List::addrandomlist(vector<Produs> originalprod, size_t howMany) {
    shuffle(originalprod.begin(), originalprod.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
    while (listproducts.size() < howMany && originalprod.size() > 0) {
        listproducts.push_back(originalprod.back());
        originalprod.pop_back();
    }
    notify();
}
const vector<Produs>& List::getallfromlist() {
    return this->listproducts;
}

void List::export_fis(string& fisier) {
    fisier += ".htm";
    ofstream fout(fisier);
    for (auto& prod : listproducts) {
        fout  <<prod.getNume() <<" "<<prod.getTip()<<" "<<prod.getProd()<<" "<<prod.getPret()<<'\n';
    }
}

void testeCos(){
    List teste;
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    Produs prod2{ "lll","gfhc","ooo",55 };
    teste.addlist(prod1);
    teste.addlist(prod2);
    assert(teste.getallfromlist().size()==2);
    teste.emptylist();
    assert(teste.getallfromlist().size()==0);

}
