#include <iostream>

int gcd1(int a, int b)
{
	int tmp, n;
	if (a < b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	while (b != 0)
	{
		n = a % b;
		a = b;
		b = n;
	}
	return a;
}

int gcd2(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd2(b, a%b);
}