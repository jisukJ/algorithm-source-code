
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct RangeResult {
	int size;
	int mostFrequent;
	int leftNumber, leftFreq;
	int rightNumber, rightFreq;
};
struct RMQ{
	int n;
	vector<RangeResult>rangeMaximum;
	RMQ(const vector<int>& arr)
	{
		n = arr.size();
		rangeMaximum.resize(4 * n);
		init(arr, 0, n - 1, 0);
	}
	RangeResult init(const vector<int>& arr, int left, int right, int node)
	{
		if (left == right)
		{
			rangeMaximum[node].size = 1;
			rangeMaximum[node].mostFrequent = 1;
			rangeMaximum[node].leftNumber = arr[left];
			rangeMaximum[node].leftFreq = 1;
			rangeMaximum[node].rightNumber = arr[left];
			rangeMaximum[node].rightFreq = 1;
			return rangeMaximum[node];
		}
		int mid = (left + right) / 2;
		return rangeMaximum[node] = merge(init(arr, left, mid, node * 2 + 1),
			init(arr, mid + 1, right, node * 2 + 2));
	}
	RangeResult merge(const RangeResult& a, const RangeResult& b) {
		RangeResult ret;
		ret.size = a.size + b.size;
		ret.leftNumber = a.leftNumber;
		ret.leftFreq = a.leftFreq;
		if (a.size == a.leftFreq&&a.leftNumber == b.leftNumber)
			ret.leftFreq += b.leftFreq;
		ret.rightNumber = b.rightNumber;
		ret.rightFreq = b.rightFreq;
		if (b.size == b.rightFreq&&a.rightNumber == b.rightNumber)
			ret.rightFreq += a.rightFreq;
		ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
		if (a.rightNumber == b.leftNumber)
			ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);
		return ret;
	}
};


int main() 
{
	vector<int> arr;
	for (int i = 0; i < 16; ++i)
	{
		arr.push_back(rand() % 10);
		cout << arr[i] << " ";
	}
	sort(arr.begin(), arr.end());
	cout << endl;
	for (int i = 0; i < 16; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	RMQ rmq(arr);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < pow(2, i); ++j)
		{
			cout << rmq.rangeMaximum[pow(2, i) - 1 + j].mostFrequent << " ";
		}
		cout << endl;
	}
}