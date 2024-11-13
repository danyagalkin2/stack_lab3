#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
	TCalc c;
	c.setInfix("1+10*(10-8)^2-32");
	c.ToPostfix();
	cout << c.getPostfix() << '\n';
	cout << c.CalcPostfix();
   return 0;
}

