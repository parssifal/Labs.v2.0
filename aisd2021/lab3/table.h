#include <stdio.h>
#ifndef TABLE_H
#define TABLE_H
typedef struct Info {
    float f1, f2;
    char *str;
} Info;

typedef struct Item {
    Info info;
	int release;
	char *key1;
	int key2;
	int ind_1;
	int ind_2;
	struct Item *next;
} Item;

typedef struct Space1 {
    char *key;
    char *par;
    Item *item;
} Space1;

typedef struct Space2 {
    int prev_st;
    int busy;
	int key;
	int release;
	Item *item;
} Space2;

typedef struct Table {
    Space1 *ks1;
    Space2 *ks2;
    int num; //number of elements for space1
    int msize;
} Table;

typedef struct Index {
    int k;
    int *mas;
} Index;

int find_space1(Table *table, char *key);
int find_space1_par(Table *table, Table *table2, char *par);
int del_space1(Table *table, char *key);
unsigned int hash1(int key);
unsigned int hash2_1(int key);
unsigned int hash2(int key, int msize);
int put_space2(Table *table, Item *item, int key);
int find_space2(Table *table, int key);
int find_space2_all(Table *table, Index *index, int key);
int del_space2(Table *table, int key);
//составные ключи
int insert_double(Table *table, char *key1, char *par, int key2, float f1, float f2, char *str);
int delete_double(Table *table, char *key1, int key2);
int find_double(Table *table, char *key1, int key2);
void table_new(Table *table, int n);
void table_delete(Table *table);
void show_table1(Table *table, Index *index);
void show_table2(Table *table, Index *index);
void show_table(Table *table);
void show_table_par(Table *table);
void show_item(Table *table, int ind_2);
#endif

