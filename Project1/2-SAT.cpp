#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int V, E;
vector<int> adj[20001];
vector<int>adjSCC[20001];
vector<int> readj[20001];
stack<int>st;
vector<int>SCC[20001];
int numInSCC[20001];
int indegreeSCC[20001];
int check[20010];
int sccSize = 0;
vector<int>SAT(20001, -1);
vector<int>visited(20001, -1);

void dfs(int here) {
	visited[here] = 1;
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (visited[there] == -1) {
			dfs(there);
		}
	}
	st.push(here);
}

void constructSCC(int here) {
	visited[here] = 1;
	SCC[sccSize].push_back(here);
	numInSCC[here] = sccSize;
	for (int i = 0; i < readj[here].size(); ++i) {
		int there = readj[here][i];
		if (visited[there] == -1) {
			constructSCC(there);
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
		if (0 < a && 0 < b) {
			adj[a + V].push_back(b);
			readj[b].push_back(a + V);
			adj[b + V].push_back(a);
			readj[a].push_back(b + V);
		} else if (0 < a && b < 0) {
			adj[a + V].push_back(abs(b) + V);
			readj[abs(b) + V].push_back(a + V);
			adj[abs(b)].push_back(a);
			readj[a].push_back(abs(b));
		} else if (a < 0 && 0 < b) {
			adj[abs(a)].push_back(b);
			readj[b].push_back(abs(a));
			adj[b + V].push_back(abs(a) + V);
			readj[abs(a) + V].push_back(b + V);
		} else {
			adj[abs(a)].push_back(abs(b) + V);
			readj[abs(b) + V].push_back(abs(a));
			adj[abs(b)].push_back(abs(a) + V);
			readj[abs(a) + V].push_back(abs(b));
		}
	}

	for (int i = 1; i <= V * 2; ++i) {
		if (visited[i] == -1) {
			dfs(i);
		}
	}

	for (int i = 1; i <= V * 2; ++i) {
		visited[i] = -1;
	}
	while (!st.empty()) {
		int here = st.top();
		st.pop();
		if (visited[here] != -1) {
			continue;
		}
		constructSCC(here);
		sccSize++;
	}
	for (int i = 0; i < sccSize; ++i) {
		for (int j = 0; j < SCC[i].size(); ++j) {
			int here = SCC[i][j];
			check[here]++;
			if (V < here) {
				if (0 < check[here - V]) {
					cout << 0;
					return 0;
				}
			} else {
				if (0 < check[here + V]) {
					cout << 0;
					return 0;
				}
			}
		}
		for (int j = 0; j < SCC[i].size(); ++j) {
			int here = SCC[i][j];
			check[here]--;
		}
	}
	cout << 1;
	for (int here = 1; here <= 2 * V; ++here) {
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];
			if (numInSCC[here] != numInSCC[there]) {
				adjSCC[numInSCC[here]].push_back(numInSCC[there]);
				indegreeSCC[numInSCC[there]]++;
			}
		}
	}
	//이미 위상정렬 되어있음
	for (int i = 0; i < sccSize; ++i) {
		for (int j = 0; j < SCC[i].size(); ++j) {
			int there = SCC[i][j];
			if (SAT[there] == -1) {
				SAT[there] = 0;
				if (there <= V) {
					SAT[there + V] = 1;
				} else {
					SAT[there - V] = 1;
				}
			}
		}
	}
	/*
	for (int i = 0; i <= 2 * V; ++i) {
		visited[i] = -1;
	}
	queue<int>Q;
	for (int i = 0; i < sccSize; ++i) {
		if (indegreeSCC[i] == 0) {
			Q.push(i);
			for (int j = 0; j < SCC[i].size(); ++j) {
				int there = SCC[i][j];
				if (SAT[there] == -1) {
					SAT[there] = 0;
					if (there <= V) {
						SAT[there + V] = 1;
					} else {
						SAT[there - V] = 1;
					}
				}
			}
		}
	}
	while (!Q.empty()) {
		int here = Q.front();
		Q.pop();
		visited[here] = 1;
		for (int i = 0; i < adjSCC[here].size(); ++i) {
			indegreeSCC[adjSCC[here][i]]--;
			if (indegreeSCC[adjSCC[here][i]] == 0 && visited[adjSCC[here][i]] == -1) {
				Q.push(adjSCC[here][i]);
				for (int j = 0; j < SCC[adjSCC[here][i]].size(); ++j) {
					int there = SCC[adjSCC[here][i]][j];
					if (SAT[there] == -1) {
						SAT[there] = 0;
						if (there <= V) {
							SAT[there + V] = 1;
						} else {
							SAT[there - V] = 1;
						}
					}
				}
			}
		}
	}
	*/
	cout << "\n";
	for (int i = 1; i <= V; ++i) {
		cout << SAT[i] << " ";
	}

}