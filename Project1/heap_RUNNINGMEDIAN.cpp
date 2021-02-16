#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;

long long C, N, a, b;
long long A[200001];

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N>>a>>b;
		long long ans = 0;
		priority_queue < int, vector<int>, less<int> > maxHeap;
		priority_queue < int, vector<int>, greater<int> > minHeap;
		A[0] = 1983;
		maxHeap.push(A[0]);
		ans += A[0];
		for (int i = 1; i < N; ++i)
		{
			A[i] = (A[i - 1] * a + b) % 20090711;
		}
		
		for (int i = 1; i < N; ++i)
		{
			if (maxHeap.size() == minHeap.size())
				maxHeap.push(A[i]);
			else
				minHeap.push(A[i]);
			if (!minHeap.empty() && !maxHeap.empty())
			{
				if (minHeap.top() < maxHeap.top())
				{
					int a = minHeap.top();
					int b = maxHeap.top();
					minHeap.pop();
					maxHeap.pop();
					maxHeap.push(a);
					minHeap.push(b);
				}
			}
			ans = (ans + maxHeap.top()) % 20090711;
		}
		cout << ans << endl;
	}
}