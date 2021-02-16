#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int C, N, Q;

struct mM {
	int min, max;
};
vector<int> hi;
struct RMQ {
	int n;
	vector<mM>range;
	RMQ(const vector<int>& arr)
	{
		n = arr.size();
		range.resize(4 * n);
		init(arr, 0, n - 1, 0);
	}
	mM init(const vector<int>&arr, int left, int right, int node)
	{
		if (left == right)
		{
			range[node].min = arr[left];
			range[node].max = arr[left];
			return range[node];
		}
		int mid = (left + right) / 2;
		mM ls=init(arr, left, mid, node * 2 + 1);
		mM rs=init(arr, mid+1, right, node * 2 + 2);
		range[node].min = min(ls.min, rs.min);
		range[node].max = max(ls.max, rs.max);
		return range[node];
	}
	mM query(int left, int right,int nodeLeft,int nodeRight, int node)
	{
		if (right < nodeLeft || nodeRight < left)
		{
			mM ret;
			ret.max = 0;
			ret.min = 20000;
			return ret;
		}
		if (left <= nodeLeft && nodeRight <= right)
		{
			return range[node];
		}
		int mid = (nodeLeft + nodeRight) / 2;
		mM ls = query(left,right,nodeLeft, mid, node * 2 + 1);
		mM rs = query(left,right,mid+1, nodeRight, node * 2 + 2);
		mM ret;
		ret.max = max(ls.max, rs.max);
		ret.min = min(ls.min, rs.min);
		return ret;
	}
	mM query(int left, int right)
	{
		return query(left, right, 0, n - 1, 0);
	}
};

int main()
{
	cin >> C;
	
	for (int test = 0; test < C; ++test)
	{
		cin >> N >> Q;
		hi.clear();
		for (int i = 0; i < N; ++i)
		{
			int tmp;
			cin >> tmp;
			hi.push_back(tmp);
		}
		RMQ rmq(hi);
		for (int i = 0; i < Q; ++i)
		{
			int tmp, tmp2;
			cin >> tmp >> tmp2;
			mM ans = rmq.query(tmp, tmp2);
			cout << ans.max - ans.min << endl;
		}
	}
}