//#include "stdafx.h"
#include <iostream>
#include "C:\Users\Артур\source\repos\oop2021\lab2\Buth_Lemn.h"

using namespace std;
using namespace Prog2;

int _tmain(int argc, _TCHAR* argv[]) {
	Buth_Lemn l(3, 1);
	int fl1 = 1;
	double r;
	char* s = NULL;
	while (fl1) {
		cout << "Your lemniskata is:" << endl;
		s = l.frm();
		cout << s << endl;
		delete[] s;
		cout << "area: " << l.area() << endl;
		cout << "type: " << l.type() << endl;
		cout << "parametrs: " << l.parametrs() << endl;
		cout << "distance: " << l.distance() << endl;
		int fl2 = 1;
		while (fl2) {
			cout << "Enter x for calculate value y(x) or precc ctrl+Z to quit:" << endl;
			double x;
			cin >> x;
			fl2 = cin.good();
			if (!fl2)
				continue;
			try {
				y = c.f(x);
				cout << "y1 = " << y.x << ", y2 = " << y.y << endl;
			}
				catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		cin.clear();
		cout << "Enter new x, y and r to continue or press ctrl+Z to quit:" << endl;
		cin >> p.x >> p.y >> r;
		if (cin.good()) {
			c.setP(p);
			try {
				c.setR(r);
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		else
			fl1 = 0;
	}
	return 0;
}
