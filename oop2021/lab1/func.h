#ifndef func_h
#define func_h

namespace data {
	typedef struct value {
		unsigned int y;
		int value;
		struct val* next;
	} val;

	typedef struct matrix {
		val** data;
		val** cur;
		unsigned int size;
	}matr;
}

using namespace data;

const int read_zm(matrix* M, int m);

const int read_m(matrix* M, bool b);

matrix* init_m(int n, int m, bool b);

const int get_val(const char* k);

void del_m(matrix* m);

matrix* modif_m(matrix* m);
#endif //func_jh
