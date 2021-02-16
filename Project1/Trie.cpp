#include <stdio.h>

int C, N, M;

struct Pair {
	int freq;
	char str[12];
};
Pair Dict[10000];
char Str[20000][12];

struct TrieNode {
	int terminal;
	int idx;
	TrieNode* children[26];
	TrieNode() : idx(-1),terminal(-1) {
		for (int i = 0; i < 26; ++i)
			children[i] = nullptr;
	}
	~TrieNode() {
		for (int i = 0; i < 26; ++i)
			if (children[i])
				delete children[i];
	}
	void insert(int id, const char* key)
	{
		if (idx == -1)
			idx = id;
		if (*key == 0)
		{
			terminal = id;
		}
		else
		{
			int next = *key - 'A';
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			children[next]->insert(id,key + 1);
		}
	}
	TrieNode* find(const char* key)
	{
		if (*key == 0)
			return this;
		else
		{
			int next = *key - 'A';
			if (children[next] == nullptr)
				return nullptr;
			return children[next]->find(key + 1);
		}
	}
	int type(const char*key, int id)
	{
		if (*key == 0)
			return 0;
		if (idx == id)
			return 1;
		int next = *key - 'A';
		return 1 + children[next]->type(key + 1, id);
	}
};
bool cmp(Pair& l, Pair& r)
{
	if (l.freq != r.freq)
		return r.freq < l.freq;
	int tmpcnt = 0;
	while (tmpcnt < 11)
	{
		if (l.str[tmpcnt] != r.str[tmpcnt])
			return l.str[tmpcnt] < r.str[tmpcnt];
		tmpcnt++;
	}
}
int partition(int left, int right)
{
	Pair tmp;
	int lo = left;
	int hi = right;
	while (1)
	{
		do {
			lo++;
		} while (lo < right&&cmp(Dict[lo], Dict[left]));
		do {
			hi--;
		} while (left < hi&&cmp(Dict[left], Dict[hi]));
		if (hi < lo)
			break;
		tmp = Dict[lo];
		Dict[lo] = Dict[hi];
		Dict[hi] = tmp;
	}
	tmp = Dict[hi];
	Dict[hi] = Dict[left];
	Dict[left] = tmp;
	return hi;
}
void qsort(int left, int right)
{
	if (right <= left)
		return;
	int pivot = partition(left, right);
	qsort(left, pivot);
	qsort(pivot + 1, right);
}
int main()
{
	scanf("%d", &C);
	for (int test = 0; test < C; ++test)
	{
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i)
			scanf("%s %d", &Dict[i].str,&Dict[i].freq);
		for (int i = 0; i < M; ++i)
			scanf("%s", &Str[i]);
		qsort(0, N);
		TrieNode* Trie=new TrieNode();
		for (int i = 0; i < N; ++i)
			Trie->insert(i,Dict[i].str);
		int ans = 0;
		Trie->idx = -1;
		for (int i = 0; i < M; ++i)
		{
			TrieNode* tmp=Trie->find(Str[i]);
			if (tmp != nullptr&&tmp->terminal!=-1)
			{
				ans += Trie->type(Str[i], tmp->terminal);
			}
			else
			{
				int tmpcnt = 0;
				while (Str[i][tmpcnt])
				{
					tmpcnt++;
				}
				ans += tmpcnt;
			}
		}
		ans += M - 1;
		printf("%d\n", ans);
	}
}