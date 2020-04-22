#include <iostream>
#include "Header.h"

using namespace std;

void canonizareArbore(Nod*& nod) {

    int j = 0;
    bool flag = 0;
    Nod* nodVec;
    //verificam fiecare nod
    for (int f1 = 0; f1 < nod -> grad; ++f1) {
        if (nod -> vDesc[f1] != nullptr) {
            canonizareArbore(nod -> vDesc[f1]);
            flag = 1;

        }
    }

    // in caz ca e nod terminal ,inlocuim corespunzator
    if (flag == 0) {
    //    Nod* temp;
        Nod* S = make_nod(1);
        Nod* P = make_nod(1);
        Nod* D = make_nod(0);

        S -> data = 'S';
        S -> vDesc[0] = P;

        P -> data = 'P';
        P -> vDesc[0] = D;

        D -> data = nod -> data;

        //Rescriem nodul cu ceva dragut
        //temp = nod;
        nod = S;
    //    delete(temp);
        return;
    }

    if (nod -> data == '+') {

        sumareArbore(nod);
        return;
    }
    if (nod -> data == '*') {

        inmultireArbore(nod);
        return;
    }
}
void sumareArbore(Nod*& nod) {

    int j = 0;
    Nod* child, * temp = nod;
    Nod* vec[VECTOR_SIZE];

    //Parcurgem fiecare copil al nodului +
    for (int f1 = 0; f1 < nod -> grad; ++f1) {
        // Parcurgem copiii copiilor si le retinem adresele

        if (nod -> vDesc[f1] != nullptr) {

            child = nod -> vDesc[f1];

            for (int f2 = 0; f2 < child -> grad; ++f2) {

                if (child -> vDesc[f2] != nullptr) {

                    vec[j] = child -> vDesc[f2];

                    ++j;
                }
            }
            delete(child);
        }
    }
    Nod* S = make_nod(j);
    S -> data = 'S';

    for (int f1 = 0; f1 < j; ++f1) {
        S -> vDesc[f1] = vec[f1];
    }
    nod = S;
    //delete(temp);
}
void inmultireArbore(Nod*& nod) {

    Nod* child, * temp;
    Nod* vec[15][15];
    int f1, f2, j =0;
    int size = 1, nrTermeniParanteza[15], nrParanteze;

    for (f1 = 0; f1 < nod -> grad; ++f1) {

        if (nod -> vDesc[f1] != nullptr) {

            child = nod -> vDesc[f1];

            for (f2 = 0; f2 < child -> grad; ++f2) {

                if (child -> vDesc[f2] != nullptr) {

                    vec[f1][f2] = child -> vDesc[f2] -> vDesc[0];
                }
            }
            delete(child);
            //Numarul de termeni din fiecare paranteza
            nrTermeniParanteza[f1] = f2;
        }
    }
    //Stocam cate paranteze avem
    nrParanteze = f1;

    //Calculam numarul de noduri necesare
    for (int f1 = 0; f1 < nrParanteze; ++f1) {
        size *= nrTermeniParanteza[f1];
    }

    //Cream un nod nou

    Nod* S = make_nod(size);
    S -> data = 'S';

    //Creeam produsele rezultate 
    Nod** P = new Nod * [size];

    //To improve
    for (int f1 = 0; f1 < size; ++f1) {
        P[f1] = make_nod(nrParanteze);
        P[f1] -> data = 'P';
        S -> vDesc[f1] = P[f1];
    }

    //Pentru fiecare membru din prima paranteza
    for (f1 = 0; f1 < nrTermeniParanteza[0]; ++f1) {
        for (f2 = 0; f2 < size / nrTermeniParanteza[0]; ++f2) {
            P[j]->vDesc[0] = vec[0][f1];
            ++j;
        }
    }
    j = 0;
    for (f1 = 0; f1 < nrTermeniParanteza[1]; ++f1) {
        for (f2 = 0; f2 < size/ nrTermeniParanteza[1]; ++f2) {
        
            P[j]->vDesc[1] = vec[1][f1];
            ++j;
        }
    }
    temp = nod;
    nod = S;

    //  delete(temp);
}
bool comparareArbore(Nod* nod1, Nod* nod2) {

    if (nod1 -> grad != nod2 -> grad)
        return false;

    //Modalitate de a asigura ca acelasi nod nu este luat in considerare de 2 ori
    bool flagged[VECTOR_SIZE], found;

    for (int f1 = 0; f1 < VECTOR_SIZE; ++f1) {
        flagged[f1] = false;
    }

    Nod* child1, * child2;
    for (int f1 = 0; f1 < nod1 -> grad; ++f1) {
        // Parcurgem copiii copiilor si le retinem adresele
        child1 = nod1 -> vDesc[f1];
        found = false;
        for (int f2 = 0; f2 < nod2 -> grad; ++f2) {
            child2 = nod2 -> vDesc[f2];
            if (comparareNod(child1, child2) && !flagged[f2]) {
                found = true;
                flagged[f2] = true;
                break;
            }

        }
        if (!found) {
            return false;
        }
    }
    return true;
}
//Comparare nod individual

bool comparareNod(Nod* nod1, Nod* nod2) {

    bool flagged[VECTOR_SIZE];
    bool found;


    if (nod1 -> grad != nod2 -> grad)
        return false;

    for (int f1 = 0; f1 < VECTOR_SIZE; ++f1) {
        flagged[f1] = false;
    }

    Nod* child1, * child2;
    for (int f1 = 0; f1 < nod1 -> grad; ++f1) {
        // Parcurgem copiii copiilor si le retinem adresele
        child1 = nod1 -> vDesc[f1];
        found = false;
        for (int f2 = 0; f2 < nod1 -> grad; ++f2) {
            child2 = nod2 -> vDesc[f2];
            if (child1 -> data == child2 -> data && !flagged[f2]) {
                found = true;
                flagged[f2] = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

//afisare arbore arbore recursiv
void afisareArbore(Nod* nod) {
    cout << nod -> data << " ";

    for (int f1 = 0; f1 < nod -> grad; ++f1) {
        if (nod -> vDesc[f1] != nullptr) {
            afisareArbore(nod -> vDesc[f1]);
        }
    }
}
Nod* creareArbore() {
    char buffer[DIM_EXPR];
    cin >> buffer;
    int length = strlen(buffer);
    Nod* n = parse(buffer, 0, length - 1);
    return n;
}
Nod* make_nod(int grad) {

    // ?? that looks not safe
    Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - grad) * sizeof(Nod*)];
    p -> grad = grad;
    return p;
}

Nod* parse(char buffer[], int start, int end) {
    int openP = 0;
    int indici[GRMAX];
    int k = 0;
    openP = 0;

    for (int i = start; i <= end; i++) {
        if (buffer[i] == '(') openP++;
        if (buffer[i] == ')') openP--;
        if (buffer[i] == '+') {
            if (openP > 0) {
                continue;
            }
            indici[k++] = i;
        }
    }

    if (k > 0) {
        Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - k + 1) * sizeof(Nod*)];
        p -> grad = k + 1;
        p -> data = '+';

        //Parte recursiva
        p -> vDesc[0] = parse(buffer, start, indici[0] - 1);
        for (int j = 1; j < p -> grad - 1; j++) {
            p -> vDesc[j] = parse(buffer, indici[j - 1] + 1, indici[j] - 1);
        }
        p -> vDesc[p -> grad - 1] = parse(buffer, indici[p -> grad - 2] + 1, end);
        return p;
    }
    openP = 0;

    for (int i = start; i <= end; i++) {
        if (buffer[i] == '(') openP++;
        if (buffer[i] == ')') openP--;
        if (buffer[i] == '*') {
            if (openP > 0) {
                continue;
            }
            indici[k++] = i;
        }
    }

    if (k > 0) {
        Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX - k + 1) * sizeof(Nod*)];
        p -> grad = k + 1;
        p -> data = '*';

        //Parte recursiva
        p -> vDesc[0] = parse(buffer, start, indici[0] - 1);
        for (int j = 1; j < p -> grad - 1; j++) {
            p -> vDesc[j] = parse(buffer, indici[j - 1] + 1, indici[j] - 1);
        }
        p -> vDesc[p -> grad - 1] = parse(buffer, indici[p -> grad - 2] + 1, end);
        return p;
    }

    if (buffer[start] == '(' && buffer[end] == ')') {
        return parse(buffer, start + 1, end - 1);
    }
    if (start == end) {
        if (true) {
            Nod* p = (Nod*) new char[sizeof(Nod) - (GRMAX) * sizeof(Nod*)];
            p -> data = buffer[start];
            p -> grad = 0;
            return p;
        }
    }
    printf("\nExpresia de intrare este eronata. Apasati o tasta");
    exit(1);
}
//300 !