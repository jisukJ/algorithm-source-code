#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_V = 200;
const int INF = 987654321;
int V;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int source, int sink)
{
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		queue<int>q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();
			for (int there = 0; there < V; ++there) {
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1)
			break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

struct Edge {
	int target, capacity, flow;
	Edge* reverse;
	int residualCapacity() {
		return capacity - flow;
	}
	void push(int amt) {
		flow += amt;
		reverse->flow -= amt;
	}
};

vector<Edge*> adj[20000];

void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge(), *vu = new Edge();
	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;
	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;
	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

int networkFlow(int src, int snk) {
	int totalFlow = 0;
	while (true) {
		vector<int>parent(MAX_V, -1);
		vector<Edge*>path(MAX_V, nullptr);
		queue<int>q;
		parent[src] = src;
		q.push(src);
		while (!q.empty() && parent[snk] == -1) {
			int here = q.front();
			q.pop();
			for (int i = 0; i < adj[here].size(); ++i) {
				Edge* tmp = adj[here][i];
				if (parent[tmp->target] == -1 && 0 < tmp->residualCapacity()) {
					q.push(tmp->target);
					parent[tmp->target] = here;
					path[tmp->target] = tmp;
				}
			}
		}
		if (parent[snk] == -1) {
			break;
		}
		int amt = 987654321;
		for (int p = snk; p != src; p = parent[p]) {
			amt = min(amt, path[p]->residualCapacity());
		}
		for (int p = snk; p != src; p = parent[p]) {
			path[p]->push(amt);
		}
		totalFlow += amt;
	}
	return totalFlow;
}
/*min Cut 에 속하는 간선은 dfs로 쉽게 탐색가능 

void dfs(int here) {
	visited[here] = 1;
	for (int i = 0; i < V; ++i) {
		if (visited[i] == -1 && capacity[here][i] - flow[here][i] > 0) {
			dfs(i);
		}
	}
}

for (int i = 0; i < V; i++)
	for (int j = 0; j < V; j++)
		if (visited[i] && !visited[j] && graph[i][j])
			cout << i << " - " << j << endl;
	*/