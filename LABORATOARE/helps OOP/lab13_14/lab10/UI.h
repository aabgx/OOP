//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_UI_H
#define UNTITLED_UI_H
#include "Service.h"
class ConsoleUI {
private:
    ProdService& srv;
public:
    ConsoleUI(ProdService& srv) :srv{ srv } {};
    ConsoleUI(const ConsoleUI& ot) = delete;
    void printMenu();
    void printListMenu();
    void uiAdd();
    void printAllProducts();
    void uiFind();
    void uiRandomize();
    void uiDell();
    void uiFiltreaza();
    void uiModify();
    void uiSort();
    void uiDto();
    void uiValoare_Cos(const vector<Produs>& allproducts);

    void uiaddlist();
    void uiaddrandomlist();
    void uiemptylist();
    void uiCos();
    void printAllfromlist();


    void uiexport();
    void uiundo();
    void run();
};


#endif //UNTITLED_UI_H
