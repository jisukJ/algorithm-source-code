#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int C, N;

long long countMoves(vector<int>& A, int left, int right)
{
	if (left == right)
		return 0;
	int mid = (left + right) / 2;
	long long ret = countMoves(A, left, mid) + countMoves(A, mid + 1, right);
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right)
	{
		if (leftIndex <= mid && (right < rightIndex || A[leftIndex] <= A[rightIndex]))
			tmp[tmpIndex++] = A[leftIndex++];
		else
		{
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	for (int i = 0; i < tmp.size(); ++i)
		A[left + i] = tmp[i];
	return ret;
}
int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N;
		vector<int> A(N);
		for (int i = 0; i < N; ++i)
			cin >> A[i];
		cout << countMoves(A, 0, N - 1) << endl;
	}
}