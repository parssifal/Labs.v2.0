//#include "stdafx.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
#include "Buth_Lemn.h"

namespace Prog2 {
		double type(double c, double m) const {       //Определяет
			int i;                          //тип кривой
			if (c > 2 * m * m) return i = 0;//elleptic
			if (c < 2 * m * m) return i = 1;//hyperbolic
		}

		double parametrs(double c, double m) const {          //Определяет
			if (type(c, m) == 0) {//e               //параметры
				double a2 = 2 * m * m + c;      //для полярного
				double b2 = 2 * m * m + c;      //уравнения
			}                                       //зависящие
			else if (type(c, m) == 1) {//h          //от типа
				double a2 = 2 * m * m + c;      //кривой
				double b22 = 2 * m * m - c;
			}
		}

		double area(double c, double m) const {//Вычисляет площадь
			if (type(c, m) == 0) {
				return 3.14159 * ((2 * m * m + c) + (2 * m * m + c)) / 2;
			}
			else if (type(c, m) == 1) {
				return ((2 * m * m + c) - (2 * m * m - c)) * (atan(sqrt((2 * m * m + c) / (2 * m * m - c)))) / 2 + (sqrt((2 * m * m + c) * (2 * m * m - c))) / 2;
			}
		}
		Buth_Lemn& Buth_Lemn::setCM(double c0, double m0) {
			if (c0 == 0)
				throw exception("invalid value, degeneration into bernoulli lemniscate");
			c = c0;
			return *this;
			if (c0 = 2 * m0 * m0)
				throw exception("invalid values, degeneration into two circles");
			c = c0;
			m = m0;
			return *this;
		}
		char* Buth_Lemn::frm(int type) const { //формула лемнискаты Бута
			int i = type;
			if (i == 0) {
				char* s1 = "(x^2 + y^2)^2 = (2* ^2 + )^2 * x^2 + ( - 2* ^2) * y^2\n";
				int l1 = strlen(s1) + 1;
				size_t Size = 20;
				char num[20];
				sprintf_s(num, 20, "%.2f", c);
				l1 += strlen(num);
				sprintf_s(num, 20, "%.2f", m);
				l1 += strlen(num);
				char* s1 = new char[l1];
				sprintf_s(s1, l1, "(x^2 + y^2)^2 = (2* ^2 + %.2f)^2 * x^2 + (%.2f - 2* ^2) * y^2\n", c, c);
				int k = strlen(s1);
				sprintf_s(s1 + k, l1 - k, "(x^2 + y^2)^2 = (2*%.2f^2 + )^2 * x^2 + ( - 2*%.2f^2) * y^2\n", m, m);
				k = strlen(s1);
				return s1;
			}
			else if (i == 1) {
				char* s2 = "(x^2 + y^2)^2 = (2* ^2 + )^2 * x^2 - (2* ^2 - ) * y^2\n";
				int l2 = strlen(s2) + 1;
				size_t Size = 20;
				char num[20];
				sprintf_s(num, 20, "%.2f", c);
				l2 += strlen(num);
				sprintf_s(num, 20, "%.2f", m);
				l2 += strlen(num);
				char* s2 = new char[l2];
				sprintf_s(s2, l2, "(x^2 + y^2) ^ 2 = (2* ^2 + %.2f)^ 2 * x^2 + (% .2f - 2 * ^2) * y ^ 2\n", c, c);
				int k = strlen(s2);
				sprintf_s(s2 + k, l2 - k, "(x^2 + y^2)^2 = (2*%.2f^2 + )^2 * x^2 + ( - 2*%.2f^2) * y^2\n", m, m);
				k = strlen(s2);
				return s2;
			}
		}
	}

