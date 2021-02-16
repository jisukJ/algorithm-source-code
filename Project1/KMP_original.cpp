#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string N;
	string H;
	int M;
	cin >> H >> N;
	M = N.size();

	vector <int> fail(M+1, 0);
	for (int i = 1, j = 0; i < M; ++i)
	{
		while (j > 0 && N[i] != N[j])
		{
			j = fail[j];
		}

		if (N[i] == N[j])
			fail[i+1] = ++j;
	}
	int n = H.size(), m = N.size();
	vector<int>ret;
	int matched = 0; 
	for (int i = 0; i < n; ++i) {
		while (matched > 0 && H[i] != N[matched])
			matched = fail[matched];
		if (H[i] == N[matched])
		{
			++matched;
			if (matched == m) {
				ret.push_back(i - m + 1);
				matched = fail[matched];
			}
		}
	}
	for (int i = 0; i < ret.size(); ++i)
		cout << ret[i] << endl;
}