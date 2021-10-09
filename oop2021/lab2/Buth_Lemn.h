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
        //setters
        void setC(double c) {
            this->c = c;
        }
        void setM(double c) {
            this->c = c;
        }
        //getters
        double getC() const { return c; };
        double getM() const { return m; };
        Buth_Lemn(double c = 3, double m = 1);//конструктор
        double type() const;
        double parametrs() const;
        double area() const;
        double distance() const;
        char* frm() const;
        bool correct_get_int(int& a) noexcept;
        bool correct_get_double(double& a) noexcept;
        int get_int() noexcept;
        double get_double() noexcept;
        int create(Buth_Lemn l);
        int change_parameters(Buth_Lemn l);
    };
}

#endif