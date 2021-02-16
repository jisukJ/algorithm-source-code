#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;
int C,N;
map<int, int>coords;

bool isDominated(int x, int y)
{
	map<int, int> ::iterator iter = coords.lower_bound(x);
	if (iter == coords.end())
		return false;
	return y < iter->second;
}

void removeDominated(int x,int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.begin())
		return;
	--it;
	while (true)
	{
		if (y < it->second)
			break;
		if (it == coords.begin())
		{
			coords.erase(it);
			break;
		}
		else
		{
			map<int, int>::iterator tmp = it;
			--tmp;
			coords.erase(it);
			it = tmp;
		}
	}
	return;
}

int NERD2(int x,int y) {
	if (isDominated(x, y))
		return coords.size();
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N;
		int ans=0;
		coords.clear();
		for (int i = 0; i < N; ++i)
		{
			int x, y;
			cin >>x>>y;
			ans += NERD2(x,y);
		}
		cout << ans << endl;
	}
}