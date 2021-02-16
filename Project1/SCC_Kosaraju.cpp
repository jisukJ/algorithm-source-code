#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <stack>
using namespace std;

int V, E, sccSize;
vector<vector<int>>adj(10000);
vector<vector<int>>readj(10000);
vector<bool>visited(10000, false);
stack<int>st;
vector<vector<int>>scc;

bool cmp(vector<int>x, vector<int>y) {
	return x[0] < y[0];
}

void dfs(int here) {
	visited[here] = true;
	for (int i = 0; i < adj[here].size(); ++i) {
		int next = adj[here][i];
		if (visited[next]) {
			continue;
		}
		dfs(next);
	}
	st.push(here);
}

void func(int here) {
	visited[here] = true;
	scc[sccSize - 1].push_back(here);
	for (int i = 0; i < readj[here].size(); ++i) {
		int next = readj[here][i];
		if (visited[next]) {
			continue;
		}
		func(next);
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
		readj[b].push_back(a);
	}
	for (int i = 0; i < V; ++i) {
		if (visited[i]) {
			continue;
		}
		dfs(i);
	}
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	while (!st.empty()) {
		int here = st.top();
		st.pop();
		if (visited[here]) {
			continue;
		}
		scc.resize(++sccSize);
		func(here);
	}
	for (int i = 0; i < sccSize; ++i) {
		sort(scc[i].begin(), scc[i].end());
	}
	sort(scc.begin(), scc.end(), cmp);
	cout << scc.size() << "\n";
	for (int i = 0; i < sccSize; ++i) {
		for (int j = 0; j < scc[i].size(); ++j) {

			cout << scc[i][j]+1 << " ";
		}
		cout << "-1\n";
	}
}