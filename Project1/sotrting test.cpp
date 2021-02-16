#include <algorithm>
#include <iostream>


int N[1000];
int A = 5;
using namespace std;

bool cmp(int i, int j)
{
	return i > j;
}

int main()
{
	for (int i = 0; i < A; ++i)
		cin >> N[i];
	sort(N,N+A,cmp);
	for (int i = 0; i < A; ++i)
		cout << N[i] << " ";
}