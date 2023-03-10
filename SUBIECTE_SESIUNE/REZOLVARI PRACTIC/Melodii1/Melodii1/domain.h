#pragma once
#include <utility>

#include "string"

using namespace std;
class Melodie {
private:
    int id, rank;
    string titlu, artist;

public:
    Melodie(int id, string titlu, string artist, int rank) : id(id), titlu(titlu), artist(artist), rank(rank) {};
    int get_id() const { return id; };
    int get_rank() const { return rank; };
    string get_titlu() const { return titlu; };
    string get_artist() const { return artist; };


    void set_titlu(string titlu_nou) { this->titlu = titlu_nou; };
    void set_rank(int rank_nou) { this->rank = rank_nou; }
};

void test_creaza();
void test_set();