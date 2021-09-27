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
	int n, m;
	n = get_val("Enter n:");
	m = get_val("Enter m ");
	matrix* M = init_matrix(n, m, 1);
	read_m(M, m);
	matrix* nm = modif_m(M);
	int h;
	while ((h = info())) {
		switch (h) {
		case 1: read_m(M, m); break;
		case 2: read_rm(M, 1); break;
		case 3: read_rm(nm, 0); break;
		case 4:
			clear_m(M);
			clear_m(nm);
			cout << "End of programm.\n";
			return 0;
		}
	}

}