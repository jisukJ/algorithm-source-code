#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E;
vector<vector<int>>adj(100000);
vector<int>discovered(100000,-1);
vector<pair<int, int>>ans;
int counter = 0;
int findBridge(int here,int before) {
	discovered[here] = counter ++;
	int ret = discovered[here];
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (there == before)
			continue;
		if (discovered[there] == -1) {
			int subtree=findBridge(there,here);
			if (discovered[here] < subtree) {
				ans.push_back({ here,there });
			}
			ret = min(ret, subtree);
		} else {
			ret = min(ret, discovered[there]);
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
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
			findBridge(i,i);
		}
	}
	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); ++i) {
		if (ans[i].first > ans[i].second) {
			swap(ans[i].first, ans[i].second);
		}
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i].first+1 << " " << ans[i].second+1 << "\n";
	}
}