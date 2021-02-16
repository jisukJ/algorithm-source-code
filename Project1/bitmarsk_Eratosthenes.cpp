#include <iostream>

using namespace std;

#define LAST_NUM 2000000000

unsigned char sieve[(LAST_NUM + 7) / 8 + 1];

void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}

bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}

void eratosthenes() {
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = int(sqrt(LAST_NUM));
	for (int i = 2; i <= sqrtn; ++i)
	{
		if (isPrime(i))
		{
			for (int j = i * i; j <= LAST_NUM; j += i)
			{
				setComposite(j);
			}
		}
	}
}


int main()
{
	eratosthenes();
	cout << "го";
}