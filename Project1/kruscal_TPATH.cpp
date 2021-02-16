#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

const int MAX_V = 2000;
vector<pair<int, int>>adj[MAX_V];
int V, E,C;
int ans;
const int INF = 1000000000;
vector<pair<int,pair<int,int>>> weight;
vector<int>edges;

struct disjointSet {
	vector<int>rank, parent;
	disjointSet(int val) : rank(val), parent(val) {
		for (int i = 0; i < val; ++i)
			parent[i] = i;
	}
	int find(int u)
	{
		if (parent[u] == u)
			return u;
		else parent[u] = find(parent[u]);
	}
	void merge(int u, int v)
	{
		u = find(u), v = find(v);
		if (u == v)
			return;
		if (rank[u] < rank[v])
			swap(u, v);
		parent[v] = u;
		if (rank[u] == rank[v])
			rank[u]++;
	}
};

int kruscal(vector<pair<int,int>>& selected , int lo,int hi)
{
	selected.clear();
	int ret = weight[hi].first - weight[lo].first;
	disjointSet set(V);
	for (int i = lo; i <= hi; ++i)
	{
		int u=weight[i].second.first;
		int v = weight[i].second.second;
		if (set.find(u) ==set.find(v))
			continue;
		selected.push_back(make_pair(u, v));
		set.merge(u, v);
	}
	return ret;
}

bool hasPath(int hi, int lo) 
{
	queue<int> q;
	vector<int> visit(MAX_V, 0);
	q.push(0);
	visit[0] = 1;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		if (here == V - 1) break;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int velocity = adj[here][i].second;
			if (velocity<lo || velocity>hi || visit[there]) continue;
			visit[there] = 1;
			q.push(there);
		}
	}
	if (visit[V - 1]) return true;
	return false;
}
int minUpperBound(int low)
{
	int lo = low - 1, hi = edges.size();
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (hasPath(edges[low], edges[mid]))
			hi = mid;
		else
			lo = mid;
	}
	if (hi == edges.size())
		return INF;
	return edges[hi];
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> V >> E;
		for (int i = 0; i < V; ++i)
			adj[i].clear();
		weight.clear();
		edges.clear();
		for (int i = 0; i < E; ++i)
		{
			int a, b, c;
			cin >> a >> b >> c;
			if(c!=0)
			{
				adj[a].push_back(make_pair(b, c));
				adj[b].push_back(make_pair(a, c));
				weight.push_back(make_pair(c,make_pair(a,b)));
				weight.push_back(make_pair(c, make_pair(b, a)));
				edges.push_back(c);
			}
		}
		sort(edges.begin(), edges.end());
		sort(weight.begin(), weight.end());
		ans = 1000;
		cout << ans<<endl;
	}
}