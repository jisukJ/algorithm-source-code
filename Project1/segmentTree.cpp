#include <iostream>

using namespace std;
int N, M, K;
unsigned long long int input[1000000];


template <typename T>
struct SegmentTree {
	T* arr;
	int size;
	SegmentTree(int N) {
		size = 3 * N;
		arr = new T[size];
		init(0, N - 1, 0);
	}
	~SegmentTree() {
		delete[] arr;
	}
	T init(int left, int right, int node)
	{
		if (left == right)
			return arr[node] = input[left];
		int mid = (left + right) / 2;
		T leftNode = init(left, mid, node * 2 + 1);
		T rightNode = init(mid + 1, right, node * 2 + 2);
		return arr[node] = (leftNode * rightNode) % 1000000007;
	}
	T query(int left, int right)
	{
		return query(left, right, 0, N - 1, 0);
	}
	T query(int left, int right, int nodeLeft, int nodeRight, int node)
	{
		if (nodeRight < left || right < nodeLeft)
			return 1;
		if (left <= nodeLeft && nodeRight <= right)
			return arr[node];
		int mid = (nodeLeft + nodeRight) / 2;
		T leftNode = query(left, right, nodeLeft, mid, node * 2 + 1);
		T rightNode = query(left, right, mid + 1, nodeRight, node * 2 + 2);
		return (leftNode * rightNode) % 1000000007;
	}
	T update(int n)
	{
		return update(n, 0, N - 1, 0);
	}
	T update(int n, int left, int right, int node)
	{
		if (n < left || right < n)
			return arr[node];
		if (left == right)
			return arr[node] = input[left];
		int mid = (left + right) / 2;
		T leftNode = update(n, left, mid, node * 2 + 1);
		T rightNode = update(n, mid + 1, right, node * 2 + 2);
		return arr[node] = (leftNode * rightNode) % 1000000007;
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		cin >> input[i];
	}
	SegmentTree<unsigned long long int> segmenttree(N);
	for (int i = 0; i < M + K; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1) {
			--b;
			input[b] = c;
			segmenttree.update(b);
		} else {
			--b;
			--c;
			cout << segmenttree.query(b, c) << "\n";
		}
	}
}