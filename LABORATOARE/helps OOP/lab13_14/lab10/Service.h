//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_SERVICE_H
#define UNTITLED_SERVICE_H
#include <iostream>
#include "Repository.h"
#include "Validator.h"
#include "CosProd.h"
#include "Undo.h"
#include "DTO.h"
#include <functional>
#include <map>
#include "unique_ptr.h"
using std::map;
using std::function;
using std::unique_ptr;

class ProdService {
private:
    ProdRepo& repo;
    ProdValidator& val;

    List currentlist;
    vector<unique_ptr<ActiuneUndo>>UndoActions;
public:
    ProdService(ProdRepo& prodrepo, ProdValidator& val) :repo{ prodrepo }, val{ val }{} ;

    //constructor de copiere
    //punem delete fiindca nu vrem sa se faca nicio copie la Service
    //(in aplicatie avem 1 singur Service)
    ProdService(const ProdService& ot) = delete;

    /*
    Adauga un produs cu nume,tip,producator si pret
    *@param nume: numele produsului care se adauga (string)
    *@param tip: tipul produsului care se adauga (string)
    *@param producator: producatorul produsului care se adauga (string)
    *@param pret: pretul produsului care se adauga (double)
    *
    * @throws:
    *	RepoException daca mai exista produs cu nume si producator dat
    *	ValidationException daca prosusul nu este valid
    */

    void addservice(string nume, string tip, string producator, double pret);

    /*
    cauta un produs cu nume si producator dat
    *@param nume: numele produsului  (string)
    *@param producator: producatorul produsului  (string)
    *return :produsul cautat
    * @throws:
    *	RepoException daca nu exista produs cu nume si producator dat
    *	ValidationException daca prosusul nu este valid
    */
    Produs findservice(string nume, string producator);

    /*
    sterge un produs cu nume,tip,producator si pret
    *@param nume: numele produsului care se sterge (string)
    *@param tip: tipul produsului care se sterge (string)
    *@param producator: producatorul produsului care se sterge (string)
    *@param pret: pretul produsului care se sterge (double)
    *
    * @throws:
    *	RepoException daca nu se gaseste in lista
    *	ValidationException daca prosusul nu este valid
    */
    void dellservice(string nume, string tip, string producator, double pret);

    /*
    Modifica pretul unui produs un produs
    *@param nume: numele produsului care se modifica(string)
    *@param tip: tipul produsului care se modifica (string)
    *@param producator: producatorul produsului care se modifica (string)
    *@param pretnou: pretul nou al produsului
    *
    * @throws:
    *	RepoException daca nu exista produs cu nume si producator dat
    *	ValidationException daca produsul nu este valid(sau pretul nou)
    */
    void modifyservice(string nume, string tip, string producator, double pretnou);

    vector<Produs> filter(function<bool(const Produs&)> fct);

    /*Filtreaza produsele dupa un tip dat
    param tip: tipul dupa care se doreste filtrarea
    return :lista de cu obiecte de tip produs care au tipul dat*/
    vector<Produs> filtreaza_tip(string tip);

    /*Filtreaza produsele dupa un producator dat
    param prod: producatorul dupa care se doreste filtrarea
    return :lista de cu obiecte de tip produs care au producator dat*/
    vector<Produs> filtreaza_prod(string prod);

    /*Filtreaza produsele dupa un nume dat
    param nume: numele dupa care se doreste filtrarea
    return :lista de cu obiecte de tip produs care au numele dat*/
    vector<Produs> filtreaza_nume(string nume);

    /*
     Functie de sortare generala
     functie - functie de comparare, verifica daca are loc relatia intre cele 2 produse
     returneaza o lista sortata dupa criteriu dat ca paramatru
    */
    vector<Produs> sortservice(int reverse,bool (*functie)( Produs&, Produs&));

    /*
    functie de sortare a produselor dupa nume
    param reverse: 0-ordine crescatoare,1-descrescatoare*/
    vector <Produs> sortnume(int reverse);

    /*
    functie de sortare a produselor dupa pret
    param reverse: 0-ordine crescatoare,1-descrescatoare*/
    vector<Produs> sortpret(int reverse);

    vector<Produs> sortNumeTip(int reverse);

    /*
    Returneaza un vector cu toate produsele disponibile

    @return: lista cu toate produsele disponibile (vector cu obiecte de tip produs)
    */
    vector<Produs>& getallproducts() noexcept {
        return this->repo.getallproducts();
    }




    /*
	* Adauga o un produs cu nume si producator dat in sos
	*
	* @param nume: numele produsului care se adauga (string)
	* @param prod: producatorul produsului care se adauga (string)
	*
	* post: produsul este adaugata la lista
	* @throws: RepoException daca nu exista produs cu numele si producatorul dat
	*/
    void addlistsrv(string nume, string produ);
    /*
    * Adauga un numar random de produse in cos
    *
    * @param howMany: cate produse se adauga (int)
    *
    * @return: numarul de produse adaugate in lista
    * post: se adauga un numar random de produse in lista
    */
    int addrandomsrv(int howMany);
    /*
    * Elimina toate produsele din lista
    * post: lista nu contine niciun produs
    */
    void emptylistsrv();
    /*
    * Returneaza un vector cu toate produsele din cos
    */
    const vector<Produs>& getallfromlistsrv();

    map<string, DTO> get_dict();

    void exportsrv(string& fisier);
    void exportqt(string& fisier);
    List& getcos(){
        return this->currentlist;
    }

    void undo();
};

void testeservice();
//void testaddservice();
//void testdellservice();
//void testmodifyservice();
//void testfind_filtreaza_service();






#endif //UNTITLED_SERVICE_H
