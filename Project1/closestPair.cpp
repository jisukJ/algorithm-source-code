#include <iostream>
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
	vector(int size = 1) {
		_capacity = size;
		arr = new T[_capacity];
	}
	vector(const vector &ref) {
		_capacity = ref._capacity;
		_size = ref._size;
		arr = new T[_capacity];
		for (int i = 0; i < _size; ++i) {
			arr[i] = ref.arr[i];
		}
	}
	~vector() {
		if (arr) {
			delete[] arr;
		}
	}

	void push_back(T val) {
		if (_size == _capacity) {
			_capacity *= 2;
			T* tmp = new T[_capacity];
			for (int i = 0; i < _size; ++i) {
				tmp[i] = arr[i];
			}
			delete[] arr;
			arr = new T[_capacity];
			for (int i = 0; i < _size; ++i) {
				arr[i] = tmp[i];
			}
			delete[] tmp;
		}
		arr[_size++] = val;
	}

	void pop_back() {
		_size--;
	}

	void clear() {
		delete[] arr;
		_capacity = 1;
		_size = 0;

		arr = new T[_capacity];
	}
	T& operator[](int i) {
		return arr[i];
	}
	void operator=(const vector& ref) {
		if (arr) {
			delete[] arr;
		}
		_capacity = ref._capacity;
		_size = ref._size;
		arr = new T[_capacity];
		for (int i = 0; i < _size; ++i) {
			arr[i] = ref.arr[i];
		}
	}
};

using namespace std;

struct Point {
	long long x, y;
	Point() : x(0), y(0) {}
	Point(long long _x, long long _y) : x(_x), y(_y) {}
};
bool cmp1(Point a, Point b) {
	if (a.x == b.x) {
		return a.y < b.y;
	} else {
		return a.x < b.x;
	}
}
bool cmp2(Point a, Point b) {
	if (a.y == b.y) {
		return a.x < b.x;
	} else {
		return a.y < b.y;
	}
}
void quicksort1(vector<Point>&arr, int left, int right) {
	if (right - 1 <= left) {
		return;
	}
	int st = left;
	int ed = right;
	int pivot = left;
	Point tmp;
	while (1) {
		do {
			st++;
		} while (st < right&&cmp1(arr[st], arr[pivot]));
		do {
			ed--;
		} while (left < ed&&cmp1(arr[pivot], arr[ed]));
		if (ed <= st) {
			tmp = arr[pivot];
			arr[pivot] = arr[ed];
			arr[ed] = tmp;
			break;
		} else {
			tmp = arr[st];
			arr[st] = arr[ed];
			arr[ed] = tmp;
		}
	}
	quicksort1(arr, left, ed);
	quicksort1(arr, ed + 1, right);
}
void quicksort2(vector<Point>&arr, int left, int right) {
	if (right - 1 <= left) {
		return;
	}
	int st = left;
	int ed = right;
	int pivot = left;
	Point tmp;
	while (1) {
		do {
			st++;
		} while (st < right&&cmp2(arr[st], arr[pivot]));
		do {
			ed--;
		} while (left < ed&&cmp2(arr[pivot], arr[ed]));
		if (ed <= st) {
			tmp = arr[pivot];
			arr[pivot] = arr[ed];
			arr[ed] = tmp;
			break;
		} else {
			tmp = arr[st];
			arr[st] = arr[ed];
			arr[ed] = tmp;
		}
	}
	quicksort2(arr, left, ed);
	quicksort2(arr, ed + 1, right);
}

int N;
const long long INF = 1000000000000;
vector<Point>P;

long long min(long long a, long long b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}
long long distance(Point a, Point b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

long long closestPair(int left, int right) {
	if (right <= left) {
		return INF;
	} else {
		int mid = (left + right) / 2;
		long long minL = closestPair(left, mid);
		long long minR = closestPair(mid + 1, right);
		long long ret = min(minL, minR);
		vector<Point>tmpL;
		vector<Point>tmpR;
		for (int i = left; i <= mid; ++i) {
			if ((P[mid].x - P[i].x)*(P[mid].x - P[i].x) <= ret) {
				tmpL.push_back(P[i]);
			}
		}
		for (int i = mid + 1; i <= right; ++i) {
			if ((P[mid].x - P[i].x)*(P[mid].x - P[i].x) <= ret) {
				tmpR.push_back(P[i]);
			}
		}
		quicksort2(tmpL, 0, tmpL.size());
		quicksort2(tmpR, 0, tmpR.size());
		int tmpRstart = 0;
		for (int i = 0; i < tmpL.size(); ++i) {
			for (int j = tmpRstart; j < tmpRstart + 6; ++j) {
				if (tmpR.size() <= j) {
					break;
				}
				if (tmpR[j].y < tmpL[i].y - ret) {
					if (j == tmpRstart) {
						tmpRstart++;
					}
				} else {
					ret = min(ret, distance(tmpL[i], tmpR[j]));
				}
			}
		}
		return ret;
	}
}

long long closestPair2(int left, int right) {
	long long ret = INF;
	bool flag = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			ret = min(ret, distance(P[i], P[j]));
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
		cin >> N;
		P.clear();
		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> x >> y;
			P.push_back(Point(x, y));
		}
		quicksort1(P, 0, N);
		cout << closestPair(0, N - 1) << "\n";
}