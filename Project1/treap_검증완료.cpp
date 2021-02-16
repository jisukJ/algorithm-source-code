#include <iostream>
#include <vector>
using namespace std;


struct Node
{
	int key;
	Node *left, *right;
	int size, priority;
	Node(int _key) :key(_key), left(nullptr), right(nullptr), size(1), priority(rand()) {}
	~Node() {
		
	}
	void setLeft(Node* node)
	{
		left = node;
		calcSize();
	}
	void setRight(Node* node)
	{
		right = node;
		calcSize();
	}
	void calcSize()
	{
		size = 1;
		if (left)
			size += left->size;
		if (right)
			size += right->size;
	}
};
struct NodePair
{
	Node *first, *second;
};

NodePair split(Node* root, int key)
{
	NodePair ret;
	if (root == nullptr) {
		ret.first = nullptr;
		ret.second = nullptr;
		return ret;
	}
	if (root->key <= key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		ret.first = root;
		ret.second = rs.second;
		return ret;
	} else {
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		ret.first = ls.first;
		ret.second = root;
		return ret;
	}
}
Node* insert(Node* root, Node* node)
{
	if (root == nullptr)
		return node;
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	if (root->key < node->key) {
		root->setRight(insert(root->right, node));
		return root;
	} else {
		root->setLeft(insert(root->left, node));
		return root;
	}
}

Node* merge(Node* a, Node* b)
{
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	} else {
		a->setRight(merge(a->right, b));
		return a;
	}
}
Node* erase(Node* root, int key)
{
	if (root == nullptr)
		return nullptr;
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	} else {
		if (root->key < key) {
			root->setRight(erase(root->right, key));
			return root;
		} else {
			root->setLeft(erase(root->left, key));
			return root;
		}
	}
}
Node* find(Node* root, int key)
{
	if (root == nullptr)
		return nullptr;
	if (root->key == key)
		return root;
	if (root->key < key)
		return find(root->right, key);
	else
		return find(root->left, key);
}
int N1, N2;

void clear(Node* root) {
	if (root->left)
		clear(root->left);
	if (root->right)
		clear(root->right);
	delete root;
}

int main()
{
	for (int iter = 0; iter  < 5; ++iter) {
		Node* BST1 = nullptr;
		for (int i = 0; i < 50000000; ++i) {
			BST1 = insert(BST1, new Node(rand()));
		}
		clear(BST1);
	}
	while (1);
}