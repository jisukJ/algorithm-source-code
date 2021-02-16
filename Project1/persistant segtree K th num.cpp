#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

struct node {
	int val;
	node *l, *r;
	node(int v, node* l, node* r) : val(v), l(l), r(r){}
};
int N, M;
node* Vs[100001];
int Arr[100001];
int Copy[100001];
int Rank[100001];
map<int, int> MAP;
void init(node* n, int left, int right)
{
	if (left == right)
	{
		n->val = 0;
		return;
	}
	int mid = (left + right) / 2;
	n->l = new node(0, nullptr, nullptr);
	n->r = new node(0, nullptr, nullptr);
	init(n->l, left, mid);
	init(n->r, mid + 1, right);
	n->val = n->l->val + n->r->val;
	return;
}

void upgrade(node* prev, node* cur, int left, int right, int idx, int val)
{
	if (idx < left || right < idx)
		return;
	if (left == right)
	{
		cur->val += val;
		return;
	}
	int mid = (left + right) / 2;
	if (idx <= mid)
	{
		cur->r = prev->r;
		cur->l = new node(0, nullptr, nullptr);
		upgrade(prev->l, cur->l, left, mid, idx, val);
	}
	else
	{
		cur->l = prev->l;
		cur->r = new node(0, nullptr, nullptr);
		upgrade(prev->r, cur->r, mid + 1, right, idx, val);
	}
	cur->val = cur->l->val + cur->r->val;
	return;
}
int query(node* prev, node* cur, int kth,int idxL, int idxR)
{
	if (idxL==idxR)
		return idxL;
	if (kth<=cur->l->val - prev->l->val)
	{
		return query(prev->l, cur->l,kth,idxL,(idxR+idxL)/2);
	}
	else
	{
		return query(prev->r, cur->r, kth - (cur->l->val - prev->l->val),(idxR + idxL) / 2+1,idxR);
	}
}
int query(int left, int right, int kth)
{
	return query(Vs[left - 1], Vs[right], kth,0,N-1);
}

int main()
{
	scanf("%d %d", &N, &M);
	node* root = new node(NULL, NULL, 0);
	init(root, 0, N - 1);
	Vs[0] = root;
	node* tmp = Vs[0];
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", &Arr[i]);
		Copy[i] = Arr[i];
	}
	sort(Copy+1, Copy + N+1);
	for (int i = 1; i <= N; ++i)
		MAP[Copy[i]] = i-1;
	map<int, int>::iterator iter;
	for (int i = 1; i <= N; ++i)
	{
		Vs[i] = new node(NULL, NULL, 0);
		upgrade(Vs[i - 1], Vs[i], 0, N - 1, MAP[Arr[i]], 1);
		Rank[MAP[Arr[i]]] = Arr[i];
	}
	for (int i = 0; i < M; ++i)
	{
		int a1, a2, a3;
		scanf("%d %d %d", &a1, &a2, &a3);
		//printf("%d\n", query(a1, a2, a3));
		//iter = MAP.find(query(a1, a2, a3));
		printf("%d\n",Rank[query(a1, a2, a3)]);
	}
}