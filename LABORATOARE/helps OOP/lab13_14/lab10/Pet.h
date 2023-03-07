//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_PET_H
#define UNTITLED_PET_H
#include <string>

class Pet
{
public:
    Pet() = default;
    Pet(std::string t, std::string s, double p) :type{ t }, species{ s }, price{ p } {
    }
    double getPrice() const noexcept {
        return price;
    }
    std::string getType() const {
        return type;
    }
private:
    std::string type;
    std::string species;
    double price=-1.0;

};


#endif //UNTITLED_PET_H
