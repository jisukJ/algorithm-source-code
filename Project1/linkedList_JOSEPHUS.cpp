#include <iostream>
#include <list>

using namespace std;
int C, N, K;

void josephus(int n, int k) {

	list <int> JOSEPHUS;
	for (int i = 1; i <= n; ++i)
		JOSEPHUS.push_back(i);
	list<int>::iterator kill = JOSEPHUS.begin();
	while (2 < n)
	{
		kill = JOSEPHUS.erase(kill);
		if (kill == JOSEPHUS.end())
			kill = JOSEPHUS.begin();
		--n;
		for (int i = 0; i < k - 1; ++i) {
			++kill;
			if (kill == JOSEPHUS.end())
				kill = JOSEPHUS.begin();
		}
	}
	cout << JOSEPHUS.front() << " " << JOSEPHUS.back() << endl;
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N >> K;
		josephus(N, K);
	}
}