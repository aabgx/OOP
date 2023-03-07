//
// Created by Laura on 4/8/2022.
//

#include "Service.h"
#include "Validator.h"
//#include <gsl/gsl_util>
#include <algorithm>
#include <functional>
#include <algorithm>
#include <fstream>
//#include <bits/stdc++.h>
#include "DTO.h"
#include <assert.h>
using std::move;
using std::make_unique;

void ProdService::addservice(string nume, string tip, string producator, double pret) {
    Produs p1{ nume,tip,producator,pret };
    val.valideaza(p1);
    repo.addrepo(p1);
    UndoActions.push_back( make_unique<AddUndo>(repo, p1) );
}

void ProdService::dellservice(string nume, string tip, string producator, double pret) {
    Produs p1{ nume,tip,producator,pret };
    val.valideaza(p1);
    repo.dellrepo(p1);
    UndoActions.push_back( make_unique<DelUndo>(repo, p1) );
}

void ProdService::modifyservice(string nume, string tip, string producator, double pretnou) {
    Produs p1{ nume,tip,producator,pretnou};
    val.valideaza(p1);
    Produs p2=repo.find(p1.getNume(),p1.getProd());
    repo.modifyrepo(p1);
    UndoActions.push_back( make_unique<UpdUndo>(repo, p2) );
}

Produs ProdService::findservice(string nume, string producator) {
    return repo.find(nume, producator);
}

/*vector<Produs> ProdService::filter(function<bool(const Produs&)> fct){
    vector<Produs> filteredPr;
    for (const auto& prod : repo.getallproducts()) {
        if (fct(prod)) {
            filteredPr.push_back(prod);
        }
    }
    return filteredPr;
}*/

vector<Produs> ProdService::filtreaza_tip(string tip) {
    //return filter([tip](const Produs& prod) {
        //return prod.getTip() == tip;
    //});
    const vector<Produs>& allprod = getallproducts();
    vector<Produs> filteredPr;
    std::copy_if(allprod.begin(), allprod.end(), back_inserter(filteredPr),
                 [tip](const Produs& m) {
                     return m.getTip() == tip;
                 });
    return filteredPr;
}

vector<Produs> ProdService::filtreaza_nume(string nume) {
    //return filter([nume](const Produs& prod) {
       // return prod.getNume() == nume;
    //});
    const vector<Produs>& allprod = getallproducts();
    vector<Produs> filteredPr;
    std::copy_if(allprod.begin(), allprod.end(), back_inserter(filteredPr),
                 [nume](const Produs& m) {
                     return m.getNume() == nume;
                 });
    return filteredPr;
}

vector<Produs> ProdService::filtreaza_prod(string produ) {
    //return filter([produ](const Produs& prod) {
        //return prod.getProd() == produ;
    //});
    const vector<Produs>& allprod = getallproducts();
    vector<Produs> filteredPr;
    std::copy_if(allprod.begin(), allprod.end(), back_inserter(filteredPr),
                 [produ](const Produs& m) {
                     return m.getProd() ==produ ;
                 });
    return filteredPr;
}


/*vector<Produs> ProdService::sortservice(int reverse, bool(*functie)(Produs&, Produs&)) {
    vector<Produs> v{ repo.getallproducts() };//fac o copie

    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (reverse == 0) {
                //crescator
                if (!functie(v[i],v[j])){
                    //interschimbam
                    Produs aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
            else
            {
                //descrescator
                if (functie(v[i], v[j])) {
                    //interschimbam
                    Produs aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
        }
    }
    return v;
}*/

vector <Produs> ProdService::sortnume(int reverse) {
    vector<Produs> sortedCopy{ repo.getallproducts() };
    sort(sortedCopy.begin(), sortedCopy.end(), cmpnume);
    if(reverse==1) {
        std::reverse(sortedCopy.begin(),sortedCopy.end());
    }
    return sortedCopy;
    //return sortservice(reverse,cmpnume);
}

vector <Produs> ProdService::sortpret(int reverse) {
    vector<Produs> sortedCopy{ repo.getallproducts() };
    sort(sortedCopy.begin(), sortedCopy.end(), cmppret);
    if(reverse==1) {
        std::reverse(sortedCopy.begin(),sortedCopy.end());
    }
    return sortedCopy;
    //return sortservice(reverse, cmppret);
}

vector <Produs> ProdService::sortNumeTip(int reverse) {
    vector<Produs> sortedCopy{ repo.getallproducts() };
    sort(sortedCopy.begin(), sortedCopy.end(), cmpNumeTip);
    if(reverse==1) {
        std::reverse(sortedCopy.begin(),sortedCopy.end());
    }
    return sortedCopy;
    //return sortservice(reverse, cmpNumeTip);
}

void ProdService::addlistsrv(string nume, string prod) {

    const auto& produs = repo.find(nume, prod);
    currentlist.addlist(produs);

}
int ProdService::addrandomsrv(int howMany) {
    currentlist.addrandomlist(this->getallproducts(), howMany);
    return currentlist.getallfromlist().size();
}
void ProdService::emptylistsrv() {
    currentlist.emptylist();
}
const vector<Produs>& ProdService::getallfromlistsrv() {
    return currentlist.getallfromlist();
}


map<string, DTO> ProdService::get_dict() {
    map<string, DTO> dict;
    auto& products = repo.getallproducts();
    for (const auto& prod : products) {
        auto it = dict.find(prod.getTip());
        if (it == dict.end()) {
            dict[prod.getTip()] = DTO{ prod.getTip() };
        }
        else {
            it->second.incr();
        }
    }
    return dict;
}

void ProdService::exportsrv(string& fisier) {
    currentlist.export_fis(fisier);
}

void ProdService::exportqt(string& fisier) {
    const vector<Produs>& allprod = getallproducts();
    fisier += ".htm";
    std::ofstream fout(fisier);
    for (auto& prod : allprod) {
        fout  <<prod.getNume() <<" "<<prod.getTip()<<" "<<prod.getProd()<<" "<<prod.getPret()<<'\n';
    }
}

void ProdService::undo() {
    if (UndoActions.size() < 1) {
        throw UndoException("Nu se poate da undo!\n");
    }
    UndoActions.back()->doUndo();
    UndoActions.pop_back();
}

void testsortareservice() {
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("lll", "gfhc", "ooo", 55);
    testService.addservice("lll", "ghv", "hgfcv", 80);
    testService.addservice("gcv", "gvhb", "ggg", 80);
    testService.addservice("gv", "gb", "ggg", 85);

    auto firstP = testService.sortnume(0)[0];
    assert(firstP.getTip() == "bbb");

    firstP = testService.sortnume(1)[2];
    assert(firstP.getTip() == "gb");

    firstP = testService.sortpret(1)[0];
    //assert(firstP.getTip() == "gb");

    firstP = testService.sortpret(0)[0];
    assert(firstP.getNume() == "aaa");

    firstP = testService.sortNumeTip(0)[0];
    assert(firstP.getNume() == "aaa");



}
void testfind_filtreaza_service()
{
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("lll", "gfhc", "ooo", 55);
    testService.addservice("lll", "ghv", "hgfcv", 80);
    testService.addservice("gcv", "gvhb", "ggg", 80);
    testService.addservice("gv", "gb", "ggg", 85);
    assert(testService.getallproducts().size() == 5);
    try {
        testService.findservice("aaa", "ccc");
        assert(true);
    }
    catch (RepoExcep&)
    {
        assert(false);
    }
    assert((testService.filtreaza_tip("bbb")).size() == 1);
    assert((testService.filtreaza_nume("lll")).size() == 2);
    assert((testService.filtreaza_prod("ggg")).size() == 2);




}
void testmodifyservice() {
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    //testService.addservice("lll", "gfhc", "ooo", 55);
    assert(testService.getallproducts().size() == 1);
    try {
        testService.modifyservice("aaa", "bbb", "ccc", 45);
        assert(true);
    }
    catch (RepoExcep&) {
        assert(false);
    }



}
void testdellservice() {
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("lll", "gfhc", "ooo", 55);

    assert(testService.getallproducts().size() == 2);
    testService.dellservice("aaa", "bbb", "ccc", 38.5);
    assert(testService.getallproducts().size() == 1);
    try {
        testService.dellservice("aaa", "bbb", "ccc", 38.5);
        assert(false);
    }
    catch (RepoExcep&) {
        assert(true);
    }
}



void testaddservice() {
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("lll", "gfhc", "ooo", 55);

    assert(testService.getallproducts().size() == 2);
    try {
        testService.addservice("aaa", "bbb", "ccc", 38.5);
        assert(false);
    }
    catch (RepoExcep&) {
        assert(true);
    }

    try {
        testService.addservice("nsa", "mna", "akn", 48.8);
        assert(true);
    }
    catch (ValidationExcep&) {
        assert(false);
    }

    try {
        testService.addservice("nsa", "mna", "akn", -5);
        assert(false);
    }
    catch (ValidationExcep&) {
        assert(true);
    }

    try {
        testService.addservice("nsa", "mna", "", 48.8);
        assert(false);
    }
    catch (ValidationExcep&) {
        assert(true);
    }


    try {
        testService.addservice("", "hgcv", "hjvb", 13.9);
        assert(false);
    }
    catch (ValidationExcep& ve) {
        assert(ve.getErrorMessages() == "Numele trebuie sa aiba cel putin 2 caractere.\n");
    }


    try {
        testService.addservice("jbdas", "", "jkb", 7.6);
        assert(false);
    }
    catch (ValidationExcep&) {
        assert(true);
    }


}

void testCossrv() {
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };

    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("lll", "gfhc", "ooo", 55);
    testService.addservice("aba", "kjs", "ccc", 35);
    testService.addservice("lddl", "kjs", "ooo", 50);

    testService.addrandomsrv(4);
    assert(testService.getallfromlistsrv().size() == 4);
    testService.emptylistsrv();
    assert(testService.getallfromlistsrv().size() == 0);

    testService.addrandomsrv(20);
    //putem adauga doar 4 produse (fara sa se repete)
    assert(testService.getallfromlistsrv().size() == 4);

    testService.emptylistsrv();
    testService.addlistsrv("aaa", "ccc");
    assert(testService.getallfromlistsrv().size() == 1);

    try {
        testService.addlistsrv("aa", "scs");
        assert(false);
    }
    catch (RepoExcep&) {
        assert(true);
    }


}

void testDTOsrv()
{
    ProdRepo testRepo;
    ProdValidator testVal;
    ProdService testService{ testRepo,testVal };
    testService.addservice("aaa", "bbb", "ccc", 38.5);
    testService.addservice("aba", "bbb", "ccc", 35);
    auto dict=testService.get_dict();
    assert(dict.find("bbb")->second.get_nr()==2);
    assert(dict.find("bbb")->second.getTip()=="bbb");
}

void testeservice() {
    testaddservice();
    testdellservice();
    testmodifyservice();
    testfind_filtreaza_service();
    testsortareservice();
    testCossrv();
    testDTOsrv();
}
