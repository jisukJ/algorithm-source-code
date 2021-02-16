#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int C;

vector<int> getTable(string & S) {
	vector<int> fail(S.size(), 0);
	for (int j = 0, i = 1; i < S.size(); ++i)
	{
		while (0 < j&&S[i] != S[j])
			j = fail[j - 1];
		if (S[i] == S[j])
			fail[i] = ++j;
	}
	return fail;
}

int PALINDROMIZE(string & S,string & R) {
	int ret = 0;
	vector<int> fail;
	fail = getTable(R);
	int matched = 0;
	for (int i = 0; i < S.size(); ++i)
	{
		while (0 < matched&&S[i] != R[matched])
			matched = fail[matched - 1];
		if (S[i] == R[matched])
		{
			matched++;
			if (ret < matched&&i==S.size()-1)
				ret = matched;
		}
	}
	return ret;
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		string S1,S2;
		cin >> S1;
		for (int i = S1.size(); 0 < i; --i)
		{
			S2.push_back(S1[i - 1]);
		}
		cout << 2*S1.size()-PALINDROMIZE(S1, S2)<<endl;
	}
}