#pragma once
#include <iostream>
#include <string> 
#include <math.h>
namespace Polynomial
{
    class TMember
    {
    public:
        TMember();
        TMember(int coeff,int deg);

        int get_degree();
        int get_coeff();

        void set_degree(int deg);
        void set_coeff(int coeff);

        bool friend operator==(const TMember& c1, const TMember& c2);
        bool friend operator!= (const TMember& c1, const TMember& c2);
        std::string to_string();

        TMember* diff();
        double calc(int x);

    private:
        int FCoeff;
        int FDegree;
    };
}
