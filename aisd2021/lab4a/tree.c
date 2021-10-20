#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *node_new() {
    Node *node = (Node *) calloc(1, sizeof(Node));
    node->key = NULL;
    node->info = NULL;
    node->left = NULL;
    node->right = NULL;
    node->par = NULL;
    node->next = NULL;
    return node;
}

Node *find_min(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return NULL;
    while (ptr->left) {
        ptr = ptr->left;
    }
    return ptr;
}

Node *find_max(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return NULL;
    while (ptr->right) {
        ptr = ptr->right;
    }
    return ptr;
}

int find_min_all(Tree *tree, Address *address) {
    Node *ptr = tree->root;
    if (!ptr)
        return -1;
    while (ptr->left) {
        ptr = ptr->left;
    }
    char *key = ptr->key;
    int k = 0;
    address->mas = NULL;
    do {
        k++;
        address->mas = (Node **) realloc(address->mas, k * sizeof(Node *));
        address->mas[k - 1] = ptr;
        ptr = ptr->right;
    } while (ptr && strcmp(key, ptr->key) == 0);
    address->k = k;
    return 0;
}

Node *find_next(Node *node) {
    Node *ptr, *x = node;
    if (!x)
        return NULL;
    if (x->right) {
        ptr = find_min(x->right);
        return ptr;
    }
    ptr = x->par;
    while (ptr && x == ptr->right) {
        x = ptr;
        ptr = x->par;
    }
    return ptr;
}

Node *find_prev(Node *node) {
    Node *ptr, *x = node;
    if (!x)
        return NULL;
    if (x->left) {
        ptr = find_max(x->left);
        return ptr;
    }
    ptr = x->par;
    while (ptr && x == ptr->left) {
        x = ptr;
        ptr = x->par;
    }
    return ptr;
}

int find(Tree *tree, char *key, Address *address) {
    Node *ptr = tree->root;
    if (!ptr)
        return -1;
    while (ptr) {
        if (strcmp(key, ptr->key) < 0) {
            ptr = ptr->left;
        } else if (strcmp(key, ptr->key) > 0) {
            ptr = ptr->right;
        } else if (strcmp(key, ptr->key) == 0) {
            int k = 0;
            address->mas = NULL;
            do {
                k++;
                address->mas = (Node **) realloc(address->mas, k * sizeof(Node *));
                address->mas[k - 1] = ptr;
                ptr = ptr->next;
            } while (ptr && strcmp(key, ptr->key) == 0);
            address->k = k;
            return 0;
        }
    }
    return -1;
}

void find_count_of_words(Tree *tree, Words *words) {
    Node *ptr = tree->root;
    if (!ptr)
        return;
    int count = 0, k = 0;
    ptr = find_min(ptr);
    Node *prev;
    while (ptr) {
        count++;
        prev = ptr;
        ptr = ptr->next;
        if (!ptr || strcmp(prev->key, ptr->key) != 0) {
            k++;
            words->k = k;
            words->mas = (char **) realloc(words->mas, k * sizeof(char *));
            words->count = (int *) realloc(words->count, k * sizeof(int));
            words->mas[k - 1] = (char *) calloc(strlen(prev->key) + 1, sizeof(char));
            strcpy(words->mas[k - 1], prev->key);
            words->count[k - 1] = count;
            count = 0;
        }
    }
}

void show_words(Words *words) {
    int i, k = words->k;
    for (i = 0; i < k; i++) {
        printf("|Key %s| Count %d|\n", words->mas[i], words->count[i]);
    }
}

int insert(Tree *tree, char *key, char *info) {
    Node *par, *ptr = tree->root;
    if (!ptr) {
        ptr = node_new();
        ptr->key = key;
        ptr->info = info;
        tree->root = ptr;
        return 0;
    }
    //поиск целевого узла - par
    while (ptr) {
        par = ptr;
        if (strcmp(key, ptr->key) < 0) {
            ptr = ptr->left;
        } else if (strcmp(key, ptr->key) > 0) {
            ptr = ptr->right;
        } else if (strcmp(key, ptr->key) == 0) {
            do {
                par = ptr;
                ptr = ptr->right;
            } while (ptr && strcmp(key, ptr->key) == 0);
            break;
        }
    }
    //вставка нового элемента
    ptr = NULL;
    ptr = node_new();
    ptr->key = key;
    ptr->info = info;
    ptr->par = par;
    if (strcmp(key, par->key) < 0) {
        par->left = ptr;
    } else {
        if (par->right) {
            ptr->right = par->right;
            par->right->par = ptr;
        }
        par->right = ptr;
    }
    Node *prev;
    prev = find_prev(ptr);
    if (prev)
        prev->next = ptr;
    ptr->next = find_next(ptr);
    return 0;
}

int delete_node(Tree *tree, char *key, int num) {
    Node *x, *y, *p, *par, *next, *prev, *ptr = tree->root;
    //находим удаляемый элемент - x
    int k = -1;
    if (!ptr)
        return -1;
    while (ptr) {
        if (strcmp(key, ptr->key) < 0) {
            ptr = ptr->left;
        } else if (strcmp(key, ptr->key) > 0) {
            ptr = ptr->right;
        } else if (strcmp(key, ptr->key) == 0) {
            k = 1;
            while (k < num && ptr && strcmp(key, ptr->key) == 0) {
                ptr = ptr->next;
                k++;
            }
            break;
        }
    }

    if (k == num && ptr && strcmp(key, ptr->key) == 0) {
        x = ptr;
    } else return -1;
    //находим реально удаляемый элемент - y
    if (x->left == NULL || x->right == NULL) {
        y = x;
    } else y = find_next(x); //элемент следующий за x
    prev = find_prev(y);
    next = find_next(y);
    //находим поддерево и родительский узел для y
    if (y->left) {
        p = y->left;
    } else p = y->right;
    par = y->par;
    //переопределяем родительский узел для p
    if (p) {
        p->par = par;
    }
    //изменения для родительской вершины y
    if (!par) {
        tree->root = p;
    } else {
        if (par->left == y) {
            par->left = p;
        } else {
            par->right = p;
        }
    }
    //удаляем и копируем сами данные
    free(x->key);
    free(x->info);
    if (y != x) {
        x->key = y->key;
        x->info = y->info;
        x->next = find_next(x);
    } else {
        if (prev) {
            prev->next = next;
        }
    }
    free(y);
    return 0;
}

void show(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    ptr = find_min(ptr);
    while (ptr) {
        printf("|Key %s| Info %s|\n", ptr->key, ptr->info);
        ptr = ptr->next;
    }
    /*show(ptr->left);
    printf("|Key %s| Info %s|\n", ptr->key, ptr->info);
    show(ptr->right);*/
}

void format_show(Node *node, int space) {
    if (!node)
        return;
    int count = 2;
    space += count;
    format_show(node->right, space);
    for (int i = count; i < space; ++i)
        printf(" ");
    printf("%s\n", node->key);
    format_show(node->left, space);
}

void graphviz_show(Node *node) {
    Node *par, *ptr = node;
    char str;
    if (!ptr)
        return;
    par = ptr->par;
    if (par) {
        if (par->left == ptr) {
            str = 'L';
        } else str = 'R';
        printf("\"%s\"->\"%s\"[label = %c]\n",par->key, ptr->key, str);
    }
    graphviz_show(ptr->left);
    graphviz_show(ptr->right);
}

void show_founded(Address *address) {
    int i;
    Node *ptr;
    for (i = 0; i < address->k; i++) {
        ptr = address->mas[i];
        printf("|Key %s| Info %s|\n", ptr->key, ptr->info);
    }
}

void write_tree(FILE *file, Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    int len1, len2;
    len1 = strlen(ptr->key) + 1;
    len2 = strlen(ptr->info) + 1;
    fseek(file, 0, SEEK_END);
    fwrite(&len1, sizeof(int), 1, file);
    fwrite(&len2, sizeof(int), 1, file);
    fwrite(ptr->key, sizeof(char), len1, file);
    fwrite(ptr->info, sizeof(char), len2, file);

    write_tree(file, ptr->left);
    write_tree(file, ptr->right);
}

int file_write(char *name, Tree *tree) {
    FILE *file = fopen(name, "w+b");
    if (!file)
        return -1;
    if (!tree->root) {
        fclose(file);
        return -2;
    }
    write_tree(file, tree->root);
    fclose(file);
    return 0;
}

int file_read(char *name, Tree *tree) {
    FILE *file = fopen(name, "r+b");
    if (!file)
        return -1;
    int len1, len2;
    char *key, *info;
    while (fread(&len1, sizeof(int), 1, file)) {
        if (!fread(&len2, sizeof(int), 1, file))
            break;
        key = (char *) calloc(len1, sizeof(char));
        info = (char *) calloc(len2, sizeof(char));
        if (!fread(key, sizeof(char), len1, file)) {
            free(key);
            free(info);
        }
        if (!fread(info, sizeof(char), len2, file)) {
            free(key);
            free(info);
        }
        insert(tree, key, info);
        key = NULL;
        info = NULL;
    }
    fclose(file);
    return 0;
}

int make_words_and_insert_in_tree(Tree *tree, char *str) {
    if (!str)
        return -1;
    int len, i, num;
    char *ptr = str;
    char pt[] = " \t";
    char *word, *info;
    puts(str);

    for (i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] != '\0'))
            str[i] = ' ';
    }

    do {
        num = strspn (ptr, pt);
        ptr += num;
        if (*ptr != '\0') {
            info = (char *) calloc(1,sizeof(char));
            info[0] = '\0';
            len = strcspn (ptr, pt);
            word = (char *) calloc(len + 1, sizeof(char));
            strncpy(word, ptr, len);
            word[len] = '\0';
            ptr += len;
            insert(tree, word, info);
        }
    } while (*ptr != '\0');
    return 0;
}

void delete_tree(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    delete_tree(ptr->left);
    delete_tree(ptr->right);
    free(ptr->info);
    free(ptr->key);
    free(ptr);
}

void delete_words(Words *words) {
    for (int i = 0; i < words->k; i++) {
        free(words->mas[i]);
    }
    if (words->k > 0) {
        free(words->mas);
        free(words->count);
    }
    words->mas = NULL;
    words->count = NULL;
    words->k = 0;
}
