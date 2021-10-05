#ifndef _BUTH_LEMN_H_
#define _BUTH_LEMN_H_
//#include "gtest/gtest_proud.h"
#include <math.h>

namespace Prog2 {
    class Buth_Lemn {
    private:
        double c;
        double m;
    public:
        Buth_Lemn(double c = 3, double m = 1);//конструктор
        //setters
        Buth_Lemn& setCM(double c, double m);
        //getters
        double getC() const { return c; };
        double getM() const { return m; };
        double type() const;
        double parametrs() const;
        double area() const;
        double distance() const;
        char* frm() const;
    };
}

#endif
