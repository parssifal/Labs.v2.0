#include <iostream>
//#include <cstdlib>
#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC

#include "func.h"

using namespace data;
using namespace std;

int info() {
	int h;
	do {
		cout << "Choose an option.\n" << "1. Read matrix.\n2. Read real matrix.\n3. Read modified matrix.\n4. Exit.\n";
	} while ((h = get_val("Your choise: ")) < 1 && h > 4);
	return h;
}

int main() {
	//int n, m;
	n = get_val("Enter n: ");
	m = get_val("Enter m: ");
	matrix* M = init_m(n, m, 1);
	read_zm(M, m);
	matrix* nm = modif_m(M);
	int h;
	while ((h = info())) {
		switch (h) {
		case 1: read_zm(M, m); break;
		case 2: read_m(M, 1); break;
		case 3: read_m(nm, 0); break;
		case 4:
			del_m(M);
			del_m(nm);
			cout << "End of programm.\n";
			return 0;
		}
	}

}
