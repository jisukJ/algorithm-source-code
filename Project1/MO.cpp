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

struct query {
	int lo, hi, idx;
};
int N, M;
vector<int> A(100010);
query Query[100010];
int ans[100010];
int cnt[1000010];
int distinctNumbers;
int sz;
int sqrt(int n)
{
	double ret = n;
	for (int i = 0; i < 16; ++i)
	{
		ret = ret - (ret*ret - n) / (ret * 2);
	}
	return (int)ret;
}
bool cmp(query l, query r)
{
	int lIdx = l.hi / sz;
	int rIdx = r.hi / sz;
	if (lIdx == rIdx)
		return l.lo < r.lo;
	else
		return lIdx < rIdx;
}
int partition(int left, int right)
{
	query tmp;
	int low = left;
	int high = right;
	while (1) {
		do {
			low++;
		} while (low < right&&cmp(Query[low], Query[left]));
		do {
			high--;
		} while (left < high&&cmp(Query[left], Query[high]));
		if (high < low)
			break;
		tmp = Query[low];
		Query[low] = Query[high];
		Query[high] = tmp;
	}
	tmp = Query[left];
	Query[left] = Query[high];
	Query[high] = tmp;
	return high;
}

void quicksort(int left, int right) {
	if (right <= left)
		return;
	int pivot = partition(left, right);
	quicksort(left, pivot);
	quicksort(pivot + 1, right);
}

void add(int num)
{
	if (++cnt[num] == 1)
		++distinctNumbers;
}
void erase(int num)
{
	if (--cnt[num] == 0)
		--distinctNumbers;
}

int main()
{
	scanf("%d", &N);
	sz = sqrt(N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &A[i]);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
	{
		Query[i].idx = i;
		int cc, dd;
		scanf("%d %d", &cc, &dd);
		Query[i].lo = cc - 1;
		Query[i].hi = dd - 1;
	}
	quicksort(0, M);
	int lo = 0, hi = 0;
	add(A[0]);
	for (int i = 0; i < M; ++i)
	{
		query cur = Query[i];
		int nlo = cur.lo, nhi = cur.hi;
		for (int j = lo; j < nlo; ++j)
			erase(A[j]);
		for (int j = lo - 1; nlo <= j; --j)
			add(A[j]);
		for (int j = hi; nhi < j; --j)
			erase(A[j]);
		for (int j = hi + 1; j <= nhi; ++j)
			add(A[j]);
		lo = nlo;
		hi = nhi;
		ans[cur.idx] = distinctNumbers;
	}
	for (int i = 0; i < M; ++i)
	{
		printf("%d\n", ans[i]);
	}
}