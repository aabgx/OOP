//
// Created by Laura on 4/25/2022.
//

#ifndef UNTITLED_UNDO_H
#define UNTITLED_UNDO_H
#pragma once
#include "Repository.h"
#include <string>
using std::string;


class ActiuneUndo{
private:
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class AddUndo: public ActiuneUndo {
private:
    ProdRepo& repo;
    Produs prod;
public:
    AddUndo(ProdRepo& _repo, const Produs& p) :repo{ _repo }, prod{ p }{};
    void doUndo() override;
};

class DelUndo : public ActiuneUndo {
private:
    ProdRepo& repo;
    Produs prod;
public:
    DelUndo(ProdRepo& _repo, const Produs& p) :repo{ _repo }, prod{ p }{};
    void doUndo() override;
};

class UpdUndo : public ActiuneUndo {
private:
    ProdRepo& repo;
    Produs prod;
public:
    UpdUndo(ProdRepo& _repo, const Produs& p) :repo{ _repo }, prod{ p}{};
    void doUndo() override;
};

class UndoException {
private:
    string msg;
public:
    UndoException(const string& msg) :msg{ msg } {};
    const string& get_msg() const noexcept;
};



#endif //UNTITLED_UNDO_H
