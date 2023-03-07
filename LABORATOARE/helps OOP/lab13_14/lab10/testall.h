//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_TESTALL_H
#define UNTITLED_TESTALL_H
//
// Created by Laura on 4/8/2022.
//

#include "VectorDinamicTemplate.h"
#include "Pet.h"
#include <assert.h>
#include <vector>
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    double totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.getPrice();
    }
    Pet p{ "total","tt",totalPrice };
    v.add(p);
    return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Pet p{ std::to_string(i) + "_type",std::to_string(i) + "_spec",i + 10.0 };
        v.add(p);
    }
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addPets(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).getType() == "50_type");

    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).getType() == "50_type");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3.get(50).getType() == "50_type");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4.get(50).getType() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addPets(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}





#endif //UNTITLED_TESTALL_H
