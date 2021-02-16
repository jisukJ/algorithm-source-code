#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class ListNode {
public:
	T value;
	ListNode<T> *next;
	ListNode() : next(nullptr) {}
	ListNode(T _value, ListNode<T> *_next){
		value = _value;
		next = _next;
	}
};

template<typename T>
class LinkedList {
public:
	int size;
	ListNode<T> *head;

	LinkedList(){
		size = 0;
		head = nullptr;
	}

	~LinkedList() {
		ListNode<T> *t1 = head, *t2;
		while (t1 != nullptr) {
			t2 = t1->next;
			delete t1;
			t1 = t2;
		}
	}

	void insert(int k, T value) {
		if (k < 0 || k > size) {
		} else if (k == 0) {
			head = new ListNode<T>(value, head);
		} else {
			ListNode<T> *dest = head;
			for (int i = 0; i < k - 1; i++) 
				dest = dest->next;
			dest->next = new ListNode<T>(value, dest->next);
		}
		size++;
	}

	void erase(int k) {
		if (k < 0 || k >= size) {
		} else if (k == 0) {
			ListNode<T> *temp = head->next;
			delete head;
			head = temp;
		} else {
			ListNode<T> *dest = head, *temp;
			for (int i = 0; i < k - 1; i++) 
				dest = dest->next;
			temp = dest->next->next;
			delete dest->next;
			dest->next = temp;
		}
		size--;
	}

	int search(T value) {
		ListNode<T> *temp = head;
		for (int i = 0; i < size; i++) {
			if (temp->value == value) return i;
			temp = temp->next;
		}
		return -1;
	}
};


int N, K;
vector<int> ans;
int main() {
	LinkedList<int> LL;
	scanf("%d %d", &N, &K);
	for (int i = N; 0 < i; --i) {
		LL.insert(0, i);
	}

	ListNode<int>* pointerForListNode = LL.head;
	
	int idx = 0;
	while (0 < LL.size) {
		int k = 1;
		while (k < K) {
			++k;
			++idx;
			pointerForListNode = pointerForListNode->next;
			if (pointerForListNode == nullptr) {
				idx = 0;
				pointerForListNode = LL.head;
			}
		}
		ans.push_back(pointerForListNode->value);
		pointerForListNode = pointerForListNode->next;
		LL.erase(idx);
		if (pointerForListNode == nullptr) {
			idx = 0;
			pointerForListNode = LL.head;
		}
	}
	printf("<");
	for (int i = 0; i < ans.size() - 1; ++i) {
		printf("%d, ", ans[i]);
	}
	printf("%d>", ans[ans.size() - 1]);
}

