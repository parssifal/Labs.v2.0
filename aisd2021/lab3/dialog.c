#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialog.h"
#include "func1.h"
int D_add(Table *table) {
    char *key1, *par, *str;
    puts("Add key1");
    key1 = get_str();
    if (!key1)
        return -1;
    puts("Add parent's key or enter 0 if parent doesn't exist");
    par = get_str();
    if (!par) {
        free(key1);
        return -1;
    }
    int key2, status, n;
    puts("Add key2");
    status = get_int(&key2);
    if (status == -1) {
        free(key1);
        free(par);
        return -1;
    }
    float f1, f2;
    puts("/Information/");
    puts("Enter float number 1");
    status = get_float(&f1);
    if (status == -1) {
        free(key1);
        free(par);
        return -1;
    }
    puts("Enter float number 2");
    status = get_float(&f2);
    if (status == -1) {
        free(key1);
        free(par);
        return -1;
    }
    puts("Enter string");
    str = get_str();
    if (!str) {
        free(key1);
        free(par);
        return -1;
    }
    n = insert_double(table, key1, par, key2, f1, f2, str);
    if (n == -1) {
        free(key1);
        free(par);
        free(str);
        return -1;
    } else return 0;
}

int D_delete(Table *table) {
    char *key1;
    puts("Add key1");
    key1 = get_str();
    if (!key1) return -1;
    int key2, status;
    puts("Add key2");
    status = get_int(&key2);
    if (status == -1) {
        free(key1);
        return -1;
    }
    if (delete_double(table, key1, key2) == 0) {
        free(key1);
        return 0;
    } else {
        free(key1);
        return -1;
    }
}

int D_find(Table *table) {
    char *key1;
    puts("Add key1");
    key1 = get_str();
    if (!key1) return -1;
    int key2, status;
    puts("Add key2");
    status = get_int(&key2);
    if (status == -1) {
        free(key1);
        return -1;
    }
    int j;
    j = find_double(table, key1, key2); //index in space2
    if (j >= 0) {
        free(key1);
        return j;
    } else {
        free(key1);
        puts("Element with this keys doesn't exist");
        return -1;
    }
}

int D_find_one(Table *table, Index *index) {
    int i;
    int a = dialog(MSGS2, MSGS2_SIZE);
    if (a == 0) return -1;
    if (a == 1) {
        char *key1;
        puts("Add key1");
        key1 = get_str();
        if (!key1) return -1;
        i = find_space1(table, key1);
        if (i < 0) {
            free(key1);
            return -1;
        }
        index->k = 1; //number of indexes
        index->mas = (int *) calloc(1, sizeof(int));
        index->mas[0] = i;
        free(key1);
        return 1;
    } else if (a == 2) {
        int key2, status;
        puts("Add key2");
        status = get_int(&key2);
        if (status == -1) {
            return -1;
        }
        status = find_space2_all(table, index, key2);
        if (status < 0) {
            return -1;
        }
        return 2;
    }
    return 0;
}

int D_find_par(Table *table, Table *table2) {
    char *par;
    puts("Add parent's key");
    par = get_str();
    if (!par) return -1;
    if (find_space1_par(table, table2, par) == -1)
        puts("Element with this parent's key doesn't exist");
    free(par);
    return 0;
}

int D_delete_one(Table *table) {
    int i;
    int a = dialog(MSGS2, MSGS2_SIZE);
    if (a == 0) return -1;
    if (a == 1) {
        char *key1;
        puts("Add key1");
        key1 = get_str();
        if (!key1) return -1;
        i = del_space1(table, key1);
        if (i < 0) {
            free(key1);
            return -1;
        }
        free(key1);
        return 1;
    } else if (a == 2) {
        int key2, status;
        puts("Add key2");
        status = get_int(&key2);
        if (status == -1) {
            return -1;
        }
        status = del_space2(table, key2);
        if (status < 0) {
            return -1;
        }
        return 2;
    }
    return 0;
}
