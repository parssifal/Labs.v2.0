#include <iostream>
#include "Buth_Lemn.h"

using namespace std;
using namespace Prog2;

int main() {
    int h;
    double t;
    Buth_Lemn l;
    char s = NULL;
    do {
        cout << "0. Exit" << endl;
        cout << "1. Create lemniskate" << endl;
        cout << "2. Change parameters of lemniskate" << endl;
        cout << "3. Get area of lemniskate" << endl;
        cout << "4. Get type of lemniskate" << endl;
        cout << "5. Get parameters of lemniskate in polar coordinates" << endl;
        cout << "6. Get distance" << endl;
        cout << "7. Get text form of lemniskate" << endl;

        h = get_int();
        switch (h) {
        case 0:
            cout << "***Exit***" << endl;
            break;

        case 1:
            cout << "***Create lemniskate***" << endl;
            if (create(l) == 1) return 1;
            break;

        case 2:
            std::cout << "***Change parameters of lemniskate***" << endl;
            if (change_parameters(l) == 1) return 1;
            break;

        case 3:
            cout << "***Get area of lemniskate***" << endl;
            double area = l.area(c, m);
            cout << "Your area is :" << area << endl;
            break;

        case 4:
            cout << "***Get type of lemniskate***" << endl;
            int type = l.type(c, m);
            if (type == 0) {
                cout << "Your lemniskate is elleptic." << endl;
            }
            else {
                cout << "Your lemniskate is hyperbolic." << endl;
            }
            break;

        case 5:
            cout << "***Get parameters of lemniskate in polar coordinates***" << endl;
            l.parametrs(c, m);
            break;

        case 6:
            cout << "***Get distance***" << endl;
            double dist = l.distance(l.c, l.m);
            cout <<"Your distnace is :" << dist << endl;
            break;

        case 7:
            cout << "***Get text form of lemniskate***" << endl;
            s* = l.frm();
            cout << "Text version of your lemniskate" << endl;
            cout << s << endl;
            break;

        default:
            cout << "You are wrong! Try again" << endl;
            break;
        }
    } while (h != 0);
    return 0;
}