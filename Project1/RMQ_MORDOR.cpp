#include <iostream>

using namespace std;
int C,N,Q;
const int INF = 20000;
int hi[100000];
int r_hi[100000];
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

struct RMQ {
	int n;
	int* rangemin;
	RMQ(int arr[])
	{
		
		n = N;
		rangemin = new int [n * 4];
		init(arr, 0, n - 1, 0);
	}
	int init(int arr[], int left, int right, int node)
	{
		if (left == right)
			return rangemin[node] = arr[left];
		int mid = (left + right) / 2;
		int leftmin = init(arr, left, mid, node*2+1);
		int rightmin = init(arr, mid + 1, right, node * 2 + 2);
		return rangemin[node] = min(leftmin, rightmin);
	}
	int query(int left, int right, int nodeLeft, int nodeRight, int node)
	{
		if (right < nodeLeft || nodeRight < left)
			return INF;
		if (left<=nodeLeft &&nodeRight<=right)
			return rangemin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, nodeLeft, mid, node * 2 + 1), query(left, right, mid + 1, nodeRight, node * 2 + 2));
	}
	int query(int left, int right)
	{
		return query(left, right,0, n - 1, 0);
	}
	int update(int index, int newValue, int nodeLeft, int nodeRight, int node)
	{
		if (index < nodeLeft || nodeRight < index)
			return rangemin[node];
		if (nodeLeft == nodeRight)
			return rangemin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangemin[node] = min(update(index, newValue, nodeLeft, mid, node * 2 + 1), update(index, newValue, mid + 1, nodeRight, node * 2 + 2));
	}
	int update(int index, int newValue)
	{
		return update(index, newValue, 0, n - 1, 0);
	}

};

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N >> Q;
		
		for (int i = 0; i < N; ++i)
		{
			cin >> hi[i];
			r_hi[i] = -hi[i];
		}

		RMQ Min = RMQ(hi);
		RMQ Max = RMQ(r_hi);
		for (int i = 0; i < Q; ++i)
		{
			int a, b;
			cin >> a >> b;
			cout << -Max.query(a, b)-Min.query(a, b) << endl;
		}
	}
}