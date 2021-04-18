#include <iostream>
#include "TMember.h"

using namespace Polynomial;
using namespace std;

int main()
{
    TMember* pol1 = new TMember(-99,0);

    cout << pol1->to_string() <<endl;
}
