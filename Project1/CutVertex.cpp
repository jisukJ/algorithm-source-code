#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

vector<vector<int>>adj(10000);
vector<int>discovered(10000, -1);
vector<bool>isCutVertex(10000, false);
int counter = 0;

int V, E;

int findCutVertex(int here, bool isRoot) {
	discovered[here] = counter++;
	int ret = discovered[here];
	int children = 0;
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (discovered[there] == -1) {
			++children;
			int subtree = findCutVertex(there, false);
			if (!isRoot&&discovered[here] <= subtree) {
				isCutVertex[here] = true;
			}
			ret = min(ret, subtree);
		} else {
			ret = min(ret, discovered[there]);
		}
	}
	if (isRoot) {
		isCutVertex[here] = (2 <= children);
	}
	return ret;
}

int main() {
	cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 0; i < V; ++i) {
		if (discovered[i] == -1) {
			findCutVertex(i, true);
		}
	}
	vector<int>ans;
	for (int i = 0; i < V; ++i) {
		if (isCutVertex[i]) {
			ans.push_back(i);
		}
	}
	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i] + 1 << " ";
	}
}