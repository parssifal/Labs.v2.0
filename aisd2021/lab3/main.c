#include <stdio.h>
#include <stdlib.h>
#include "func1.h"
#include "dialog.h"
int main() {
    int j, n, status;
    puts("Enter the size of your table:");
    do {
        status = get_simple(&n);
    } while (status == 1);
    if (status == -1) return 0;
    Table table;
    table_new(&table, n);
    int a;
    do {
        a = dialog(MSGS, MSGS_SIZE);
        switch(a) {
            case 0:
                puts("Quit");
                break;
            case 1:
                puts("Add new element");
                D_add(&table);
                break;
            case 2:
                puts("Delete element using 2 keys");
                D_delete(&table);
                break;
            case 3:
                puts("Find element using 2 keys");
                j = D_find(&table);
                if (j >= 0) {
                    show_item(&table, j);
                }
                break;
            case 4:
                puts("Show the table");
                show_table(&table);
                break;
            case 5:
                puts("Find element using 1 key");
                Index index;
                index.mas = NULL;
                status = D_find_one(&table, &index);
                if (status < 0) break;
                if (status == 1) {
                    show_table1(&table, &index);
                } else if (status == 2) {
                    show_table2(&table, &index);
                }
                free(index.mas);
                break;
            case 6:
                puts("Delete elements using 1 key");
                D_delete_one(&table);
                break;
            case 7:
                puts("Find children using parent's key");
                Table table2;
                table_new(&table2, table.msize);
                if (D_find_par(&table, &table2) == 0) {
                    show_table_par(&table2);
                }
                table_delete(&table2);
                break;
        }
    } while (a != 0);
    table_delete(&table);
    return 0;
}
