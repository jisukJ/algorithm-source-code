#include <iostream>

using namespace std;

unsigned int nextt = 1;

int rand(void)
{
	nextt = nextt * 1103515245 + 12345;
	return (int)(nextt >> 16) & 0x7fff;
}

int main()
{
	for (int i = 0; i < 100; ++i)
	{
		nextt = i;
		cout << rand() << endl;
	}
}