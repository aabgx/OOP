//
// Created by Laura on 4/8/2022.
//

#include "Repository.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "VectorDinamicTemplate.h"
#include <assert.h>
using std::ifstream;
using std::stringstream;
using std::ofstream;

bool ProdRepo::exists(const Produs& p) {
    try {
        find(p.getNume(), p.getProd());
        return true;
    }
    catch (RepoExcep) {
        return false;
    }
}
const Produs& ProdRepo::find(string nume, string producator) {
    //for (const Produs& p : this->allproducts) {
        //if (p.getNume() == nume && p.getProd() == producator) {
            //return p;
        //}
    //}
    vector<Produs>:: iterator f = std::find_if(this->allproducts.begin(), this->allproducts.end(),
                                            [=](const Produs& s) {
                                                return s.getNume() == nume && s.getProd() == producator;
                                            });

    if (f != this->allproducts.end())
        return (*f);
    else
        throw RepoExcep("Produsul pe care ati incercat sa il cautati nu exista.\n");
}

//int ProdRepo::findindex(string nume, string producator) {
   // for (int i = 0;i< this->allproducts.size(); i++ ){
      //  if (this->allproducts.at(i).getNume() == nume && this->allproducts.at(i).getProd() == producator) {
           // return i;
       // }
    //}
   // return -1;
//}



void ProdRepo::addrepo(const Produs& p) {
    if (exists(p))
    {
        throw RepoExcep("Produsul exista deja in magazin\n.");
    }
    allproducts.push_back(p);
}

void ProdRepo::dellrepo(const Produs& p) {
    if (!exists(p))
    {
        throw RepoExcep("Produsul pe care doriti sa il stergeti nu exista in magazin.\n");
    }
    int i = 0;
    for (auto& prod : this->allproducts) {
        if (prod.getNume() == p.getNume() && prod.getProd() == p.getProd() && prod.getTip() == p.getTip() &&
            prod.getPret() == p.getPret()) {
            allproducts.erase(this->allproducts.begin() + i);
        }
        i++;
    }
    //const int index = findindex(p.getNume(), p.getProd());
    //if (index != -1)
    //{
       // this->allproducts.remove(index);
    //}
}

void ProdRepo::modifyrepo(const Produs& p) {
    if (!exists(p))
    {
        throw RepoExcep("Produsul pe care doriti sa il modificati nu exista in magazin.\n");
    }
    int i = 0;
    for (auto& prod : this->allproducts) {
        if (prod.getNume() == p.getNume() && prod.getProd() == p.getProd() && prod.getTip() == p.getTip()) {
            prod.setPret(p.getPret());
            //prod = p;
        }
        i++;
    }
}

vector<Produs>& ProdRepo::getallproducts() noexcept {
    return this->allproducts;
}




void RepoFile::load() {
    ifstream prodFile(this->filename);
    if (!prodFile.is_open()) {
        throw RepoExcep("Cannot read from file " + filename);
    }
    string line;
    while (getline(prodFile, line))
    {
        string nume,tip,producator;
        double pret;

        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        while (getline(linestream, current_item, ','))
        {
            if (item_no == 0)  nume= current_item;
            if (item_no == 1) tip = current_item;
            if (item_no == 2) producator = current_item;
            if (item_no == 3) pret = std::stod(current_item);
            item_no++;
        }
        Produs p{ nume,tip,producator,pret };
        ProdRepo::addrepo(p);


    }
    prodFile.close();
}

void RepoFile::write() {
    ofstream prodOutput(this->filename);
    if (!prodOutput.is_open())
        throw RepoExcep("Cannot write to file " + filename);
    for (auto& prod : getallproducts()) {
        prodOutput << prod.getNume() << "," << prod.getTip() << ",";
        prodOutput << prod.getProd() << "," << prod.getPret() << endl;
    }
    prodOutput.close();
}

void RepoFile::addrepo(const Produs& s){
    ProdRepo::addrepo(s);
    write();
}

void RepoFile::modifyrepo(const Produs& s)
{
    ProdRepo::modifyrepo(s);
    write();

}

void RepoFile::dellrepo(const Produs& p){
    ProdRepo::dellrepo(p);
    write();
}



void testaddrepo() {
    ProdRepo testrepo;
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    testrepo.addrepo(prod1);
    assert(testrepo.getallproducts().size() == 1);

    Produs prod2{ "aaa","gfhc","ccc",55};
    try {
        testrepo.addrepo(prod2);
        assert(false);
    }
    catch (RepoExcep) {
        assert(true);
    }
}
void testdell() {
    ProdRepo testrepo;
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    testrepo.addrepo(prod1);
    assert(testrepo.getallproducts().size() == 1);

    Produs prod2{ "abva","gfhc","ccc",55 };
    testrepo.addrepo(prod2);
    assert(testrepo.getallproducts().size() == 2);
    testrepo.dellrepo(prod2);
    assert(testrepo.getallproducts().size() == 1);
    try {
        testrepo.dellrepo(prod2);
        assert(false);
    }
    catch (RepoExcep) {
        assert(true);
    }
}

void testfind()
{
    ProdRepo testrepo;
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    Produs prod2{ "lll","gfhc","ooo",55 };
    testrepo.addrepo(prod1);
    assert(testrepo.exists(prod1));
    assert(!testrepo.exists(prod2));
    testrepo.addrepo(prod2);
    auto foundprod = testrepo.find("lll", "ooo");
    assert(foundprod.getPret() == 55);
    assert(foundprod.getNume() == "lll");
    //auto found=testrepo.find("ava","ajh");

    try {
        testrepo.find("jhb", "ccc");
        assert(false);
    }
    catch (RepoExcep& ve) {
        assert(ve.getErrorMessage() == "Produsul pe care ati incercat sa il cautati nu exista.\n");
    }

}
void testmodify()
{
    ProdRepo testrepo;
    Produs prod1{ "aaa","bbb","ccc",38.5 };
    testrepo.addrepo(prod1);
    assert(testrepo.getallproducts().size() == 1);
    Produs prod2{ "aaa","bbb","ccc",46 };
    Produs prod3{ "aaa","bbb","jjj",78 };
    testrepo.modifyrepo(prod2);
    assert(testrepo.find("aaa","ccc").getPret() == 46);
    try {
        testrepo.modifyrepo(prod3);
        assert(false);
    }
    catch (RepoExcep& ve) {
        assert(ve.getErrorMessage() == "Produsul pe care doriti sa il modificati nu exista in magazin.\n");
    }

}



void testerepo() {
    testaddrepo();
    testfind();
    testdell();
    testmodify();
}
