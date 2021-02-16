#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int C,K;
string S;
vector<int>SA;
vector<int>group;
int d,N;

bool cmp(int i, int j)
{
	if (group[i] != group[j])
		return group[i] < group[j];
	i += d;
	j += d;
	return (i < N&&j < N) ? group[i]<group[j] : i>j;
}
void getSA() {
	N = S.size();
	SA.assign(N,0);
	group.assign(N,0);
	for (int i = 0; i < N; ++i)
	{
		SA[i] = i;
		group[i] = S[i];
	}
	vector<int>temp(N,0);
	for (d = 1;; d *= 2)
	{
		sort(SA.begin(), SA.end(), cmp);
		for (int i = 0; i < N-1; ++i)
			temp[i + 1] = temp[i] + cmp(SA[i], SA[i + 1]);
		for (int i = 0; i < N; ++i)
			group[SA[i]] = temp[i];
		if (temp[N - 1] == N - 1)
			break;
	}
}

int commonPrefix(int i, int j)
{
	int k = 0;
	while (i < S.size() && j < S.size() && S[i] == S[j])
	{
		++i;
		++j;
		++k;
	}
	return k;
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> K;
		cin >> S;
		SA.clear();
		group.clear();
		getSA();
		int ans = 0;
		for (int i = 0; i + K <= S.size(); ++i)//범위에 주목
		{
			ans = max(ans, commonPrefix(SA[i], SA[i + K - 1]));
		}
		cout << ans << endl;
	}
}