#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
int arr[1000000];
struct FenwickTree {
	vector<int>tree;
	FenwickTree(int n) : tree(n + 1) {}
	int sum(int pos) {
		pos++;
		int ret = 0;
		while (0 < pos) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos&-pos);
		}
	}
};
int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N;
		for (int i = 0; i < N; ++i)
			cin >> arr[i];
		FenwickTree tmp(1000000);
		long long ans = 0;
		for (int i = 0; i < N; ++i)
		{
			ans +=tmp.sum(999999)-tmp.sum(arr[i]);
			tmp.add(arr[i], 1);
		}
		cout << ans << endl;
	}
}