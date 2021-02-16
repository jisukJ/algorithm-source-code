#include <iostream>

using namespace std;

int C, N, Q;
int new_num[100000];
int num_new[100000];
int numberlist[250000];
int locInTrip[100000];
int num_cnt, cnt;
int depth;

int min(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

struct node {
	int data;

	node *prev, *next;
	node(int a) : data(a), prev(NULL), next(NULL) {}
};
struct LinkedList {
	node *head, *tail;
	int rank;
	LinkedList() : head(NULL), tail(NULL), rank(0) {}
};
void append(LinkedList* list, node* newnode)
{
	if (list->head == NULL)
	{
		list->head = newnode;
		list->tail = newnode;
		return;
	}
	else
	{
		list->tail->next = newnode;
		newnode->prev = list->tail;
		list->tail = newnode;
		return;
	}
}
LinkedList *list[100000];
void traversal(LinkedList* traversal_list, int seed)
{
	node* tmp;
	tmp = traversal_list->head;
	traversal_list->rank = depth;
	if (locInTrip[seed] == 0)
		locInTrip[seed] = cnt;
	numberlist[cnt++] = seed;
	while (tmp)
	{
		new_num[tmp->data] = num_cnt;
		num_new[num_cnt] = tmp->data;
		num_cnt++;
		depth++;
		traversal(list[tmp->data], new_num[tmp->data]);
		depth--;
		numberlist[cnt++] = seed;
		tmp = tmp->next;
	}
	return;
}

struct RMQ {
	int n;
	int* rangemin;
	RMQ(int arr[])
	{
		n = cnt;
		rangemin = new int[n * 4];
		init(arr, 0, n - 1, 0);
	}
	int init(int arr[], int left, int right, int node)
	{
		if (left == right)
			return rangemin[node] = arr[left];
		int mid = (left + right) / 2;
		return rangemin[node] =
			min(init(arr, left, mid, node * 2 + 1), init(arr, mid + 1, right, node * 2 + 2));
	}
	int query(int left, int right, int nodeLeft, int nodeRight, int node)
	{
		if (right < nodeLeft || nodeRight < left)
			return 200000;
		if (left <= nodeLeft && nodeRight <= right)
			return rangemin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, nodeLeft, mid, node * 2 + 1), query(left, right, mid + 1, nodeRight, node * 2 + 2));
	}
	int query(int left, int right)
	{
		return query(left, right, 0, n - 1, 0);
	}
};

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N >> Q;
		for (int i = 0; i < N; ++i)
		{
			list[i] = new LinkedList();
			locInTrip[i] = 0;
		}
		for (int i = 1; i <= N - 1; ++i)
		{
			int a;
			cin >> a;
			append(list[a], new node(i));
		}
		new_num[0] = 0;
		num_cnt = 1;
		cnt = 0;
		depth = 0;
		traversal(list[0], 0);
		RMQ rmq = RMQ(numberlist);
		for (int i = 0; i < Q; ++i)
		{
			int tmp1, tmp2;
			cin >> tmp1 >> tmp2;
			int tmp3 = new_num[tmp1];
			int tmp4 = new_num[tmp2];
			if (tmp4 < tmp3)
				swap(tmp3, tmp4);
			int ans = num_new[rmq.query(locInTrip[tmp3], locInTrip[tmp4])];
			ans = list[ans]->rank;
			ans += ans;
			ans = list[tmp1]->rank + list[tmp2]->rank - ans;
			cout << ans << endl;
		}
	}
}