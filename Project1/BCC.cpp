#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
using namespace std;

int V, E;

vector<vector<int>>adj(100000);
vector<int>discovered(100000, -1);
vector<vector<pair<int, int>>>BCC;
stack<pair<int, int>>S;
int counter = 0;

int dfs(int here, int before) {
	discovered[here] = counter++;
	int ret = discovered[here];
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (there == before) {
			continue;
		}
		if (discovered[here] > discovered[there]) {
			S.push({here,there});
		}
		if (0 <= discovered[there]) {
			ret = min(ret, discovered[there]);
		} else {
			int subtree = dfs(there, here);
			ret = min(ret, subtree);
			if (discovered[here] <= subtree) {
				vector<pair<int, int>>tmpBCC;
				while (!S.empty() && S.top() != make_pair(here,there)) {
					tmpBCC.push_back(S.top());
					S.pop();
				}
				tmpBCC.push_back(S.top());
				S.pop();
				BCC.push_back(tmpBCC);
			}
		}

	}
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
}