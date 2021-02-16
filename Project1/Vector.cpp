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