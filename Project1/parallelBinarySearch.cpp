#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, Q;
int query[100000][2];
int lo[100000];
int hi[100000];
int result[100000][2];
vector<pair<int, pair<int, int>>>edge;

struct UnionFind {
	vector<int>parent;
	vector<int>size;
	vector<int>rank;
	UnionFind(int n) {
		parent.resize(n);
		size.resize(n);
		rank.resize(n);
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
			size[i] = 1;
			rank[i] = 1;
		}
	}
	int find(int a) {
		if (parent[a] == a) {
			return a;
		} else {
			return parent[a] = find(parent[a]);
		}
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) {
			return;
		}
		if (rank[a] < rank[b]) {
			swap(a, b);
		}
		parent[b] = a;
		size[a] += size[b];
		if (rank[a] == rank[b]) {
			rank[a]++;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		edge.push_back({ c,{a,b} });
	}
	sort(edge.begin(), edge.end());
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		cin >> query[i][0] >> query[i][1];
		--query[i][0];
		--query[i][1];

		lo[i] = 0;
		hi[i] = M + 1;
	}

	while (true) {
		bool flag = false;
		vector<vector<int>>G(M + 1);
		for (int i = 0; i < Q; ++i) {
			if (lo[i] + 1 < hi[i]) {
				flag = true;
				G[(lo[i] + hi[i]) / 2].push_back(i);
			}
		}
		if (!flag) {
			break;
		}
		UnionFind unionfind(N);
		for (int i = 0; i < M; ++i) {
			int u, v, w;
			w = edge[i].first;
			u = edge[i].second.first;
			v = edge[i].second.second;
			unionfind.merge(u, v);
			for (int j : G[i + 1]) {
				int a = unionfind.find(query[j][0]), b = unionfind.find(query[j][1]);
				if (a == b) {
					hi[j] = i + 1;
					result[j][0] = w;
					result[j][1] = unionfind.size[unionfind.find(a)];
				} else {
					lo[j] = i + 1;
				}
			}
		}
	}

	for (int i = 0; i < Q; ++i) {
		if (lo[i] == M) {
			cout << "-1\n";
		} else {
			cout << result[i][0] << " " << result[i][1] << "\n";
		}
	}
}