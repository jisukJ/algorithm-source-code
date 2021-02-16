#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;



struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int v) :parent(v), rank(v) {
		for (int i = 0; i < v; ++i)
			parent[i] = i;
	}
	int find(int u)
	{
		if (u == parent[u])
			return u;
		else
			return parent[u] = find(parent[u]);
	}
	void merge(int u, int v)
	{
		u = find(u); v = find(v);
		if (u == v)
			return;
		if (rank[u] > rank[v])
			swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v])
			++rank[v];
	}
};
const int MAX_V = 100;
int V;
vector<pair<int, int>>adj[MAX_V];

int kruscal(vector<pair<int, int>>& selected)
{
	int ret = 0;
	selected.clear();
	vector<pair<int, pair<int, int>>>edges;
	for(int u=0;u<V;++u)
		for (int i = 0; i < adj[u].size(); ++i)
		{
			int v = adj[u][i].first, cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	sort(edges.begin(), edges.end());

	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); ++i)
	{
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		if (sets.find(u) == sets.find(v))
			continue;
		sets.merge(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}

#define MAX_NODE 10001
typedef pair<int, int> pii;
bool visit[MAX_NODE];
vector<pii> vc[MAX_NODE];

void prim(int start)
{
	visit[start] = true;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 0; i < vc[start].size(); i++)
	{
		int next = vc[start][i].first;
		int nextCost = vc[start][i].second;

		pq.push(pii(nextCost, next));
	}

	int ans = 0;

	while (!pq.empty())
	{
		int here = pq.top().second;
		int hereCost = pq.top().first;
		pq.pop();
		if (visit[here])
			continue;
		visit[here] = true;
		ans += hereCost;
		for (int i = 0; i < vc[here].size(); i++)
		{
			int there = vc[here][i].first;
			int thereCost = vc[here][i].second;

			pq.push(pii(thereCost, there));
		}
	}
	printf("%d", ans);
}
int main()
{

}