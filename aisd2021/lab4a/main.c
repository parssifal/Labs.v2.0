#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dialog.h"
#include "func.h"

const char *MSGS[] = {"0. Quit", "1. Add new element", "2. Delete element", "3. Find elements",
"4. Show the tree", "5. Find element with smallest key", "6. Show the tree in beautiful style",
"7. Add new elements with random", "8. Write tree in file", "9. Read tree from file",
"10. Delete tree", "11. Use graphviz", "12. Find count of words in file input.txt"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main()  {
    int a, j;
    Tree tree;
    tree.root = NULL;
    Address address;
    Words words;
    words.k = 0;
    do {
        a = dialog(MSGS, MSGS_SIZE);
        switch(a) {
            case 0:
                puts("***Quit***");
                break;
            case 1:
                puts("***Add new element***");
                D_add(&tree);
                break;
            case 2:
                puts("***Delete element***");
                D_delete(&tree);
                break;
            case 3:
                puts("***Find elements***");
                address.k = 0;
                j = D_find(&tree, &address);
                if (j == 0) {
                    show_founded(&address);
                    free(address.mas);
                }
                break;
            case 4:
                puts("***Show the tree***");
                if (tree.root) {
                    show(tree.root);
                } else puts("Nothing to show. Tree is empty");
                break;
            case 5:
                puts("***Find elements with smallest key***");
                address.k = 0;
                j = D_find_min(&tree, &address);
                if (j == 0) {
                    show_founded(&address);
                    free(address.mas);
                }
                break;
            case 6:
                puts("***Show the tree in beautiful style***");
                if (tree.root) {
                    puts("___________________________________");
                    format_show(tree.root, 0);
                    puts("___________________________________");
                } else puts("Nothing to show. Tree is empty");
                break;
            case 7:
                puts("***Add new elements with random***");
                D_add_random(&tree);
                break;
            case 8:
                puts("***Write tree in file***");
                D_write_file(&tree);
                break;
            case 9:
                puts("***Read tree from file***");
                D_read_file(&tree);
                break;
            case 10:
                puts("***Delete tree***");
                delete_tree(tree.root);
                tree.root = NULL;
                break;
            case 11:
                puts("***Use graphviz***");
                if (tree.root) {
                    puts("digraph G {");
                    graphviz_show(tree.root);
                    puts("}");
                } else puts("Nothing to show. Tree is empty");
                break;
            case 12:
                puts("***Find count of words in file input.txt***");
                FILE *file = fopen("input.txt","rt");
                if (!file) {
                    puts("File doesn't exist or can't be opened");
                } else {
                    char *str = NULL;
                    int z = 0;
                    do {
                        str = file_str(file);
                        if (str) {
                            z = 1;
                            make_words_and_insert_in_tree(&tree, str);
                            free(str);
                        }
                    } while (str);
                    if (!z) puts("File is empty");
                    fclose(file);
                    if (tree.root) {
                        delete_words(&words);
                        find_count_of_words(&tree, &words);
                        show_words(&words);
                    } else puts("Nothing to show. Tree is empty");
                }
                break;
        }
    } while (a != 0);
    delete_tree(tree.root);
    delete_words(&words);
    return 0;
}
