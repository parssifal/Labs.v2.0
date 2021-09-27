#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
int get_int(int *num) {
	int status;
	puts("Enter integer number:");
	status = scanf("%d",num);
	while (status < 1) {
        if (status < 0) {
            return -1;
        }
        printf("It is not a number. Enter again:\n");
		scanf("%*[^\n]");
		scanf("%*c");
		status = scanf("%d",num);
	}
	scanf("%*[^\n]");
	scanf("%*c");
	return 0;
}

int get_u_int(unsigned int *num) {
	int status;
	puts("Enter unsigned integer number:");
	status = scanf("%u",num);
	while (status < 1) {
        if (status < 0) {
            return -1;
        }
        printf("It is not a number. Enter again:\n");
		scanf("%*[^\n]");
		scanf("%*c");
		status = scanf("%u",num);
	}
	scanf("%*[^\n]");
	scanf("%*c");
	return 0;
}

int get_float(float *num) {
	int status;
	puts("Enter float number:");
	status = scanf("%f",num);
	while (status < 1) {
        if (status < 0) {
            return -1;
        }
        printf("It is not a number. Enter again:\n");
		scanf("%*[^\n]");
		scanf("%*c");
		status = scanf("%f",num);
	}
	scanf("%*[^\n]");
	scanf("%*c");
	return 0;
}

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    char *s = NULL;
    int len = 0;
    int n;
    printf("Enter string:\n");
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            s = res;
            res = (char *) realloc(res, sizeof(char) * (str_len + 1));
            if (!res) {
               free(s);
               return NULL;
            }
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char *) calloc(1, sizeof(char));
        if (!res) {
           return NULL;
        }
    }
    return res;
}

int dialog (const char *msgs[], int n) {
    char *error = "";
    int choice = 0;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice:");
        if (get_int(&choice) == -1) choice = 0;
    } while (choice < 0 || choice >= n);
    return choice;
}
