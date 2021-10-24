#include <strstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include "C:\Users\Артур\source\repos\lab2\Buth_Lemn.h"

using namespace std;

namespace Prog2 {
	double type(double c, double m) {       //Определяет
		int i;                          //тип кривой
		if (c > 2 * m * m) return i = 0;//elleptic
		if (c < 2 * m * m) return i = 1;//hyperbolic
	}

	double parametrs(double c, double m) {          //Определяет
		if (type(c, m) == 0) {//e               //параметры
			double a2 = 2 * m * m + c;      //для полярного
			double b2 = 2 * m * m + c;
			cout << "a = " << a2 << endl;   //уравнения
			cout << "b = " << b2 << endl;
		}                                       //зависящие
		else if (type(c, m) == 1) {//h          //от типа
			double a22 = 2 * m * m + c;      //кривой
			double b22 = 2 * m * m - c;
			cout << "a = " << a22 << endl;
			cout << "b = " << b22 << endl;
		}
	}

	double area(double c, double m) {//Вычисляет площадь
		if (type(c, m) == 0) {
			return 3.14159 * ((2 * m * m + c) + (2 * m * m + c)) / 2;
		}
		else if (type(c, m) == 1) {
			return ((2 * m * m + c) - (2 * m * m - c)) * (atan(sqrt((2 * m * m + c) / (2 * m * m - c)))) / 2 + (sqrt((2 * m * m + c) * (2 * m * m - c))) / 2;
		}
	}

	double distance(double c, double m, double phi) {
		if (type(c, m) == 0) {
			double a2 = 2 * m * m + c;
			double b2 = 2 * m * m + c;
			double p = pow(a2 * cos(phi), 2) + pow(b2 * sin(phi), 2);
			return p;
		}
		else if (type(c, m) == 1) {
			double a22 = 2 * m * m + c;
			double b22 = 2 * m * m - c;
			double p = pow(a22 * cos(phi), 2) + pow(b22 * sin(phi), 2);
			p = sqrt(p);
			return p;
		}
	}

	char* Prog2::Buth_Lemn::frm(int type) const { //формула лемнискаты Бута
		int i = type;
		if (i == 0) {
			const char* s1 = "(x^2 + y^2)^2 = (2* ^2 + )^2 * x^2 + ( - 2* ^2) * y^2\n";
			int l1 = strlen(s1) + 1;
			size_t Size = 20;
			char num[20];
			sprintf_s(num, 20, "%.2f", c);
			l1 += strlen(num);
			sprintf_s(num, 20, "%.2f", m);
			l1 += strlen(num);
			char* sr1 = new char[l1];
			sprintf_s(sr1, l1, "(x^2 + y^2)^2 = (2* ^2 + %.2f)^2 * x^2 + (%.2f - 2* ^2) * y^2\n", c, c);
			int k = strlen(sr1);
			sprintf_s(sr1 + k, l1 - k, "(x^2 + y^2)^2 = (2*%.2f^2 + )^2 * x^2 + ( - 2*%.2f^2) * y^2\n", m, m);
			k = strlen(sr1);
			return sr1;
		}
		else if (i == 1) {
			const char* s2 = "(x^2 + y^2)^2 = (2* ^2 + )^2 * x^2 - (2* ^2 - ) * y^2\n";
			int l2 = strlen(s2) + 1;
			size_t Size = 20;
			char num[20];
			sprintf_s(num, 20, "%.2f", c);
			l2 += strlen(num);
			sprintf_s(num, 20, "%.2f", m);
			l2 += strlen(num);
			char* sr2 = new char[l2];
			sprintf_s(sr2, l2, "(x^2 + y^2) ^ 2 = (2* ^2 + %.2f)^ 2 * x^2 + (% .2f - 2 * ^2) * y ^ 2\n", c, c);
			int k = strlen(sr2);
			sprintf_s(sr2 + k, l2 - k, "(x^2 + y^2)^2 = (2*%.2f^2 + )^2 * x^2 + ( - 2*%.2f^2) * y^2\n", m, m);
			k = strlen(sr2);
			return sr2;
		}
	}

	bool correct_get_int(int& a) noexcept {
		cin >> a;
		if (!cin.good()) {
			cin.clear();
			cin.ignore();
			return false;
		}
		return true;
	}

	bool correct_get_double(double& a) noexcept {
		cin >> a;
		if (!cin.good()) {
			cin.clear();
			cin.ignore();
			return false;
		}
		return true;
	}

	int get_int() noexcept {
		int num;
		while (true) {
			if (correct_get_int(num))
				break;
			cout << "Wrong number" << endl;
		}
		return num;
	}

	double get_double() noexcept {
		double num;
		while (true) {
			if (correct_get_double(num))
				break;
			cout << "Wrong number" << endl;
		}
		return num;
	}

	int create(Buth_Lemn& l) {
		double c, m;

		cout << "Enter c" << endl;
		c = get_double();

		cout << "Enter m" << endl;
		m = get_double();

		try {
			l.setC(c);
		}
		catch (const char* msg) {
			cerr << msg << endl;
			return 1;
		}

		try {
			l.setM(m);
		}
		catch (const char* msg2) {
			cerr << msg2 << endl;
			return 1;
		}

		return 0;
	}

	int change_parameters(Buth_Lemn& l) {
		int h;
		double c, m;
		do {
			cout << "0. Exit" << endl;
			cout << "1. Change c" << endl;
			cout << "2. Change m" << endl;
			h = get_int();
			switch (h) {
			case 0:
				cout << "***Exit***" << endl;
				break;

			case 1:
				cout << "***Change c***" << endl;
				c = get_double();
				try {
					l.setC(c);
				}
				catch (const char* msg) {
					cerr << msg << endl;
					return 1;
				}
				break;

			case 2:
				cout << "***Change m***" << endl;
				m = get_double();
				try {
					l.setM(m);
				}
				catch (const char* msg) {
					cerr << msg << endl;
					return 1;
				}
				break;

			default:
				cout << "You are wrong! Try again" << endl;
				break;
			}
		} while (h != 0);
		return 0;
	}

}
