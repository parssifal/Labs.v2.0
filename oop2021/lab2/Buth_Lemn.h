#ifndef _BUTH_LEMN_H_
#define _BUTH_LEMN_H_
//#include "gtest/gtest_proud.h"
#include <math.h>

namespace Prog2 {
	/*struct Parametrs {
		double a2, b2;
	};*/ 
	class Buth_Lemn {
	private:
		//Parametrs P;
		double c, m;
		/*double a2 = 2 * m * m + c;
		double b2 = c - 2 * m * m;
		double b22 = 2 * m * m - c;*/
	public:
		Buth_Lemn(double c = 3, double m = 1);
		double type(double c, double m) {	//Определяет тип кривой
			int i;
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
			} else if (type(c, m) == 1) {
				return (a2 - b22) * (atan(sqrt(a2 / b22))) / 2 + (sqrt(a2 * b22) / 2;
			}
		}
	};
}
#endif