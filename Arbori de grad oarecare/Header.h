#pragma once


#define DIM_EXPR 100
#define GRMAX 10
#define VECTOR_SIZE 15
typedef char Atom;

struct Nod {
    Atom data;          
    int grad;
    Nod* vDesc[GRMAX];
};

void afisareArbore(Nod* nod);
void canonizareArbore(Nod* &nod);
void sumareArbore(Nod* &nod);
void inmultireArbore(Nod*& nod);
bool comparareArbore(Nod* nod1,Nod* nod2);
bool comparareNod(Nod* nod1, Nod* nod2);

Nod* creareArbore();
Nod* parse(char buffer[], int start, int end);
Nod* make_nod(int grad);