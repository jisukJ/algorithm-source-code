#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef tuple<int,int,int> Edge;
const int INF = 987654321;

class HeavyLightDecomposition {
public:
	// �׷��� ������ �Է¹ް� ��� ��ó���� �ϴ� �Լ�
	void initialize();

	// e�� ������ ����ġ�� k�� �����ϴ� ����
	void update(int e, int k);

	// ���� u�� v ������ ��ο� ���� ���� �� �ִ� ����ġ ��
	int getMax(int u, int v);

private:

	int N, C, dcnt; // ������ ����, �׷��� ����, DFS ī���� ����
	// ���� ���� ��ȣ�� �����ϴ� �迭��
	int tSize[MAX], dfsn[MAX]; // ����Ʈ�� ũ��, DFS �湮 ����(�� ���� ��ȣ)
	vector<Edge> adj[MAX]; // ���� ���� �迭
	vector<int> child[MAX]; // �ڽ� ���� ���
	// �� ���� ��ȣ�� �����ϴ� �迭��
	int parent[MAX], depth[MAX], cn[MAX]; // �θ� ���� ��ȣ, ����, �׷� ��ȣ
	// ���� ��ȣ(1-based) -> �ڽ������� �� ���� ��ȣ(0-based)
	int eVertex[MAX];
	// �׷�(ü��) ��ȣ�� �����ϴ� �迭��
	// �׷쿡�� ���� ���� ���� ��ȣ, ���� ���� ��ȣ
	int cHead[MAX], cTail[MAX]; 
	// ���� �ִ� ���׸�Ʈ Ʈ��
	SegTree ST;
	// DFS �Լ� 1ȣ: ����Ʈ�� ũ�� ���ϱ�
	void dfs1(int curr, int prev = -1);

	// DFS �Լ� 2ȣ: ������ �׷��� �и�
	void dfs2(int curr, int prev = -1, int currDepth = 0);

};

void HeavyLightDecomposition::initialize() {
	// �׷��� ���� �Է¹ޱ�: �̶� ���� ��ȣ�� 0���� �ű��.
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		--u; --v;
		adj[u].push_back(Edge(v, w, i));
		adj[v].push_back(Edge(u, w, i));
	}

	// ù ��° DFS: �� ������ ����Ʈ�� ũ�� ���ϱ�
	dfs1(0);

	// �θ�, �׷� ���� ���� �ʱ�ȭ
	C = dcnt = 0;
	fill(cHead, cHead + MAX, -1);
	fill(cTail, cTail + MAX, -1);
	parent[0] = -1;

	// �� ��° DFS: �� ������ �׷캰�� �з�
	dfs2(0);

	// ���� ����� �ٽ� ���� �ʱ� ���׸�Ʈ Ʈ�� ����
	for (int curr = 0; curr < N; ++curr) {
		int u = dfsn[curr];
		for (auto &e : adj[curr]) {
			int next, d, en;
			tie(next, d, en) = e;
			int v = dfsn[next];
			// �� ������ �� �� ó���ϴ� �� ���� ����, �� ���� ������ ���ؼ��� ó��
			if (depth[u] < depth[v]) {
				eVertex[en] = v; // ���� ��ȣ(1���� ��)�� ���� ���� ���� ��ȣ�� �˷��ִ� �迭
				ST.A[MAX_ST / 2 + v] = d; // ���׸�Ʈ Ʈ���� ������ �ʱ�ȭ
			}
		}
	}
	ST.construct();
}

void HeavyLightDecomposition::dfs1(int curr, int prev) {
	tSize[curr] = 1;
	for (auto &p : adj[curr]) {
		int next, d, en;
		tie(next, d, en) = p;
		if (next != prev) { // ������ ������ �ƴ� ���� DFS �����
			dfs1(next, curr);
			// �ڽ� DFS ��, Ȯ���� �ڽ� ����Ʈ �� ����Ʈ�� ������ ����
			child[curr].push_back(next);
			tSize[curr] += tSize[next];
		}
	}
}

void HeavyLightDecomposition::dfs2(int curr, int prev, int currDepth) {
	// �� ���� ��ȣ�� DFS ī���� ������ ����
	int u = dfsn[curr] = dcnt++;
	// ���� �׷쿡 �̹� ������ ���Խ�Ŵ
	cn[u] = C;
	// ������ ���̴� �����ε� ��� �� ���̹Ƿ� �� ���� ��ȣ�� ���� �ű�
	depth[u] = currDepth;
	// �̹� �׷��� cHead(���� ��ȣ�� ���� ����, �� ���۹�ȣ), cTail(���� ��ȣ�� ū ����, �� ����ȣ) ����
	if (cHead[C] < 0) cHead[C] = u;
	cTail[C] = u;
	// ���� ����� ��� �̹� �׷��� �ŵ����� ���ư�
	if (child[curr].empty()) {
		++C;
		return;
	}

	// chained: ���ſ� ���� �� ���� ã��
	int chained = child[curr][0];
	for (int i = 1; i < child[curr].size(); ++i) {
		int next = child[curr][i];
		if (tSize[chained] < tSize[next]) chained = next;
	}
	// ���ſ� ���� ������ ���� ���� DFS: ���� �׷��� �̾����
	dfs2(chained, curr, currDepth + 1);
	// �θ� ���� ��ȣ ���� ��� ����� ���̹Ƿ� �� ���� ��ȣ�� ���� �ű�
	parent[dfsn[chained]] = u;
	// ������ �������� Ÿ�� �������� DFS�� ���� �� �׷��� ����
	for (int next : child[curr]) {
		if (next != chained) dfs2(next, curr, currDepth + 1);
		// �θ� ���� �ű�
		int v = dfsn[next];
		parent[v] = u;
	}
}

void HeavyLightDecomposition::update(int e, int k) {
	ST.update(eVertex[e], k);
}

int HeavyLightDecomposition::getMax(int u, int v) {
	int result = -INF;
	// ���� u, v�� �� ���� ��ȣ�� �ٲ�
	u = dfsn[u];
	v = dfsn[v];

	// ���� �ٸ� �׷쿡 ���� �ִ� ����, ���� �� �׷���� �����ذ��� �׷��� ����Ÿ�� �ö��
	if (cn[u] != cn[v]) {
		while (1) {
			int uHead = cHead[cn[u]], vHead = cHead[cn[v]];
			// u�� ���� �׷��� �� ����
			if (depth[uHead] > depth[vHead]) {
				// �׷� �� ���� ����
				result = max(ST.getMax(uHead, u + 1), result);
				// u�� �׷� �� ���� �ٷ� �� �������� �Űܰ�
				u = parent[uHead];
			}
			// v�� ���� �׷��� �� ����
			else {
				// �׷� �� ���� ����
				result = max(ST.getMax(vHead, v + 1), result);
				// v�� �׷� �� ���� �ٷ� �� �������� �Űܰ�
				v = parent[vHead];
			}
			// ���� ���� �׷쿡 ���ϸ� break
			if (cn[u] == cn[v]) break;
		}
	}
	// u�� v�� ���ÿ� ���� (������) �׷� �� ���� ����
	result = max(ST.getMax(min(u, v) + 1, max(u, v) + 1), result);
	// ��� ����
	return result;
}