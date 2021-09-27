#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "tree.h"
#include "func.h"
int D_add(Tree *tree) {
    int status;
    unsigned int key;
    float f;
    char *str;
    puts("Enter key");
    status = get_u_int(&key);
    if (status == -1) {
        return -1;
    }
    puts("Enter information");
    status = get_float(&f);
    if (status == -1) {
        return -1;
    }
    str = get_str();
    if (!str) {
        return -1;
    }
    Info *info = (Info*) calloc(1, sizeof(Info));
    info->f = f;
    info->str = str;
    info->next = NULL;
    double time = 0;
    clock_t start, end;
    start = clock();
    tree->root = insert(tree->root, key, info);
    end = clock();
    time += (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time = %.15lf\n", time);
    puts("Element added successfully");
    return 0;
}

int D_add_random(Tree *tree) {
    char *str = NULL;
    puts("Enter number of information that you want to add:");
    int i, num, status;
    status = get_int(&num);
    if (status < 0) {
        puts("Elements wasn't inserted");
        return -1;
    }
    unsigned int key;
    Info *info;
    srand(time(NULL));
    double time = 0;
    clock_t start, end;
    for (i = 0; i < num; i++) {
        str = (char *) calloc(2, sizeof(char));
        str[0] = '1'; str[1] = '\0';
        info = (Info*) calloc(1, sizeof(Info));
        key = rand() % 1000000;
        info->f = 1.0;
        info->str = str;
        info->next = NULL;
        start = clock();
        tree->root = insert(tree->root, key, info);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        str = NULL;
        info = NULL;
    }
    printf("Average time: %.15lf\n", time/num);
    if (num > 0)
        puts("Elements was successfully inserted");
    return 0;
}

int D_delete(Tree *tree) {
    int status;
    unsigned int key;
    puts("Enter key");
    status = get_u_int(&key);
    if (status == -1) {
        return -1;
    }
    double time = 0;
    clock_t start, end;
    start = clock();
    tree->root = remove_tree(tree->root, key);
    end = clock();
    time += (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time = %.15lf\n", time);
    return 0;
}

int D_find(Tree *tree) {
    int status;
    unsigned int key;
    Info *info;
    puts("Enter key");
    status = get_u_int(&key);
    if (status == -1) {
        return -1;
    }
    double time = 0;
    clock_t start, end;
    start = clock();
    info = find(tree->root, key);
    end = clock();
    if (info) {
        while (info) {
            printf("|Key %u| Info %f %s|\n", key, info->f, info->str);
            info = info->next;
        }
        time += (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time = %.15lf\n", time);
    } else puts("Element wasn't found");
    return 0;
}

int D_find_near(Tree *tree) {
    if (!tree->root) {
        puts("Tree is empty");
        return -1;
    }
    int status;
    unsigned int key;
    Info *info;
    puts("Enter key");
    status = get_u_int(&key);
    if (status == -1) {
        return -1;
    }

    Near near;
    near.info = NULL;
    unsigned int dist = UINT_MAX;
    find_near(tree->root, key, &near, &dist);
    info = near.info;
    key = near.key;
    if (info) {
        while (info) {
            printf("|Key %u| Info %f %s|\n", key, info->f, info->str);
            info = info->next;
        }
    } else puts("Key of element is same");
    return 0;
}

int D_show_range(Tree *tree) {
    if (!tree->root) {
        puts("Tree is empty");
        return -1;
    }
    int status;
    unsigned int a, b;
    status = get_u_int(&a);
    if (status == -1) {
        return -1;
    }
    status = get_u_int(&b);
    if (status == -1) {
        return -1;
    }
    if (a <= b) {
        show_range_direct(tree->root, a, b);
    } else {
        show_range_reverse(tree->root, a, b);
    }
    return 0;
}

int D_write_file(Tree *tree) {
    if (!tree->root) {
        puts("Tree is empty");
        return -1;
    }
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
