#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

//https://www.acmicpc.net/problem/2912

int N, C;
int color[300001];
int M;
vector<int> list[10001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	mt19937 mt = mt19937((unsigned int)time(NULL));
	uniform_int_distribution<int> ran(0, 2147483647);
	cin >> N >> C;
	for (int i = 1; i <= N; ++i)
	{
		cin >> color[i];
		if (list[color[i]].empty())
		{
			list[color[i]].push_back(-1);
		}
		list[color[i]].push_back(i);
	}
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		int st, ed, ans = -1;
		cin >> st >> ed;
		for (int j = 0; j < 100; ++j)
		{
			int col = color[ran(mt) % (ed - st + 1) + st];
			int cnt = upper_bound(list[col].begin(), list[col].end(), ed) - lower_bound(list[col].begin(), list[col].end(), st);
			if (cnt > (ed - st + 1) / 2)
			{
				ans = col;
				break;
			}
		}
		if (ans == -1)
		{
			cout << "no\n";
		}
		else
		{
			cout << "yes " << ans << "\n";
		}
	}
}
