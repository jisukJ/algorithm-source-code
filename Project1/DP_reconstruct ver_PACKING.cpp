#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int C, N, W;
int volume[100], need[100];
string str[100];
int cache[1001][100];

int pack(int capacity, int item)
{
	if (item == N)
		return 0;
	int& ret = cache[capacity][item];
	if (ret != -1)
		return ret;
	ret = pack(capacity, item + 1);
	if (volume[item] <= capacity)
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	return ret;
}

void reconstruct(int capacity, int item, vector<string>&picked)
{
	if (item == N)
		return;
	if (pack(capacity, item) == pack(capacity, item + 1))
	{
		reconstruct(capacity, item + 1, picked);
	}
	else
	{
		picked.push_back(str[item]);
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		for (int i = 0; i < 1001; ++i)
			for (int j = 0; j < 100; ++j)
				cache[i][j] = -1;

		cin >> N >> W;

		for (int i = 0; i < N; ++i)
			cin >> str[i] >> volume[i] >> need[i];
		vector<string> ans;
		pack(W, 0);
		reconstruct(W, 0, ans);
		cout << cache[W][0] <<" "<<ans.size()<<endl;
		for (int i = 0; i < ans.size(); ++i)
			cout << ans[i] << endl;
	}
}