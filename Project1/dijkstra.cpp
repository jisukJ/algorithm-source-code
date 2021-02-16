#include <iostream>
#include <queue>
using namespace std;

const int MAX_V = 20000;
const int INF =1000000000;
int V, E;

vector<pair<int, int>>adj[MAX_V];

vector<int> dijkstra(int src)
{
	vector<int>dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>>pq;
	pq.push(make_pair(0, src));
	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int here = pq.top().second;
		if (dist[here] < cost)
			continue;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			int nextDist = cost+adj[here][i].second;
			if (nextDist < dist[there])
			{
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

vector<int> dijkstra2(int src)
{
	vector<int> dist(V, INF);
	vector<bool>visited(V, false);
	dist[src] = 0;
	visited[src] = true;
	while (true) 
	{
		int closet = INF, here;
		for (int i = 0; i < V; ++i)
			if (dist[i] < closet && !visited[i]) {
				here = i;
				closet = dist[i];
			}
		if (closet == INF)
			break;
		visited[here] = true;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			if (visited[there])
				continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
			}
	return dist;
}

int main()
{
	int K;
	cin >> V >> E;
	cin >> K;
	int a, b, c;
	for (int i = 0; i < E; ++i)
	{
		scanf("%d %d %d", &a, &b, &c);
		--a;
		--b;
		adj[a].push_back(make_pair(b, c));
	}
	vector<int> ans = dijkstra(K-1);
	for (int i = 0; i < V; ++i)
	{
		if (ans[i] != INF)
			printf("%d\n", ans[i]);
		else
			printf("INF\n");
	}
}