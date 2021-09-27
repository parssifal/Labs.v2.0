#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "func1.h"
int find_space1(Table *table, char *key) {
    if (table->num < 1) {
        puts("Table is empty");
        return -1;
    }
    for (int i = 0; i < table->num; i++) {
        if (strcmp(table->ks1[i].key, key)==0)
            return i;
    }
    puts("Element was not found");
    return -1;
}

int find_space1_par(Table *table, Table *table2, char *par) {
    if (table->num < 1) {
        puts("Table is empty");
        return -1;
    }
    for (int i = 0; i < table->num; i++) {
        if (strcmp(table->ks1[i].par, par)==0) {
            Item *ptr = table->ks1[i].item;
            int j;
            Item *item, *item_first, *item_prev = NULL;
            while (ptr) {
                item = (Item *) calloc(1, sizeof(Item));
                item->ind_1 = i;
                item->info.f1 = ptr->info.f1;
                item->info.f2 = ptr->info.f2;
                item->info.str = (char *)calloc(strlen(ptr->info.str) + 1, sizeof(char));
                strcpy(item->info.str, ptr->info.str);
                item->key1 = (char *)calloc(strlen(ptr->key1) + 1, sizeof(char));
                strcpy(item->key1, ptr->key1);
                item->key2 = table->ks1[i].item->key2;
                item->release = ptr->release;
                j = table->ks1[i].item->ind_2;
                item->ind_2 = table->ks2[j].release; //in ind2 save release of key2
                if (item_prev) {
                    item_prev->next = item;
                } else item_first = item;
                item_prev = item;
                ptr = ptr->next;
            }
            table2->ks1[table2->num].par = (char *)calloc(strlen(par) + 1, sizeof(char));
            strcpy(table2->ks1[table2->num].par, par);
            table2->ks1[table2->num].key = item_first->key1;
            table2->ks1[table2->num].item = item_first;
            table2->num++;
        }
    }
    if (table2->num > 0) {
        return 0;
    } else return -1;
}

int del_space1(Table *table, char *key) {
    int i = find_space1(table, key);
    if (i < 0)
        return -1;
    table->num--;
    int n = table->num;
    Item *ptr_prev, *ptr = table->ks1[i].item;
    int j;
    j = ptr->ind_2;
    table->ks2[j].busy = 0;
    for (j = 0; j <= n; j++) {
        if (strcmp(table->ks1[j].par, key) == 0) {
            table->ks1[j].par = (char *)realloc(table->ks1[j].par, 2*sizeof(char));
            table->ks1[j].par[0] = '0';
            table->ks1[j].par[1] = '\0';
        }
    }
    while (ptr) {
        free(ptr->info.str);
        free(ptr->key1);
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(table->ks1[i].par);
    table->ks1[i].key = table->ks1[n].key;
    table->ks1[i].par = table->ks1[n].par;
    table->ks1[i].item = table->ks1[n].item;
    puts("Element was deleted successfully");
    return 0;
}

/******************/
unsigned int hash1(int key){
	char *s = (char*)&key;
	unsigned int hash = 0;
	for (int i = 0; i < sizeof(int); i++) {
		hash += (unsigned char)(*s);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		s++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

unsigned int hash2_1(int key){
	char *s = (char*)&key;
	unsigned int hash = 0;
	for(int i = 0; i < sizeof(int); i++) {
		hash += (unsigned char)(*s);
		hash -= (hash << 13) | (hash >> 19);
		s++;
	}
	return hash;
}

unsigned int hash2(int key, int msize){
	unsigned int hash = hash2_1(key);
	while(hash % msize == 0){
		hash = hash2_1(hash);
	}
	return hash % msize;
}

int put_space2(Table *table, Item *item, int key) {
    int m, j, i, prev_release = -1;
    int z = -1;
    m = table->msize;
    j = (hash1(key) + hash2(key, m)) % m;
    for(i = 0; i < m; i++) {
		if (table->ks2[j].prev_st == 0) {
			table->ks2[j].busy = 1;
			table->ks2[j].key = key;
			table->ks2[j].release = prev_release + 1;
			table->ks2[j].prev_st = 1;
			table->ks2[j].item = item;
			puts("Element successfully added");
			return j;
		} else if (table->ks2[j].busy == 0 && z == -1) {
		    z = j;
		}
		if (table->ks2[j].key == key) {
            if (prev_release < table->ks2[j].release) {
                prev_release = table->ks2[j].release;
            }
		}
		j = (j + 1) % m;
	}
	if (z >= 0) {
        table->ks2[z].busy = 1;
        table->ks2[z].key = key;
		table->ks2[z].release = prev_release + 1;
		table->ks2[z].prev_st = 1;
		table->ks2[z].item = item;
		puts("Element successfully added");
		return z;
	}
	puts("Table is full. Element was not added");
	return -1;
}

int find_space2(Table *table, int key) {
    //find the first element with this key
    int m, j, i;
    m = table->msize;
    j = (hash1(key) + hash2(key, m)) % m;
    for(i = 0; i < m; i++) {
		if (table->ks2[j].busy == 1 && table->ks2[j].key == key) {
			return j;
		}
		if (table->ks2[j].busy == 0 && table->ks2[j].prev_st == 0) {
			puts("Element was not found");
            return -1;
		}
		j = (j + 1) % m;
	}
	puts("Element was not found");
    return -1;
}

int find_space2_all(Table *table, Index *index, int key) {
    int m, j, i;
    index->k = 0;
    m = table->msize;
    j = (hash1(key) +  hash2(key, m)) % m;
    for(i = 0; i < m; i++) {
		if (table->ks2[j].busy == 1 && table->ks2[j].key == key) {
            index->k++;
			index->mas = (int *) realloc(index->mas, index->k * sizeof(int));
			index->mas[index->k - 1] = j;
		}
		if (table->ks2[j].busy == 0 && table->ks2[j].prev_st == 0) {
		    if(index->k == 0) {
                puts("Element was not found");
                return -1;
		    } else return 0;
		}
		j = (j + 1) % m;
	}

	if(index->k == 0) {
        puts("Element was not found");
        return -1;
    } else return 0;
}

int del_space2(Table *table, int key) {
    int m, j, i, count;
    m = table->msize;
    count = 0;
    j = (hash1(key) +  hash2(key, m)) % m;
    for(i = 0; i < m; i++) {
		if (table->ks2[j].busy == 1 && table->ks2[j].key == key) {
            del_space1(table, table->ks2[j].item->key1);
            count++;
		}
		if (table->ks2[j].busy == 0 && table->ks2[j].prev_st == 0) {
			if (count == 0) {
                puts("Element was not found");
                return -1;
			} else return 0;
		}
		j = (j + 1) % m;
	}
    if (count == 0) {
        puts("Element was not found");
        return -1;
    } else return 0;
}

/******************/
//составные ключи
int insert_double(Table *table, char *key1, char *par, int key2, float f1, float f2, char *str) {
    Item *item = (Item *)calloc(1, sizeof(Item));
    item->key1 = key1;
    item->key2 = key2;
    item->info.f1 = f1;
    item->info.f2 = f2;
    item->info.str = str;
    item->release = 0;
    item->next = NULL;
    //insert in space1
    int i = find_space1(table, key1);
    if (i >= 0) {
        if (table->ks1[i].item->key2 != key2) {
            puts("Element with such key1 already exists. Element was not added");
            free(item);
            return -1;
        } else {
            if (strcmp(par, table->ks1[i].par) != 0)
                puts("Parent's key is not similar. It was changed");
            free(par);
            Item *ptr = table->ks1[i].item;
            int d = 0;
            while (ptr->next) {
                ptr = ptr->next;
                d++;
            }
            item->release = d;
            ptr->next = item;
            puts("Element successfully added");
            return 0;
        }
    }
    int n = table->num;
    if (n >= table->msize) {
        puts("Table is full. Element was not added");
        free(item);
        return -1;
    }
    int z = 0;
    if (!(par[0] == '0' && par[1] == '\0')) {
        for (int j = 0; j < n; j++)
            if (strcmp(table->ks1[j].key, par) == 0) {
                z = 1;
                break;
            }
    } else z = 1;
    if (z == 0) {
        puts("Element with such parent's key was not found. Element was not added");
        free(item);
        return -1;
    }
    item->ind_1 = n;
    table->ks1[n].key = key1;
    table->ks1[n].par = par;
    table->ks1[n].item = item;
    table->num++;

    //insert in space2
    int j;
    if ((j = put_space2(table, item, key2)) >= 0) {
        table->ks1[n].item->ind_2 = j;
        return 0;
    } else {
        free(item);
        return -1;
    }
}

int delete_double(Table *table, char *key1, int key2) {
    //delete from space1
    int i = find_space1(table, key1);
    if (i < 0) {
        return -1;
    }
    if (table->ks1[i].item->key2 != key2) {
        puts("Element with these keys doesn't exist");
        return -1;
    }
    table->num--;
    int n = table->num;
    free(table->ks1[i].par);
    Item *ptr_prev, *ptr = table->ks1[i].item;
    int j;
    j = ptr->ind_2;
    while (ptr) {
        free(ptr->info.str);
        free(ptr->key1);
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    table->ks1[i].key = table->ks1[n].key;
    table->ks1[i].par = table->ks1[n].par;
    table->ks1[i].item = table->ks1[n].item;

    for (int j = 0; j < n; j++) {
        if (strcmp(table->ks1[j].par, key1) == 0) {
            table->ks1[j].par = (char *)realloc(table->ks1[j].par, 2*sizeof(char));
            table->ks1[j].par[0] = '0';
            table->ks1[j].par[1] = '\0';
        }
    }
    //delete from space2
    table->ks2[j].busy = 0;
    puts("Element was deleted successfully");
    return 0;
}

int find_double(Table *table, char *key1, int key2) {
    //find in space2 and compare key1
    int m, j, i;
    m = table->msize;
    j = (hash1(key2) +  hash2(key2, m)) % m;
    for (i = 0; i < m; i++) {
		if (table->ks2[j].busy == 1 && table->ks2[j].key == key2) {
		    if (strcmp(key1, table->ks2[j].item->key1) == 0) {
                return j;
		    }
		}
		if (table->ks2[j].busy == 0 && table->ks2[j].prev_st == 0) {
            return -1;
		}
		j = (j + 1) % m;
	}
    return -1;
}


/******************/

void table_new(Table *table, int n) {
    table->msize = n;
    table->num = 0;
    table->ks1 = (Space1 *) calloc(n, sizeof(Space1));
    table->ks2 = (Space2 *) calloc(n, sizeof(Space2));
    for (int i = 0; i < n; i++) {
        table->ks2[i].busy = 0;
        table->ks2[i].prev_st = 0;
    }
    return;
}

void table_delete(Table *table) {
    int n = table->num;
    Item *ptr, *ptr_prev;;
    for (int i = 0; i < n; i++) {
        ptr = table->ks1[i].item;
        free(table->ks1[i].par);
        while (ptr) {
            free(ptr->info.str);
            free(ptr->key1);
            ptr_prev = ptr;
            ptr = ptr->next;
            free(ptr_prev);
        }
    }
    free(table->ks1);
    free(table->ks2);
}

/******************/
void show_table1(Table *table, Index *index) {
    if (index->mas == NULL) return;
    puts("");
    int j, d, a;
    Item *ptr;
    a = index->mas[0];
    j = table->ks1[a].item->ind_2;
    ptr = table->ks1[a].item;
    d = 0;
    do {
        printf("|Key1: %s| Par: %s| Key2 %d| K2 Release %d| Item Release %d| Info %f %f %s|\n",table->ks1[a].key, table->ks1[a].par,
            table->ks2[j].key, table->ks2[j].release, d, ptr->info.f1, ptr->info.f2, ptr->info.str);
        ptr = ptr->next;
        d++;
    } while (ptr);
    puts("");
}

void show_table2(Table *table, Index *index) {
    if (index->mas == NULL) return;
    puts("");
    int j, d, a;
    Item *ptr;
    for (int i = 0; i < index->k; i++) {
        a = index->mas[i];
        j = table->ks2[a].item->ind_1;
        ptr = table->ks2[a].item;
        d = 0;
        do {
            printf("|Key1: %s| Par: %s| Key2 %d| K2 Release %d| Item Release %d| Info %f %f %s|\n",table->ks1[j].key, table->ks1[j].par,
               table->ks2[a].key, table->ks2[a].release, d, ptr->info.f1, ptr->info.f2, ptr->info.str);
            ptr = ptr->next;
            d++;
        } while (ptr);
    }
    puts("");
}

void show_table(Table *table) {
    int n = table->num;
    puts("");
    int j, d;
    Item *ptr;
    for (int i = 0; i < n; i++) {
        j = table->ks1[i].item->ind_2;
        ptr = table->ks1[i].item;
        d = 0;
        do {
            printf("|Key1: %s| Par: %s| Key2 %d| K2 Release %d| Item Release %d| Info %f %f %s|\n",table->ks1[i].key, table->ks1[i].par,
               table->ks2[j].key, table->ks2[j].release, d, ptr->info.f1, ptr->info.f2, ptr->info.str);
            ptr = ptr->next;
            d++;
        } while (ptr);
    }
    puts("");
}

void show_table_par(Table *table) {
    int n = table->num;
    puts("");
    int j, d;
    Item *ptr;
    for (int i = 0; i < n; i++) {
        j = table->ks1[i].item->ind_2;
        ptr = table->ks1[i].item;
        d = 0;
        do {
            printf("|Key1: %s| Par: %s| Key2 %d| K2 Release %d| Item Release %d| Info %f %f %s|\n",table->ks1[i].key, table->ks1[i].par,
               table->ks1[i].item->key2, j, d, ptr->info.f1, ptr->info.f2, ptr->info.str);
            ptr = ptr->next;
            d++;
        } while (ptr);
    }
    puts("");
}

void show_item(Table *table, int ind_2) {
    int j = ind_2;
    Item *ptr = table->ks2[j].item;
    int i, d = 0;
    i = ptr->ind_1;
    do {
        printf("|Key1: %s| Par: %s| Key2 %d| K2 Release %d| Item Release %d| Info %f %f %s|\n", table->ks1[i].key, table->ks1[i].par,
            table->ks2[j].key, table->ks2[j].release, d, ptr->info.f1, ptr->info.f2, ptr->info.str);
        ptr = ptr->next;
        d++;
    } while (ptr);
}
