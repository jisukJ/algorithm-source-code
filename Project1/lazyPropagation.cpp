#include <iostream>

using namespace std;
int N, M, K;
long long int input[1000000];
struct segmentTree {

	long long int* arr;
	long long int* lazy;
	segmentTree() {
		arr = new long long int[N * 4];
		lazy = new long long int[N * 4];
		init(0, N - 1, 0);
	}
	long long int init(int left, int right, int node) {
		lazy[node] = 0;
		if (left == right)
			return arr[node] = input[left];
		int mid = (left + right) / 2;
		return arr[node] = init(left, mid, node * 2 + 1) + init(mid + 1, right, node * 2 + 2);
	}
	long long int query(int left, int right)
	{
		return query(left, right, 0, N - 1, 0);
	}
	long long int query(int left, int right, int nodeLeft, int nodeRight, int node)
	{
		propagate(nodeLeft, nodeRight, node);
		if (nodeRight < left || right < nodeLeft)
			return 0;
		if (left <= nodeLeft && nodeRight <= right)
			return arr[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return query(left, right, nodeLeft, mid, node * 2 + 1) + query(left, right, mid + 1, nodeRight, node * 2 + 2);
	}
	void propagate(int nodeLeft, int nodeRight, int node)
	{
		if (lazy[node] != 0) {
			if (nodeLeft != nodeRight) {
				lazy[node * 2 + 1] += lazy[node];
				lazy[node * 2 + 2] += lazy[node];
			}
			arr[node] += lazy[node] * (nodeRight - nodeLeft + 1);
			lazy[node] = 0;
		}
	}
	long long int update(int val, int left, int right)
	{
		return update(val, left, right, 0, N - 1, 0);
	}
	long long int update(int val, int left, int right, int nodeLeft, int nodeRight, int node)
	{
		propagate(nodeLeft, nodeRight, node);
		if (right < nodeLeft || nodeRight < left)
			return arr[node];
		if (left <= nodeLeft && nodeRight <= right)
		{
			lazy[node] += val;
			propagate(nodeLeft, nodeRight, node);
			return arr[node];
		}
		int mid = (nodeLeft + nodeRight) / 2;
		return arr[node] = update(val, left, right, nodeLeft, mid, node * 2 + 1) + update(val, left, right, mid + 1, nodeRight, node * 2 + 2);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		cin >> input[i];
	}
	segmentTree segmenttree = segmentTree();
	for (int i = 0; i < M + K; ++i) {
		int a, b, c, d;
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			--b, --c;
			segmenttree.update(d, b, c);
		}
		else {
			cin >> b >> c;
			--b, --c;
			cout << segmenttree.query(b, c) << "\n";
		}
	}
}