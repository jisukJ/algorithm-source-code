#include <iostream>

using namespace std;

#define MAXN 100

struct node {
	int val;
	node *left, *right;
	node() {}
	node(node *l, node* r, int val) : left(l), right(r), val(val) {}
};
int arr[MAXN];
node* version[MAXN];

void build(node* n, int left, int right)
{
	if (left == right)
	{
		n->val = arr[left];
		return;
	}
	int mid = (left + right) / 2;
	n->left = new node(nullptr, nullptr, 0);
	n->right = new node(nullptr, nullptr, 0);
	build(n->left, left, mid);
	build(n->right, mid + 1, right);
	n->val = n->left->val + n->right->val;
}

void upgrade(node* prev, node* cur, int left, int right, int idx, int val)
{
	if (idx < left || right < idx)
		return;
	if (left == right)
	{
		cur->val = val;
		return;
	}
	int mid = (left+right) / 2;
	if (idx <= mid)
	{
		cur->right = prev->right;
		cur->left = new node(nullptr, nullptr, 0);
		upgrade(prev->left, cur->left, left, mid, idx, val);
	}
	else
	{
		cur->left = prev->left;
		cur->right = new node(nullptr, nullptr, 0);
		upgrade(prev->right, cur->right, mid + 1, right, idx, val);
	}
	cur->val = cur->left->val + cur->right->val;
}
int query(node* n, int nodeLeft, int nodeRight, int left, int right)
{
	if (nodeRight < left || right < nodeLeft)
		return 0;
	if (nodeLeft <= left && right <= nodeRight)
		return n->val;
	int mid = (nodeLeft + nodeRight) / 2;
	int ret1 = query(n->left, nodeLeft, mid, left, right);
	int ret2 = query(n->right, mid + 1, nodeRight, left, right);
	return ret1 + ret2;
}

int main(int argc, char const *argv[])
{
	int A[] = { 1,2,3,4,5 };
	int n = sizeof(A) / sizeof(int);

	for (int i = 0; i < n; i++)
		arr[i] = A[i];

	// creating Version-0 
	node* root = new node(NULL, NULL, 0);
	build(root, 0, n - 1);

	// storing root node for version-0 
	version[0] = root;

	// upgrading to version-1 
	version[1] = new node(NULL, NULL, 0);
	upgrade(version[0], version[1], 0, n - 1, 4, 1);

	// upgrading to version-2 
	version[2] = new node(NULL, NULL, 0);
	upgrade(version[1], version[2], 0, n - 1, 2, 10);

	cout << "In version 1 , query(0,4) : ";
	cout << query(version[1], 0, n - 1, 0, 4) << endl;

	cout << "In version 2 , query(3,4) : ";
	cout << query(version[2], 0, n - 1, 3, 4) << endl;

	cout << "In version 0 , query(0,3) : ";
	cout << query(version[0], 0, n - 1, 0, 3) << endl;
	return 0;
}
