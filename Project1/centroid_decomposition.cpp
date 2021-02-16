#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N, K;

int sz[200000];
int depth[200000];
long long lenth[200000];
bool deleted[200000];
vector<pair<int, long long>> adj[200000];
map<int, int>mp;
const int INF = 1987654321;
int ans = INF;

int getTree(int here, int parent) {
	sz[here] = 1;
	if (here == parent) {
		depth[here] = 0;
		lenth[here] = 0;
	} else {
		depth[here] = depth[parent] + 1;
	}
	for (auto there : adj[here]) {
		if (there.first == parent || deleted[there.first]) {
			continue;
		} else {
			lenth[there.first] = lenth[here] + there.second;
			sz[here] += getTree(there.first, here);
		}
	}
	return sz[here];
}

int getCentroid(int here, int parent, int cap) {
	for (auto there : adj[here]) {
		if (there.first == parent || deleted[there.first]) {
			continue;
		} else {
			if (sz[there.first] > cap) {
				return getCentroid(there.first, here, cap);
			}
		}
	}
	return here;
}

void compute(int here, int parent) {
	if (lenth[here] > K) {
		return;
	}
	if (mp.find(K - lenth[here]) != mp.end()) {
		ans = min(mp.find(K - lenth[here])->second + depth[here], ans);
	}
	for (auto there : adj[here]) {
		if (there.first == parent || deleted[there.first]) {
			continue;
		} else {
			compute(there.first, here);
		}
	}
}

void merge(int here, int parent) {
	if (lenth[here] > K) {
		return;
	}
	if (mp.find(lenth[here]) == mp.end()) {
		mp[lenth[here]] = depth[here];
	} else {
		mp[lenth[here]] = min(mp[lenth[here]], depth[here]);
	}
	for (auto there : adj[here]) {
		if (there.first == parent || deleted[there.first]) {
			continue;
		} else {
			merge(there.first, here);
		}
	}
}

void solve(int start) {
	int treeSize = getTree(start, start);
	int centroid = getCentroid(start, start, treeSize / 2);
	deleted[centroid] = true;
	getTree(centroid, centroid);
	mp.clear();
	mp[0] = 0;
	for (auto there : adj[centroid]) {
		if (!deleted[there.first]) {
			compute(there.first, centroid);
			merge(there.first, centroid);
		}
	}
	for (auto there : adj[centroid]) {
		if (!deleted[there.first]) {
			if (!deleted[there.first]) {
				solve(there.first);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		long long c;
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	solve(0);
	if (ans != INF) {
		cout << ans;
	} else {
		cout << "-1";
	}
}