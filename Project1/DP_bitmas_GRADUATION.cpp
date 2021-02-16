#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define INF 987654321
int C;
int N;
int K;
int M;
int L;
int prerequisite[12];
int classes[10];
int cache[10][(1 << 12)];
int bitcount(int x)
{
	if (x == 0)
		return 0;
	return (x % 2) + bitcount(x / 2);
}

int ForGraduation(int se, int taken) {
	if (K <= bitcount(taken))
		return 0;
	if (se == M)
		return INF;
	int& ret = cache[se][taken];
	if (ret != -1)
		return ret;
	ret = INF;
	int canTake = (classes[se] & ~taken);
	for (int i = 0; i < N; ++i)
		if ((canTake&(1 << i)) && ((taken&prerequisite[i]) != prerequisite[i]))
			canTake &= ~(1 << i);
	for (int take = canTake; 0 < take; take = ((take - 1)&canTake))
	{
		if (bitcount(take) > L)
			continue;
		ret = min(ret, ForGraduation(se + 1, (taken | take)) + 1);
	}
	ret = min(ret, ForGraduation(se + 1, taken));
	return ret;
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		memset(classes, 0, sizeof(classes));
		memset(prerequisite, 0, sizeof(prerequisite));
		memset(cache, -1, sizeof(cache));
		cin >> N >> K >> M >> L;
		for (int i = 0; i < N; ++i)
		{
			int tmp;
			cin >> tmp;
			for (int j = 0; j < tmp; ++j)
			{
				int tmp2;
				cin >> tmp2;
				prerequisite[i] |= (1 << tmp2);
			}
		}
		for (int i = 0; i < M; ++i)
		{
			int tmp;
			cin >> tmp;
			for (int j = 0; j < tmp; ++j)
			{
				int tmp2;
				cin >> tmp2;
				classes[i] |= (1 << tmp2);
			}
		}
		int a = ForGraduation(0, 0);
		if (a == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << a << endl;
	}
	return 0;
}