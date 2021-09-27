#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "tree.h"
void swap_keys(unsigned int *a, unsigned int *b) {
    unsigned int c = *a;
    *a = *b;
    *b = c;
}

void swap_info(Info *a, Info *b) {
    Info c = *a;
    *a = *b;
    *b = c;
}

void sort_2(unsigned int *a, unsigned int *b, Info *x, Info *y) {
    if (*a > *b) {
        swap_keys(a, b);
        swap_info(x, y);
    }
}

void sort_3(unsigned int *a, unsigned int *b, unsigned int *c, Info *x, Info *y, Info *z) {
    sort_2(a, b, x, y);
    sort_2(a, c, x, z);
    sort_2(b, c, y, z);
}

void sort_keys(Node *node) {
    if (!node) return;
    int size = node->size;
    if (size == 1) return;
    if (size == 2) sort_2(&(node->key[0]), &(node->key[1]), node->info[0], node->info[1]);
    if (size == 3) {
        sort_3(&(node->key[0]), &(node->key[1]), &(node->key[2]),
                node->info[0], node->info[1], node->info[2]);
    }
}

int is_leaf(Node *node) {
    if (!node) return -1;
    if (node->first || node->second || node->third) {
        return 0;
    } else return 1;
}

Node *new_node(unsigned int k, Info *info) { //при создании узла сразу вставляем в него информацию
    Node *ptr = (Node *) calloc(1, sizeof(Node));
    ptr->first = NULL;
    ptr->second = NULL;
    ptr->third = NULL;
    ptr->fourth = NULL;
    ptr->par = NULL;
    ptr->key[0] = k;
    ptr->info[0] = info;
    ptr->info[1] = NULL;
    ptr->size = 1;
    return ptr;
}

void insert_to_node(Node *node, unsigned int k, Info *info) { // Вставляем ключ k в вершину (не в дерево)
    node->key[node->size] = k;
    node->info[node->size] = info;
    node->size++;
    sort_keys(node);
}

void become_node1(Node *node, unsigned int k, Info *info, Node *x, Node *y) {  // Преобразовать в вершину c 1 ключом
    node->key[0] = k;
    node->info[0] = info;
    node->first = x;
    node->second = y;
    node->third = NULL;
    node->fourth = NULL;
    node->par = NULL;
    node->size = 1;
}

Node *split(Node *item) { //разбиение узла
    if (item->size < 3) return item;
    // Создаем две новые вершины, которые имеют такого же родителя, как и разделяющийся элемент
    Node *x = new_node(item->key[0], item->info[0]);
    x->first = item->first;
    x->second = item->second;
    x->par = item->par;

    Node *y = new_node(item->key[2], item->info[2]);
    y->first = item->third;
    y->second = item->fourth;
    y->par = item->par;

    //переставляем указатели на родителей
    if (x->first)  x->first->par = x;
    if (x->second) x->second->par = x;
    if (y->first)  y->first->par = y;
    if (y->second) y->second->par = y;
    if (item->par) {
        insert_to_node(item->par, item->key[1], item->info[1]);

        if (item->par->first == item) item->par->first = NULL;
        else if (item->par->second == item) item->par->second = NULL;
        else if (item->par->third == item) item->par->third = NULL;

        //сортировка указателей в родительском для item узле
        if (item->par->first == NULL) {
            item->par->fourth = item->par->third;
            item->par->third = item->par->second;
            item->par->second = y;
            item->par->first = x;
        } else if (item->par->second == NULL) {
            item->par->fourth = item->par->third;
            item->par->third = y;
            item->par->second = x;
        } else if (item->par->third == NULL) {
            item->par->fourth = y;
            item->par->third = x;
        }

        Node *tmp = item->par;
        free(item);
        return tmp;
    } else {
        x->par = item;   // Так как в эту ветку попадает только корень,
        y->par = item;   // то мы "родителем" новых вершин делаем разделяющийся элемент.
        become_node1(item, item->key[1], item->info[1], x, y);
        return item;
    }
}

Node *insert(Node *ptr, unsigned int k, Info *info) {
    if (!ptr) return new_node(k, info); // если дерево пусто, создаем корень
    info->next = NULL;
    Info *p;
    if (k == ptr->key[0]) {
        p = ptr->info[0];
        while (p && p->next) {
            p = p->next;
        }
        p->next = info;
    } else if (ptr->size == 2 && k == ptr->key[1]) {
        p = ptr->info[1];
        while (p && p->next) {
            p = p->next;
        }
        p->next = info;
    } else if (is_leaf(ptr) == 1) {
        insert_to_node(ptr, k, info);
    } else if (k < ptr->key[0]) {
        insert(ptr->first, k, info);
    } else if ((ptr->size == 1 && k > ptr->key[0]) || (ptr->size == 2 && k > ptr->key[0] && k < ptr->key[1])) {
        insert(ptr->second, k, info);
    } else if (ptr->size == 2 && k > ptr->key[1]) {
        insert(ptr->third, k, info);
    }

    return split(ptr);
}
Node *search(Node *ptr, unsigned int k) {
    if (!ptr) return NULL;
    if (ptr->key[0] == k || (ptr->size == 2 && ptr->key[1] == k))
        return ptr;
    if (k < ptr->key[0]) {
        return search(ptr->first, k);
    } else if ((ptr->size == 1 && k > ptr->key[0]) || (ptr->size == 2 && k > ptr->key[0] && k < ptr->key[1])) {
        return search(ptr->second, k);
    } else if (ptr->size == 2 && k > ptr->key[1]) {
        return search(ptr->third, k);
    }
    return NULL;
}
Node *search_min(Node *ptr) { // Поиск узла с минимальным ключом в поддереве с корнем p
    if (!ptr) return ptr;
    if (!(ptr->first)) {
        return ptr;
    } else return search_min(ptr->first);
}

void remove_from_node(Node *ptr, unsigned int k, int status) {
    Info *info, *prev = NULL;
    if (ptr->size >= 1 && k == ptr->key[0]) {
        ptr->key[0] = ptr->key[1];
        if (status == 1) {
            info = ptr->info[0];
            while(info) {
                prev = info;
                info = info->next;
                free(prev->str);
                free(prev);
            }
        }
        ptr->info[0] = ptr->info[1];
        ptr->info[1] = NULL;
        ptr->size--;
    } else if (ptr->size == 2 && k == ptr->key[1]) {
        if (status == 1) {
            info = ptr->info[1];
            while(info) {
                prev = info;
                info = info->next;
                free(prev->str);
                free(prev);
            }
        }
        ptr->info[1] = NULL;
        ptr->size--;
    }
}

Node *redistribute(Node *leaf) {    //перераспределение
    Node *parent = leaf->par;
    Node *first = parent->first;
    Node *second = parent->second;
    Node *third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = NULL;
            insert_to_node(parent->first, parent->key[0], parent->info[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != NULL) parent->first->first = leaf->first;
            else if (leaf->second != NULL) parent->first->first = leaf->second;

            if (parent->first->first != NULL) parent->first->first->par = parent->first;

            remove_from_node(parent, parent->key[0], 0); //не нужно удалять информацию
            free(first);
        } else if (second == leaf) {
            insert_to_node(first, parent->key[0], parent->info[0]);
            remove_from_node(parent, parent->key[0], 0);
            if (leaf->first != NULL) first->third = leaf->first;
            else if (leaf->second != NULL) first->third = leaf->second;

            if (first->third != NULL) first->third->par = first;

            parent->second = parent->third;
            parent->third = NULL;
            free(second);
        } else if (third == leaf) {
            insert_to_node(second, parent->key[1], parent->info[1]);
            parent->third = NULL;
            remove_from_node(parent, parent->key[1], 0);
            if (leaf->first != NULL) second->third = leaf->first;
            else if (leaf->second != NULL) second->third = leaf->second;

            if (second->third != NULL)  second->third->par = second;

            free(third);
        }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first != NULL) {
                leaf->second = leaf->first;
                leaf->first = NULL;
            }

            insert_to_node(leaf, parent->key[1], parent->info[1]);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                parent->info[1] = second->info[1];
                remove_from_node(second, second->key[1], 0);
                leaf->first = second->third;
                second->third = NULL;
                if (leaf->first != NULL) leaf->first->par = leaf;
            } else if (first->size == 2) {
                parent->key[1] = second->key[0];
                parent->info[1] = second->info[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != NULL) leaf->first->par = leaf;

                second->key[0] = parent->key[0];
                second->info[0] = parent->info[0];
                parent->key[0] = first->key[1];
                parent->info[0] = first->info[1];
                remove_from_node(first, first->key[1], 0);
                second->first = first->third;
                if (second->first != NULL) second->first->par = second;
                first->third = NULL;
            }
        } else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->first == NULL) {
                    leaf->first = leaf->second;
                    leaf->second = NULL;
                }
                insert_to_node(second, parent->key[1], parent->info[1]);
                parent->key[1] = third->key[0];
                parent->info[1] = third->info[0];
                remove_from_node(third, third->key[0], 0);
                second->second = third->first;
                if (second->second != NULL) second->second->par = second;
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            } else if (first->size == 2) {
                if (leaf->second == NULL) {
                    leaf->second = leaf->first;
                    leaf->first = NULL;
                }
                insert_to_node(second, parent->key[0], parent->info[0]);
                parent->key[0] = first->key[1];
                parent->info[0] = first->info[1];
                remove_from_node(first, first->key[1], 0);
                second->first = first->third;
                if (second->first != NULL) second->first->par = second;
                first->third = NULL;
            }
        } else if (first == leaf) {
            if (leaf->first == NULL) {
                leaf->first = leaf->second;
                leaf->second = NULL;
            }
            insert_to_node(first, parent->key[0], parent->info[0]);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                parent->info[0] = second->info[0];
                remove_from_node(second, second->key[0], 0);
                first->second = second->first;
                if (first->second != NULL) first->second->par = first;
                second->first = second->second;
                second->second = second->third;
                second->third = NULL;
            } else if (third->size == 2) {
                parent->key[0] = second->key[0];
                parent->info[0] = second->info[0];
                second->key[0] = parent->key[1];
                second->info[0] = parent->info[1];
                parent->key[1] = third->key[0];
                parent->info[1] = third->info[0];
                remove_from_node(third, third->key[0], 0);
                first->second = second->first;
                if (first->second != NULL) first->second->par = first;
                second->first = second->second;
                second->second = third->first;
                if (second->second != NULL) second->second->par = second;
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
        }
    } else if (parent->size == 1) {
        insert_to_node(leaf, parent->key[0], parent->info[0]);
        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            parent->info[0] = second->info[0];
            remove_from_node(second, second->key[0], 0);

            if (leaf->first == NULL) leaf->first = leaf->second;

            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = NULL;
            if (leaf->second != NULL) leaf->second->par = leaf;
        } else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            parent->info[0] = first->info[1];
            remove_from_node(first, first->key[1], 0);

            if (leaf->second == NULL) leaf->second = leaf->first;

            leaf->first = first->third;
            first->third = NULL;
            if (leaf->first != NULL) leaf->first->par = leaf;
        }
    }
    return parent;
}

Node *merge(Node *leaf) {   //склеивание
    Node *parent = leaf->par;

    if (parent->first == leaf) {
        insert_to_node(parent->second, parent->key[0], parent->info[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != NULL) parent->second->first = leaf->first;
        else if (leaf->second != NULL) parent->second->first = leaf->second;

        if (parent->second->first != NULL) parent->second->first->par = parent->second;

        remove_from_node(parent, parent->key[0], 0);
        free(parent->first);
        parent->first = NULL;
    } else if (parent->second == leaf) {
        insert_to_node(parent->first, parent->key[0], parent->info[0]);

        if (leaf->first != NULL) parent->first->third = leaf->first;
        else if (leaf->second != NULL) parent->first->third = leaf->second;

        if (parent->first->third != NULL) parent->first->third->par = parent->first;

        remove_from_node(parent, parent->key[0], 0);
        free(parent->second);
        parent->second = NULL;
    }

    if (parent->par == NULL) {
        Node *tmp = NULL;
        if (parent->first != NULL) tmp = parent->first;
        else tmp = parent->second;
        tmp->par = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}

Node *fix(Node *leaf) {
    if (leaf->size == 0 && leaf->par == NULL) { // Случай 0, удаляем корень дерева
        free(leaf);
        leaf = NULL;
        return NULL;
    }
    if (leaf->size != 0) { // Случай 1, когда вершина, в которой удалили ключ, имела два ключа
        if (leaf->par) {
            return fix(leaf->par);
        } else return leaf;   //В итоге будет возвращен корень
    }

    Node *parent = leaf->par;  //Размер удаляемого листа = 0
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) {
        leaf = redistribute(leaf); // Случай 2, у братьев есть 2 ключа -> перераспределяем ключи в дереве
    } else leaf = merge(leaf); // Случай 3, когда нужно произвести склеивание и пройтись вверх по дереву

    return fix(leaf);
}

Node *remove_tree(Node *ptr, unsigned int k) { // Удаление ключа k в 2-3-дереве с корнем p
    Node *node = search(ptr, k); // Ищем узел, где находится ключ k
    if (!node) {
        puts("Element wasn't found");
        return ptr; //элемент не найден, корень не меняется
    }
    Info *info;
    if (k == node->key[0]) {
        info = node->info[0];
        if (info->next) {
            node->info[0] = info->next;
            free(info->str);
            free(info);
            return ptr;
        }
    } else {
        info = node->info[1];
        if (info->next) {
            node->info[1] = info->next;
            free(info->str);
            free(info);
            return ptr;
        }
    }


    Node *min = NULL;
    if (node->key[0] == k) {
        min = search_min(node->second); // ищем жертву из "правого" поддерева
    } else min = search_min(node->third);

    if (min) { // Меняем ключи местами
        if (k == node->key[0]) {
            swap_keys(&(node->key[0]), &(min->key[0]));
            swap_info(node->info[0], min->info[0]);
        } else {
            swap_keys(&(node->key[1]), &(min->key[0]));
            swap_info(node->info[1], min->info[0]);
        }
        node = min; // Перемещаем указатель на лист
    }

    remove_from_node(node, k, 1); // Удаляем требуемый ключ вместе с информацией из листа
    return fix(node); // Вызываем функцию для восстановления свойств дерева
}

Info *find(Node *ptr, unsigned int k) {
    Info *found_info = NULL;
    if (!ptr) return NULL;
    if (k == ptr->key[0]) {
        found_info = ptr->info[0];
    } else if (ptr->size == 2 && k == ptr->key[1]) {
        found_info = ptr->info[1];
    } else if (k < ptr->key[0]) {
        found_info = find(ptr->first, k);
    } else if ((ptr->size == 1 && k > ptr->key[0]) || (ptr->size == 2 && k > ptr->key[0] && k < ptr->key[1])) {
        found_info = find(ptr->second, k);
    } else if (ptr->size == 2 && k > ptr->key[1]) {
        found_info = find(ptr->third, k);
    }
    return found_info;
}

void find_near(Node *ptr, unsigned int k, Near *near, unsigned int *dist) {
    if (!ptr) return;
    if (k == ptr->key[0]) {
        if (ptr->size == 2) {
            if (abs(ptr->key[1] - k) < *dist) {
                near->key = ptr->key[1];
                near->info = ptr->info[1];
                if (near->key > k) {
                    *dist = near->key - k;
                } else *dist = k - near->key;
            }
            find_near(ptr->third, k, near, dist);
        }
        find_near(ptr->first, k, near, dist);
        find_near(ptr->second, k, near, dist);
    } else if (ptr->size == 2 && k == ptr->key[1]) {
        if (abs(ptr->key[0] - k) < *dist) {
            near->key = ptr->key[0];
            near->info = ptr->info[0];
            if (near->key > k) {
                *dist = near->key - k;
            } else *dist = k - near->key;
        }
        find_near(ptr->first, k, near, dist);
        find_near(ptr->second, k, near, dist);
        find_near(ptr->third, k, near, dist);
    } else if (k < ptr->key[0]) {
        if (ptr->key[0] - k < *dist) {
            near->key = ptr->key[0];
            near->info = ptr->info[0];
            if (near->key > k) {
                *dist = near->key - k;
            } else *dist = k - near->key;
        }
        find_near(ptr->first, k, near, dist);
    } else if ((ptr->size == 1 && k > ptr->key[0]) || (ptr->size == 2 && k > ptr->key[0] && k < ptr->key[1])) {
        if (ptr->size == 1) {
            if (k - ptr->key[0] < *dist) {
                near->key = ptr->key[0];
                near->info = ptr->info[0];
                if (near->key > k) {
                    *dist = near->key - k;
                } else *dist = k - near->key;
            }
        } else if (ptr->size == 2) {
            if (k - ptr->key[0] < *dist) {
                near->key = ptr->key[0];
                near->info = ptr->info[0];
                if (near->key > k) {
                    *dist = near->key - k;
                } else *dist = k - near->key;
            }
            if (ptr->key[1] - k < *dist) {
                near->key = ptr->key[1];
                near->info = ptr->info[1];
                if (near->key > k) {
                    *dist = near->key - k;
                } else *dist = k - near->key;
            }
        }
        find_near(ptr->second, k, near, dist);
    } else if (ptr->size == 2 && k > ptr->key[1]) {
        if (k - ptr->key[1] < *dist) {
            near->key = ptr->key[1];
            near->info = ptr->info[1];
            if (near->key > k) {
                *dist = near->key - k;
            } else *dist = k - near->key;
        }
        find_near(ptr->third, k, near, dist);
    }
}

void show(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    show(ptr->first);
    Info *info;
    info = ptr->info[0];
    while (info) {
        printf("|Key %u| Info %f %s|\n", ptr->key[0], info->f, info->str);
        info = info->next;
    }
    show(ptr->second);
    if (ptr->size > 1) {
        info = ptr->info[1];
        while (info) {
            printf("|Key %u| Info %f %s|\n", ptr->key[1], info->f, info->str);
            info = info->next;
        }
        show(ptr->third);
    }
}

void graphviz_show(Node *node) {
    Node *par, *ptr = node;
    if (!ptr)
        return;
    char str;
    par = ptr->par;
    if (par) {
        if (par->first == ptr) {
            str = '1';
        } else if (par->second == ptr) {
            str = '2';
        } else str = '3';

        if (par->size == 1) {
            if (ptr->size == 1) {
                printf("\"%u\"->\"%u\"[label = %c]\n",par->key[0], ptr->key[0], str);
            } else {
                printf("\"%u\"->\"%u|%u\"[label = %c]\n",par->key[0], ptr->key[0], ptr->key[1], str);
            }
        } else {
            if (ptr->size == 1) {
                printf("\"%u|%u\"->\"%u\"[label = %c]\n",par->key[0], par->key[1], ptr->key[0], str);
            } else {
                printf("\"%u|%u\"->\"%u|%u\"[label = %c]\n",par->key[0], par->key[1], ptr->key[0], ptr->key[1], str);
            }
        }
    } else {
        if (ptr->size == 1) {
            printf("\"%u\"\n", ptr->key[0]);
        } else {
            printf("\"%u|%u\"\n", ptr->key[0], ptr->key[1]);
        }
    }
    graphviz_show(ptr->first);
    graphviz_show(ptr->second);
    graphviz_show(ptr->third);
}

void format_show(Node *node, int space) {
    if (!node)
        return;
    if (node->size == 1 ) {
        space += 3;
        format_show(node->second, space);
        for (int i = 3; i < space; ++i)
            printf(" ");
        printf("|%u|\n", node->key[0]);
        format_show(node->first, space);
    } else {
        space += 5;
        format_show(node->third, space);
        for (int i = 5; i < space; ++i)
            printf(" ");
        printf("|%u|%u|\n",node->key[0], node->key[1]);
        format_show(node->second, space);
        format_show(node->first, space);
    }
}

void show_range_direct(Node *node, unsigned int a, unsigned int b) {
    Node *ptr = node;
    if (!ptr)
        return;
    show_range_direct(ptr->first, a, b);
    Info *info;
    if (ptr->key[0] >= a && ptr->key[0] <= b) {
        info = ptr->info[0];
        while (info) {
            printf("|Key %u| Info %f %s|\n", ptr->key[0], info->f, info->str);
            info = info->next;
        }
    }
    show_range_direct(ptr->second, a, b);
    if (ptr->size > 1) {
        if (ptr->key[1] >= a && ptr->key[1] <= b) {
            info = ptr->info[1];
            while (info) {
                printf("|Key %u| Info %f %s|\n", ptr->key[1], info->f, info->str);
                info = info->next;
            }
        }
        show_range_direct(ptr->third, a, b);
    }
}

void show_range_reverse(Node *node, unsigned int a, unsigned int b) {
    Node *ptr = node;
    if (!ptr)
        return;
    Info *info;
    if (ptr->size > 1) {
        show_range_reverse(ptr->third, a, b);
        if (ptr->key[1] <= a && ptr->key[1] >= b) {
            info = ptr->info[1];
            while (info) {
                printf("|Key %u| Info %f %s|\n", ptr->key[1], info->f, info->str);
                info = info->next;
            }
        }

    }
    show_range_reverse(ptr->second, a, b);
    if (ptr->key[0] <= a && ptr->key[0] >= b) {
        info = ptr->info[0];
        while (info) {
            printf("|Key %u| Info %f %s|\n", ptr->key[0], info->f, info->str);
            info = info->next;
        }
    }
    show_range_reverse(ptr->first, a, b);
}

void write_tree(FILE *file, Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    int str_len;
    Info *info;
    write_tree(file, ptr->first);
    fseek(file, 0, SEEK_END);
    info = ptr->info[0];
    while (info) {
        str_len = strlen(info->str) + 1;
        fwrite(&(ptr->key[0]), sizeof(unsigned int), 1, file);
        fwrite(&(info->f), sizeof(float), 1, file);
        fwrite(&str_len, sizeof(int), 1, file);
        fwrite(info->str, sizeof(char), str_len, file);
        info = info->next;
    }
    write_tree(file, ptr->second);
    if (ptr->size > 1) {
        fseek(file, 0, SEEK_END);
        info = ptr->info[1];
        while (info) {
            str_len = strlen(info->str) + 1;
            fwrite(&(ptr->key[1]), sizeof(unsigned int), 1, file);
            fwrite(&(info->f), sizeof(float), 1, file);
            fwrite(&str_len, sizeof(int), 1, file);
            fwrite(info->str, sizeof(char), str_len, file);
            info = info->next;
        }
    }
    write_tree(file, ptr->third);
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
    int str_len;
    unsigned int key;
    float f;
    char *str = NULL;
    Info *info = NULL;
    while (fread(&key, sizeof(unsigned int), 1, file)) {
        if (!fread(&f, sizeof(float), 1, file))
            break;
        if (!fread(&str_len, sizeof(int), 1, file))
            break;
        str = (char *) calloc(str_len, sizeof(char));
        if (!fread(str, sizeof(char), str_len, file)) {
            free(str);
        }
        if (str) {
            info = (Info *) calloc(1, sizeof(Info));
            info->f = f;
            info->str = str;
            info->next = NULL;
            tree->root = insert(tree->root, key, info);
        }
        str = NULL;
        info = NULL;
    }
    fclose(file);
    return 0;
}

void delete_tree(Node *node) {
    Node *ptr = node;
    if (!ptr)
        return;
    delete_tree(ptr->first);
    Info *info, *prev;
    info = ptr->info[0];
    while (info) {
        free(info->str);
        prev = info;
        info = info->next;
        free(prev);
    }
    delete_tree(ptr->second);
    if (ptr->size > 1) {
        info = ptr->info[1];
        while (info) {
            free(info->str);
            prev = info;
            info = info->next;
            free(prev);
        }
    }
    delete_tree(ptr->third);
    free(ptr);
    node = NULL;
}
