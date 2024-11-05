#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
	TCalc c;
	c.setInfix("1+2*(3-2)-4");
	c.ToPostfix();
	cout << c.getPostfix();


   return 0;
}

