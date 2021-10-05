#ifndef func_h
#define func_h

namespace data {
	typedef struct value {
		unsigned int x;
		int value;
		struct val* next;
	}val;

	typedef struct matrix {
		val** data;
		unsigned int size;
	}matr;
}

using namespace data;

const int read_m(matrix* M, int m);

const int read_rm(matrix* M, bool b);

matrix* init_matrix(int n, int m, bool b);

const int get_val(const char* k);

void clear_m(matrix* m);

matrix* modif_m(matrix* m);
#endif //func_h
