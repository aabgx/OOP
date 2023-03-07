//
// Created by Laura on 4/25/2022.
//

#include "Undo.h"


const string& UndoException::get_msg() const noexcept {
    return msg;
}

void AddUndo::doUndo() {
    repo.dellrepo(prod);
}

void DelUndo::doUndo() {
    repo.addrepo(prod);
}

void UpdUndo::doUndo() {
    repo.modifyrepo(prod);
}

