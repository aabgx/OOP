#include "DTO.h"
#include "DTO.h"
#include "Entities.h"

const string& DTO::getTip() noexcept {
    return tip;
}

int DTO::get_nr() noexcept {
    return nr;
}
void DTO::incr() noexcept {
    nr++;
}

