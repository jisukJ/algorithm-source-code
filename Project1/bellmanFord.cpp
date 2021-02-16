#include <iostream>
#include <vector>

using namespace std;

int V;
const int MAX_V = 1000;
const int INF = numeric_limits<int>::max();
vector<pair<int, int>> adj[MAX_V];
int parent[MAX_V];

vector<int> bellmanFord(int src)
{
	vector<int>upper(V, INF);
	upper[src] = 0;
	bool updated;
	memset(parent, -1, sizeof(parent));
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[here] != INF && upper[here] + cost < upper[there]) {
					updated = true;
					upper[there] = upper[here] + cost;
					parent[there] = here;
				}
			}
		}
		if (updated == false)
			break;
	}
	if (updated == true)
		upper.clear();
	return upper;
}