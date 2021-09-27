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

char *file_str(FILE *file) {
    char buf[81] = {0};
    char *res = NULL;
    char *s = NULL;
    int len = 0;
    int n;

    do {
        n = fscanf(file,"%80[^\n]", buf);
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
            fscanf(file, "%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
        res = (char *) realloc(res, sizeof(char) * (strlen(res) + 10));
    } else {
        res = (char *) calloc(1, sizeof(char));
    }
    return res;
}

char *random_str(int len) {
    int i, k;
    char *str = (char *) calloc(len + 1, sizeof(char));
    for (i = 0; i < len; ++i) {
         k = rand() % 74;
         str[i] = '0' + k;
         if (str[i] == 92) //number of \ symbol
            str[i] = '0';
    }
    str[len] = '\0';
    return str;
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
