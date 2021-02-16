#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

struct Node {
	int key;
	Node *left, *right;
	int size, priority;
	Node(int _key) : key(_key), left(nullptr), right(nullptr), size(1), priority(rand()) {}
	void setLeft(Node* node) {
		left = node;
		calcSize();
	}
	void setRight(Node* node) {
		right = node;
		calcSize();
	}
	void calcSize() {
		size = 1;
		if (left) {
			size += left->size;
		}
		if (right) {
			size += right->size;
		}
	}
};
struct NodePair {
	Node* left;
	Node* right;
	NodePair(Node* _left, Node* _right) : left(_left), right(_right) {}
};

NodePair split(Node* root, int base_key) {
	NodePair splited(nullptr, nullptr);
	if (root == nullptr) {
		return splited;
	} else {
		if (root->key < base_key) {
			splited = split(root->right, base_key);
			root->setRight(splited.left);
			splited.left = root;
			return splited;
		} else {
			splited = split(root->left, base_key);
			root->setLeft(splited.right);
			splited.right = root;
			return splited;
		}
	}
}

Node* insert(Node* root, Node* node) {
	if (root == nullptr) {
		return node;
	}
	if (root->priority < node->priority) {
		NodePair splited = split(root, node->key);
		node->setLeft(splited.left);
		node->setRight(splited.right);
		return node;
	} else {
		if (root->key < node->key) {
			root->setRight(insert(root->right, node));
			return root;
		} else {
			root->setLeft(insert(root->left, node));
			return root;
		}
	}
}

Node* merge(Node* left, Node* right) {
	if (left == nullptr) {
		return right;
	} else if (right == nullptr) {
		return left;
	}
	if (left->priority < right->priority) {
		right->setLeft(merge(left, right->left));
		return right;
	} else {
		left->setRight(merge(left->right, right));
		return left;
	}
}

Node* erase(Node* root, int base_key) {
	if (root == nullptr) {
		return nullptr;
	} else {
		if (root->key == base_key) {
			Node* ret = merge(root->left, root->right);
			delete root;
			return ret;
		} else {
			if (root->key < base_key) {
				root->setRight(erase(root->right, base_key));
				return root;
			} else {
				root->setLeft(erase(root->left, base_key));
				return root;
			}
		}
	}
}
Node* kth(Node *root, int k) {
	int leftSize = 0;
	if (root->left != nullptr) {
		leftSize = root->left->size;
	}
	if (k <= leftSize) {
		return kth(root->left, k);
	} else if (k == leftSize + 1) {
		return root;
	} else {
		return kth(root->right, k - leftSize - 1);
	}
}

vector<int>first;
vector<int>second;
int arr[10000000];
Node* bst = nullptr;
int main() {
	clock_t st, ed;
	st = clock();
	for (int i = 0; i < 1000000; ++i) {
		arr[i] = i;
	}
	ed = clock();
	cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
	st = clock();
	for (int i = 0; i < 1000000; ++i) {
		first.push_back(i);
	}
	ed = clock();
	cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
	st = clock();

	for (int i = 0; i < 1000000; ++i) {
		bst = insert(bst, new Node(i));
	}
	ed = clock();
	cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
	st = clock();
	for (int i = 1; i <= 1000000; ++i) {
		second.push_back(kth(bst, i)->key);
	}
	ed = clock();
	cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
	cout << "END";
}
	//cout << (double)(ed-st) / CLOCKS_PER_SEC;