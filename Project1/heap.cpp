#include <iostream>

using namespace std;

template <typename T>
class priority_queue {
private:
	int _size = 0;
	int _capacity = 0;
	T* arr;
public:
	int size() {
		return _size;
	}
	bool empty() {
		return _size == 0;
	}
	priority_queue(int s = 1) {
		_capacity = s;
		arr = new T[_capacity];
	}
	~priority_queue() {
		if (arr)
			delete[] arr;
	}
	T top() {
		return arr[0];
	}
	void push(T val) {
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
		int here = _size - 1;
		while (0 < here&&arr[(here - 1) / 2] < arr[here]) {
			T tmp = arr[(here - 1) / 2];
			arr[(here - 1) / 2] = arr[here];
			arr[here] = tmp;
			here = (here - 1) / 2;
		}
	}
	void pop() {
		if (_size == 0) {
			return;
		}
		arr[0] = arr[--_size];
		int here = 0;
		while (1) {
			int next = here, left = here * 2 + 1, right = here * 2 + 2;
			if (_size <= left) {
				break;
			}
			if (arr[next] < arr[left]) {
				next = left;
			}
			if (right < _size&&arr[next] < arr[right]) {
				next = right;
			}
			if (next == here) {
				break;
			}
			T tmp = arr[here];
			arr[here] = arr[next];
			arr[next] = tmp;
			here = next;
		}
	}
};

int main()
{

}
