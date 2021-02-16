#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int T, N;
int ans;

vector<int> getTable(string &A)
{
	vector<int>fail(A.size(), 0);
	for (int j = 0, i = 1; i < A.size(); ++i)
	{
		while (0 < j&&A[i] != A[j])
			j = fail[j - 1];
		if (A[i] == A[j])
			fail[i] = ++j;
	}
	return fail;
}

int clockwiseKMP(string& A, string& B)
{
	string C = B;
	C = C + B;
	vector<int> fail = getTable(A);
	int matched = 0;
	for (int i = 0; i < C.size(); ++i)
	{
		while (0 < matched&&C[i] != A[matched])
			matched = fail[matched - 1];
		if (C[i] == A[matched])
		{
			matched++;
			if (matched == A.size())
				return i + 1 - A.size();
		}
	}
	return 0;
}


int main()
{
	cin >> T;
	for (int test = 0; test < T; ++test)
	{
		cin >> N;
		vector<string> S(N + 1);
		for (int i = 0; i <= N; ++i)
			cin >> S[i];
		int ans = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i % 2 == 0)
				ans += clockwiseKMP(S[i], S[i + 1]);
			else
				ans += clockwiseKMP(S[i + 1], S[i]);
		}
		cout << ans << endl;
	}
}