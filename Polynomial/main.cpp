#include <iostream>
#include "TMember.h"
#include "TPoly.cpp"

using namespace Polynomial;
using namespace std;

int main()
{
    
    TPoly pol1 = TPoly(1,2);
    TPoly pol2 = TPoly(3, 4);
    TPoly pol3 = TPoly(1, 2);
    TPoly pol4 = TPoly(3, 4);
    TPoly pol5 = TPoly(1,2);


    TPoly polr = pol4 - pol5;
    TPoly polr2 = pol2 + pol3;
    TPoly polr3 = polr2 * polr;
    TPoly polr4 = pol1.diff();

    //TMember m = polr.get_elem(0);
    //cout << m.to_string() << endl;
    //cout << polr.degree() << endl;
    //cout << polr.coeff(1) << endl;
    cout << polr4.to_string() <<endl;

    //bool a = (polr == polr2);
    //cout << a << endl;
}
