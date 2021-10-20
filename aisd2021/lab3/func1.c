#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func1.h"
const char *MSGS_P[] = {"0. Quit", "1. Add new element", "2. Delete element using 2 keys", "3. Find element using 2 keys",
"4. Show the table", "5. Find element using 1 key", "6. Delete elements using 1 key", "7. Find children using parent's key"};
const char **MSGS = MSGS_P;
const int MSGS_SIZE = 8;

const char *MSGS2_P[] = {"0. Quit", "1. Use key1", "2. Use key2"};
const char **MSGS2 = MSGS2_P;
const int MSGS2_SIZE = 3;
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

int get_simple(int *num) { //prime
	int status;
	puts("Enter simple number:");
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
	int n = *num;
    if (n > 1) {
        for (int i = 2; i < n; i++)
            if (n % i == 0) {
                puts("Your number is not simple");
                return 1;
            }
    } else {
        puts("Your number is not simple");
        return 1;
    }
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
/******************/
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
