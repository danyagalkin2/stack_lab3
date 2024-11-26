#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
	TCalc c;
	cout << "string: 1+10*(10-8)^2-32\n";
	c.setInfix("1+10*(10-8)^2-32");
	c.ToPostfix();
	cout << "Postfix string: ";
	cout << c.getPostfix() << '\n';
	cout << "res: ";
	cout << c.CalcPostfix() << '\n';


	cout << "string: 20+10*3-4+(1+2)/3-8\n";
	c.setInfix("20+10*3-4+(1+2)/3-8");
	double res = c.Calc();
	c.ToPostfix();
	cout << "Postfix string: ";
	cout << c.getPostfix() << '\n';

	cout << "res: ";
	cout << res;
	cout << "\n";

	c.setInfix("(((1+23)*1-22)+5)*2-7");
	cout << c.Calc();

   return 0;
}

