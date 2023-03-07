#ifndef UNTITLED_DTO_H
#define UNTITLED_DTO_H
#include <string>
using std::string;

class DTO {
private:
    string tip;
    int nr;
public:
    DTO() = default;
    DTO(const string& p) :tip{ p }, nr{ 1 } {};
    const string& getTip() noexcept;
    int get_nr() noexcept;
    void incr() noexcept;
};


#endif //UNTITLED_DTO_H
