#include <iostream>
#include "C:\Users\Артур\source\repos\Labs.v2.0\oop2021\lab3\table.h"

using namespace std;

int main() {
    int c, key;
    char str[1000];
    Table* t = nullptr;
    do {
        cout << "0. Exit" << endl;
        cout << "1. Create default table" << endl;
        cout << "2. Create table and initialize k elements" << endl;
        cout << "3. Find element by key" << endl;
        cout << "4. Add new element" << endl;
        cout << "5. Delete element by key" << endl;
        cout << "6. Modify info of element by key" << endl;
        cout << "7. Show table" << endl;

        c = get_int();
        switch (c) {
        case 0:
            cout << "***Exit***" << endl;
            break;

        case 1:
            cout << "***Create default table***" << endl;
            delete t;
            t = new Table;
            break;

        case 2:
            cout << "***Create table and initialize k elements***" << endl;
            int k;
            cout << "Enter k:" << endl;
            k = get_int();
            Item* items;
            items = new Item[k];
            int count;
            count = k;
            try {

            }
            catch (const char* msg) {
                cerr << msg << endl;
                delete[] items;
                break;
            }
            if (k < count) cout << "Not all data were added" << endl;
            delete t;
            try {
                t = new Table(items, k);
            }
            catch (const char* msg) {
                cerr << msg << endl;
                delete[] items;
                break;
            }
            delete[] items;
            break;

        case 3:
            cout << "***Find element by key***" << endl;
            if (!t) {
                cout << "Table is empty" << endl;
                break;
            }
            t->find_and_show();
            break;

        case 4:
            cout << "***Add new element***" << endl;
            if (!t)
                t = new Table;
            cout << "Enter key:" << endl;
            key = get_int();
            cout << "Enter info:" << endl;
            cin >> str;
            try {
                t->add(key, str);
            }
            catch (const char* msg) {
                cerr << msg << endl;
                break;
            }
            break;

        case 5:
            cout << "***Delete element by key***" << endl;
            if (!t) {
                cout << "Table is empty" << endl;
                break;
            }
            cout << "Enter key:" << endl;
            key = get_int();
            try {
                t->delete_by_key(key);
            }
            catch (const char* msg) {
                cerr << msg << endl;
                break;
            }
            break;

        case 6:
            cout << "***Modify info of element by key***" << endl;
            if (!t) {
                cout << "Table is empty" << endl;
                break;
            }
            cout << "Enter key:" << endl;
            key = get_int();
            cout << "Enter new info:" << endl;
            cin >> str;
            try {
                t->modify(key, str);
            }
            catch (const char* msg) {
                cerr << msg << endl;
                break;
            }
            break;

        case 7:
            cout << "***Show table***" << endl;
            if (!t) {
                cout << "Table is empty" << endl;
                break;
            }
            try {

            }
            catch (const char* msg) {
                cerr << msg << endl;
                break;
            }
            break;

        default:
            cout << "You are wrong! Try again" << endl;
            break;
        }
    } while (c != 0);
    delete t;
    return 0;
}