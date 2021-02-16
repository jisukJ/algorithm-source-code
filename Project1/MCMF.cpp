#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;
const int INF = 987654321;

int capacity[202][202];
int cost[202][202];
int flow[202][202];
int source = 0;
int sink = 201;
vector<int>adj[202];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 101; i < 101 + N;  ++i) {
		cin >> capacity[i][sink];
		adj[i].push_back(sink);
		adj[sink].push_back(i);
	}
	for (int i = 1; i < 1 + M; ++i) {
		cin >> capacity[source][i];
		adj[source].push_back(i);
		adj[i].push_back(source);
	}
	for (int i = 1; i <1+ M; ++i) {
		for (int j = 101; j < 101 + N; ++j) {
			cin >> cost[i][j];
			cost[j][i] = -cost[i][j];
			capacity[i][j] = INF;
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
	}
	int totalCost = 0;
	while (1) {
		vector<int>parent(202, -1);
		vector<int>dist(202, INF);
		vector<bool>inQ(202,false);
		queue<int>Q;
		dist[source] = 0;
		inQ[source] = true;
		Q.push(source);
		while (!Q.empty()) {
			int here = Q.front();
			Q.pop();
			inQ[here] = false;
			for (int there : adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0 && dist[there] > dist[here] + cost[here][there]) {
					dist[there] = dist[here] + cost[here][there];
					parent[there] = here;
					if (!inQ[there]) {
						Q.push(there);
						inQ[there] = true;
					}
				}
			}
		}
		if (parent[sink] == -1) {
			break;
		}
		int amt = INF;
		for (int p = sink; p != source; p = parent[p]) {
			amt = min(amt, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amt;
			flow[p][parent[p]] -= amt;
			totalCost += amt * cost[parent[p]][p];
		}
	}
	cout << totalCost;
}