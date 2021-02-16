#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

template <typename T>
class vector {
private:
	int _capacity = 0;
	int _size = 0;
	T *arr;
public:
	int capacity() { return _capacity; }
	int size() { return _size; }
	bool empty() { return _size == 0; }
	void clear() { _size = 0; }
	int at(int position) { return arr[position]; };
	int front() { return arr[0]; }
	int back() { return arr[_size - 1]; }

	vector(int size = 1) {
		_capacity = size;
		arr = new T[_capacity];
	}

	~vector() {
		if (arr)
			delete[] arr;
	}

	void push_back(T val) {
		if (_size == _capacity) {
			_capacity *= 2;
			T* tmp = new T[_capacity];
			for (int i = 0; i < _size; ++i)
				tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
		}
		arr[_size++] = val;
	}

	void pop_back() {
		_size--;
	}

	T& operator[](int i) {
		return arr[i];
	}
};

int sqrt(int n)
{
	double ret = n;
	for (int i = 0; i < 16; ++i)
	{
		ret = ret - (ret*ret - n) / (ret * 2);
	}
	return int(ret);
}

int N, M, K;
int main()
{
	scanf("%d %d %d", &N, &M, &K);
	vector <unsigned long long int> arr(N);
	unsigned long long int sqrtN = sqrt(N);
	vector <unsigned long long int> arr2((N/sqrtN)+1);
	for (int i = 0; i < (N / sqrtN)+1; ++i)
		arr2[i] = 0;
	for (int i = 0; i < N; ++i)
	{
		scanf("%llu", &arr[i]);
		arr2[i / sqrtN] += arr[i];
	}
	unsigned long long int a, b, c;
	for (int i = 0; i < M + K; ++i)
	{
		scanf("%llu %llu %llu", &a, &b, &c);
		if (a == 1)
		{
			b--;
			arr2[b / sqrtN] = arr2[b / sqrtN] - arr[b] + c;
			arr[b] = c;
		}
		else if (a == 2)
		{
			b--;
			c--;
			unsigned long long int left =b/sqrtN;
			unsigned long long int right = c/sqrtN;
			unsigned long long int ans = 0;
			if (left != right)
			{
				for (int i = left; i < right; ++i)
				{
					ans += arr2[i];
				}
				for (int i = left * sqrtN; i < b; ++i)
					ans -= arr[i];
				for (int i = right * sqrtN; i <= c; ++i)
					ans += arr[i];
			}
			if (left == right)
				for (int i = b; i <= c; ++i)
					ans += arr[i];
			printf("%llu\n", ans);
		}
	}
}