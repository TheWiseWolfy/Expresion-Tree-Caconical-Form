#include <iostream>
#include "Header.h"

using namespace std;
//a*(b+c)+d
//a*(b+c)+a+d*(y+m)

int main() {

	cout << "Introduceti prima expresie:  ( Ex:a*(b+c)+d , Max 10 caractere ) \n";
	Nod* T1 = creareArbore();
	cout << "Introduceti a doua expresie:\n";

	Nod* T2 = creareArbore();

	canonizareArbore(T1);
	canonizareArbore(T2);

	cout << "Forma canonica a prime expresii este: \n";
	afisareArbore(T1);
	cout << "\n";
	cout << "Forma finala a expresiei a doua este: \n";
	afisareArbore(T2);
	cout << "\n";

	if (comparareArbore(T1, T2)) {
		cout << "Formele sunt identice.\n";
	}
	else {
	cout << "Formele nu sunt sunt identice.\n";
	}

	return 0;
}


