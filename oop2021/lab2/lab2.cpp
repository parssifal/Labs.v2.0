//#include "stdafx.h"
#include <iostream>
#include "\Users\Артур\source\repos\lab2\Buth_Lemn.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Prog2::Circle c(2, 1, 2);
	Prog2::Point p(3);
	int fl1 = 1;
	double r;
	char* s = NULL;
	while (fl1) {
		std::cout << "Your circle is:" << std::endl;
		s = c.frm();
		std::cout << s << std::endl;
		delete[] s;
		std::cout << "area: " << c.area() << std::endl;
		std::cout << "perimeter: " << c.perimeter() << std::endl;
		std::cout << "distance: " << c.distance() << std::endl;
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter x for calculate value y(x) or precc ctrl+Z to quit:" <<
				std::endl;
			double x;
			Prog2::Point y;
			std::cin >> x;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				y = c.f(x);
				std::cout << "y1 = " << y.x << ", y2 = " << y.y << std::endl;
			}

			Shustova L.I.

				KC& T

				KC& T

				Shustova L.I.

				5

				catch (std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		std::cout << "Enter new x, y and r to continue or press ctrl+Z to quit:" << std::endl;
		std::cin >> p.x >> p.y >> r;
		if (std::cin.good()) {
			c.setP(p);
			try {
				c.setR(r);
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else
			fl1 = 0;
	}
	return 0;
}