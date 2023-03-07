//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_REPOSITORY_H
#define UNTITLED_REPOSITORY_H


#include "Entities.h"
#include "VectorDinamicTemplate.h"
#include <vector>
using std::vector;
class RepoExcep {
private:
    string errormsg;
public:
    RepoExcep(string errormsg) :errormsg{ errormsg } {};
    string getErrorMessage() {
        return this->errormsg;
    }
};

class ProdRepo {
private:
    vector<Produs> allproducts;
public:
    ProdRepo() noexcept = default;
    //constructor de copiere
    //punem delete fiindca nu vrem sa se faca nicio copie la Repository
    ProdRepo(const ProdRepo& ot) = delete;

    virtual /*
    Adauga un produs in lista
    @param p: produsul care se adauga
    @return -
    post: produsul va fi adaugat in lista

    @throws: RepoException daca un produs cu acelasi nume si acelasi producator
             exista deja
    */
    void addrepo(const Produs& p);

    virtual /*sterge  un produs din lista
        @param p : produsul care se sterge
        @return -
        post: produsul va fi sters din lista
        @throws : RepoException daca produsul nu exista in lista
        */
    void dellrepo( const Produs& p);

    virtual /*modifica pretul unui produs  din lista
            @param p : produsul care se modifica
            @return -
            post: pretul produsului va fi modificat
            @throws : RepoException daca produsul nu exista in lista
            */
    void modifyrepo(const Produs& p);

    /*
    Returneaza o lista cu toate produsele
    @return: lista cu produsele
    */
    vector<Produs>& getallproducts() noexcept;

    //int findindex(string nume, string producator);

    /*
    Cauta un produs cu numele si producatorul dat

    @param nume: numele dupa care se cauta
    @param prod: producatorul dupa care se cauta
    @returns: entitatea Produs cu numele si producatorul dat (daca aceasta exista)
    @throws: RepoException daca nu exista produs cu numele si producatorul dat*/
    const Produs& find(string nume, string prod);

    /*
    Verifica daca un produs dat exista in lista

    @param p: produsul care se cauta in lista
    @return: true daca produsul exista, false altfel
    */
    bool exists(const Produs& p);

};

class RepoFile : public ProdRepo {
private:
    string filename;
    void load();
    void write();
public:
    //RepoFile() = delete;
    RepoFile(string fname) :ProdRepo(), filename{ fname } { load(); };
    //RepoFile(const RepoFile& r) = delete;
    //~RepoFile() = default;

    void addrepo(const Produs& m) override ;

    void modifyrepo(const Produs& m) override ;

    void dellrepo(const Produs& m) override ;


};
void testerepo();


#endif //UNTITLED_REPOSITORY_H
