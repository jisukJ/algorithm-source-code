#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;
int V;
vector<pair<int, int>> adj[MAX_V];

int prim(vector<pair<int, int>>&selected)
{
	selected.clear();
	int ret = 0;
	vector<bool>added(V, false);
	vector<int>minWeight(V, INF), parent(V, -1);
	int ret = 0;
	minWeight[0] = parent[0] = 0;
	for (int iter = 0; iter < V; ++iter)
	{
		int u = -1;
		for (int v = 0; v < V; ++v)
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;
		for (int i = 0; i < adj[u].size(); ++i)
		{
			int v = adj[u][i].first, weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight)
			{
				parent[v] = u;
				minWeight[v] = weight;
			}
		}
	}
	return ret;
}
int prim2(vector<pair<int, int>>&selected)
{
	vector<bool>visited(V, false);
	int ret = 0;
	visited[0] = true;
	priority_queue<pair<int,pair<int, int>>>pq;
	for (int i = 0; i < adj[0].size(); ++i)
	{
		int before = 0;
		int next = adj[0][i].first;
		int cost = adj[0][i].second;
		pq.push(make_pair(-cost,make_pair(before, next)));
	}
	while (!pq.empty())
	{
		int before = pq.top().second.first;
		int here = pq.top().second.second;
		int cost = -pq.top().first;
		pq.pop();
		if (visited[here])
			continue;
		visited[here] = true;
		selected.push_back(make_pair(before, here));
		ret += cost;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			int nextCost = adj[here][i].second;
			if(visited[there]==false)
			pq.push(make_pair(-nextCost, make_pair(here,there)));
		}
	}
	return ret;
}

int main()
{

}