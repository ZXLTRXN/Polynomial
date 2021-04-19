#include <iostream>
#include "TMember.h"
#include "TPoly.cpp"

using namespace Polynomial;
using namespace std;

int main()
{
    
    TPoly p1 = TPoly(2,3);
    TPoly p2 = TPoly(1, 2);
    TPoly p3 = TPoly(4, 0);
    TPoly p4 = TPoly(0, 0);

    TPoly r1 = p1+p2-p3;
    TPoly r2 = r1.diff();
    double r3 = r1.calc(2);

    //cout << r3 << endl;
    cout << r2.to_string() << endl;

}
