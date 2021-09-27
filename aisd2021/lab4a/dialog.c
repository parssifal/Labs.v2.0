#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#include "dialog.h"
int D_add(Tree *tree) {
    char *key, *info;
    puts("Enter key:");
    key = get_str();
    if (!key) {
        puts("Element wasn't inserted");
        return -1;
    }
    puts("Enter info:");
    info = get_str();
    if (!info) {
        free(key);
        puts("Element wasn't inserted");
        return -1;
    }
    double time;
    clock_t start, end;
    start = clock();
    insert(tree, key, info);
    end = clock();
    puts("Element was successfully inserted");
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.15lf\n", time);
    return 0;
}

int D_add_random(Tree *tree) {
    char *key, *info;
    puts("Enter number of information that you want to add:");
    int i, num, status, len;
    status = get_int(&num);
    if (status < 0) {
        puts("Elements wasn't inserted");
        return -1;
    }
    double time = 0;
    clock_t start, end;
    len = 5;
    for (i = 0; i < num; i++) {
        info = (char *) calloc(2, sizeof(char));
        info[0] = '1';
        info[1] = '\0';
        key = random_str(len);
        start = clock();
        insert(tree, key, info);
        end = clock();
        time += ((double)(end - start) / CLOCKS_PER_SEC);
        key = NULL;
        info = NULL;
    }
    if (num > 0) {
        printf("Average time: %.15lf\n", time/num);
        puts("Elements was successfully inserted");
    }
    return 0;
}

int D_find(Tree *tree, Address *address) {
    char *key;
    puts("Enter key:");
    key = get_str();
    if (!key) {
        return -1;
    }
    int status;
    double time;
    clock_t start, end;
    start = clock();
    status = find(tree, key, address);
    end = clock();
    if (status == -1) {
        puts("Nothing was founded");
        free(key);
        return -1;
    }
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.15lf\n", time);
    free(key);
    return 0;
}

int D_find_min(Tree *tree, Address *address) {
    if (find_min_all(tree, address) == -1) {
        puts("Nothing was founded");
        return -1;
    }
    return 0;
}

int D_delete(Tree *tree) {
    char *key;
    puts("Enter key:");
    key = get_str();
    if (!key) {
        puts("Element wasn't deleted");
        return -1;
    }
    puts("Enter number of element you want to delete:");
    int num, status;
     status = get_int(&num);
    if (status == -1) {
        puts("Element wasn't deleted");
        free(key);
        return -1;
    }
    double time;
    clock_t start, end;
    start = clock();
    status = delete_node(tree, key, num);
    end = clock();
    if (status == 0) {
        puts("Element was successfully deleted");
        time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time: %.15lf\n", time);
        free(key);
        return 0;
    } else {
        puts("Element with this key and number wasn't founded");
        free(key);
        return -1;
    }
}

int D_write_file(Tree *tree) {
    puts("Enter name of file");
    char *name = get_str();
    if (!name)
        return -1;
    int status = file_write(name, tree);
    free(name);
    if (status == -1) {
        puts("File couldn't be opened");
        return -1;
    }
    if (status == -2) {
        puts("Tree is empty");
        return -1;
    }
    puts("Information was successfully written");
    return 0;
}

int D_read_file(Tree *tree) {
    puts("Enter name of file");
    char *name = get_str();
    if (!name)
        return -1;
    int status = file_read(name, tree);
    free(name);
    if (status == -1) {
        puts("File with this name wasn't found");
        return -1;
    }
    puts("Information was successfully read");
    return 0;
}

