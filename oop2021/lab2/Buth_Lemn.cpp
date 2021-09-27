//#include "stdafx.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
#include "Buth_Lemn.h"

namespace Prog2 {
	double type(double c, double m) {	//Определяет
		int i;							//тип кривой
		if (c > 2 * m * m) return i = 0;//elleptic
		if (c < 2 * m * m) return i = 1;//hyperbolic
	}
	double parametrs(double c, double m) {//Определяет
		if (type(c, m) == 0) {//e		//параметры
			double a2 = 2 * m * m + c;	//для полярного	
			double b2 = c - 2 * m * m;	//уравнения
		}								//зависящие
		else if (type(c, m) == 1) {//h	//от типа
			double a2 = 2 * m * m + c;	//кривой
			double b22 = 2 * m * m - c;
		}
	}
	double area(double c, double m) const {
		if (type(c, m) == 0) {
			return 3.14159 * (a2 + b2) / 2;
		}
		else if (type(c, m) == 1) {
			return (a2 - b22) * (atan(sqrt(a2 / b22))) / 2 + (sqrt(a2 * b22) / 2;
		}
	}