#include <iostream>
#include <vector>

using namespace std;
int n, m;
const int MAX_N = 1000, MAX_M = 1000;
int adj[MAX_N][MAX_M];
vector<int> aMatch, bMatch;
vector<int>visited;

bool dfs(int a) {
	visited[a] = 1;
	for (int b = 0; b < m; ++b) {
		if (adj[a][b]==1) {
			if (bMatch[b] == -1 || (visited[bMatch[b]]==-1&&dfs(bMatch[b]))) {
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}
	return false;
}

int bipartiteMatch() {
	int matched = 0;
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);
	for (int i = 0; i < n; ++i) {
		visited = vector<int>(n, -1);
		if (dfs(i)) {
			matched++;
		}
	}
	return matched;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 1; test <= T; ++test) {
		cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				adj[i][j] = 0;
			}
		}
		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			--a, --b;
			for (int j = a; j <= b; ++j) {
				adj[j][i] = 1;
			}
		}

		cout << bipartiteMatch()<<"\n";
	}
}