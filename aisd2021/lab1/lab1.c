//Вариант 5
#include <stdio.h>
#include <malloc.h>

typedef struct Line {
	int n;
	double *a;
} Line;

typedef struct Matrix {
	int lines;
	Line *matr;
} Matrix;


double summ(double a[], int m) {
        double res = 0;
        for ( ;m -- > 0; ++a) {
        res = res + *a;
        }
        return res;
}

double max(Matrix pm) {
	double sum = 0;
	int i, z;
	for (i = 0; i < pm.lines; i++) {
		if (sum < summ(pm.matr[i].a, pm.matr[i].n)) {
			sum = summ(pm.matr[i].a, pm.matr[i].n);
			z = i;
		}
	}
	return z;
}

double change(double a[], int m) {
	double tmp;
	int i, j;
	if (a[0] > 0) {
		for (i = 0; i < m; i++) {
			for (j = i + 1; j < m; j++) {
				if (a[i] >= a[j]) {
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
			}
		}
	} else if (a[0] <= 0) {
                for (i = 0; i < m; i++) {
                        for (j = i + 1; j < m; j++) {
                                if (a[i] < a[j]) {
                                        tmp = a[i];
                                        a[i] = a[j];
                                        a[j] = tmp;
                                }
                        }
                }

	}
	return 0;
}

int getInt(int *a) {
        int n;
        do {
                n = scanf("%d", a);
                if (n < 0) {
                        return 0;
                }
                if (n == 0) {
                printf("%s\n", "Error! Repeat input");
                scanf("%*c");
                }
        } while (n == 0);
        return 1;
}

int getDouble(double *a) {
        int n;
        do{
                n = scanf("%lf", a);
                if (n < 0)
                        return 0;
                if (n == 0){
                        printf("%s\n", "Error! Repeat input");
                        scanf("%*c");
                }
        } while (n == 0);
        return 1;
}

void erase(Matrix *a) {
	int i;
	for (i = 0; i < a->lines; ++i)
		free(a->matr[i].a);
	free(a->matr);
	a->lines = 0;
	a->matr = NULL;
}

int input(Matrix *rm) {
	const char *pr = "";
	int m;
	int i, j;
	double *p;
	do {
		printf("%s\n", pr);
		printf("Enter number of lines: --> ");
		pr = "You are wrong; repeat, please!";
		if(getInt(&m) == 0)
			return 0;
	} while (m < 1);
	rm->lines = m;
	rm->matr = (Line *)calloc(m, sizeof(Line));
	for (i = 0; i < rm->lines; ++i){
		pr = "";
		do {
		printf("%s\n", pr);
		printf("Enter number of items in line %d: --> ", i + 1);
		pr = "You are wrong; repeat, please!";
		if (getInt(&m) == 0){
			rm->lines = i;
			erase(rm);
			return 0;
		}
		} while (m < 1);
		rm->matr[i].n = m;
		p = (double *) malloc(sizeof(double)* m);
		
		rm->matr[i].a = p;
		printf("Enter items for matrix line #%d:\n", i + 1);
		for (j = 0; j < m; ++j, ++p)
			if (getDouble(p) == 0){
				rm->lines = i + 1;
				erase(rm);
				return 0;
			}
		}
		return 1;
}

void output(const char *msg, Matrix a) {
	int i, j;
	double *p;
	printf("%s:\n", msg);
	for (i = 0; i < a.lines; ++i) {
		p = a.matr[i].a;
		for (j = 0; j < a.matr[i].n; ++j, ++p)
			printf("%lf ", *p);
	printf("\n");
	}
}

void newLine(Line* a, Line* b) {
	int i;
	double* pa, * pb;
	b->n = a->n;
	b->a = (double *) malloc(sizeof(double) * b->n);
	pa = a->a;
	pb = b->a;
	for (i = 0; i < b->n; ++i, ++pa, ++pb) {
		*pb = *pa;
	}
}

void newMatr(Matrix* a, Matrix* b) {
	int i;
	b->lines = a->lines;
	b->matr = (Line *)calloc(b->lines, sizeof(Line));
	for (i = 0; i < a->lines; ++i) {
		newLine(&(a->matr[i]), &(b->matr[i]));
	}
}


int main() {
	Matrix matr = {0, NULL};
	Matrix matr1 = {0, NULL};
	int z;
	if (input(&matr) == 0) {
		printf("%s\n", "End  of file occured");
		return 1;
	}
	z = max(matr);
	newMatr(&matr, &matr1);
	change(matr1.matr[z].a, matr1.matr[z].n);
	output("Source matrix", matr);
	output("Modified matrix", matr1);
	erase(&matr);
	erase(&matr1);
	return 0;
}
