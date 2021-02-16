#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int C, N;
int S[500];
int cache[500];
int choices[500];
vector<int> seq;
int lis(int start)
{
	int& ret = cache[start];
	if (ret != -1)
		return ret;
	ret = 1;
	int bestNext = -1;
	for (int next = start + 1; next < N; ++next)
		if (start == -1 || S[start] < S[next])
		{
			int cand = lis(next) + 1;
			if (ret < cand)
			{
				ret = cand;
				bestNext = next;
			}
		}
	choices[start] = bestNext;
	return ret;
}
void reconstruct(int start, vector<int>& seq)
{
	if (start != -1)
		seq.push_back(S[start]);
	int next = choices[start];
	if (next != -1)
		reconstruct(next, seq);
}
int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N;
		seq.clear();
		for (int i = 0; i < N; ++i)
		{
			//cin >> S[i];
			S[i] = rand() % 1000;
			cache[i] = -1;
			choices[i] = -1;
		}
		lis(0);
		seq.clear();
		reconstruct(0, seq);
		for (int i = 0; i < seq.size(); ++i)
		{
			cout << seq[i] << " ";
		}
		cout << endl;
	}
}