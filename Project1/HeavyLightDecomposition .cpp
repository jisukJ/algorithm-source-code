#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef tuple<int,int,int> Edge;
const int INF = 987654321;

class HeavyLightDecomposition {
public:
	// 그래프 정보를 입력받고 모든 전처리를 하는 함수
	void initialize();

	// e번 간선의 가중치를 k로 갱신하는 연산
	void update(int e, int k);

	// 정점 u와 v 사이의 경로에 속한 간선 중 최대 가중치 값
	int getMax(int u, int v);

private:

	int N, C, dcnt; // 정점의 개수, 그룹의 개수, DFS 카운터 변수
	// 원래 정점 번호로 참조하는 배열들
	int tSize[MAX], dfsn[MAX]; // 서브트리 크기, DFS 방문 순서(새 정점 번호)
	vector<Edge> adj[MAX]; // 인접 간선 배열
	vector<int> child[MAX]; // 자식 정점 목록
	// 새 정점 번호로 참조하는 배열들
	int parent[MAX], depth[MAX], cn[MAX]; // 부모 정점 번호, 깊이, 그룹 번호
	// 간선 번호(1-based) -> 자식정점의 새 정점 번호(0-based)
	int eVertex[MAX];
	// 그룹(체인) 번호로 참조하는 배열들
	// 그룹에서 제일 얕은 정점 번호, 깊은 정점 번호
	int cHead[MAX], cTail[MAX]; 
	// 구간 최댓값 세그먼트 트리
	SegTree ST;
	// DFS 함수 1호: 서브트리 크기 구하기
	void dfs1(int curr, int prev = -1);

	// DFS 함수 2호: 간선을 그룹들로 분리
	void dfs2(int curr, int prev = -1, int currDepth = 0);

};

void HeavyLightDecomposition::initialize() {
	// 그래프 내용 입력받기: 이때 정점 번호는 0부터 매긴다.
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		--u; --v;
		adj[u].push_back(Edge(v, w, i));
		adj[v].push_back(Edge(u, w, i));
	}

	// 첫 번째 DFS: 각 정점의 서브트리 크기 구하기
	dfs1(0);

	// 부모, 그룹 관련 변수 초기화
	C = dcnt = 0;
	fill(cHead, cHead + MAX, -1);
	fill(cTail, cTail + MAX, -1);
	parent[0] = -1;

	// 두 번째 DFS: 각 간선을 그룹별로 분류
	dfs2(0);

	// 간선 목록을 다시 보며 초기 세그먼트 트리 구축
	for (int curr = 0; curr < N; ++curr) {
		int u = dfsn[curr];
		for (auto &e : adj[curr]) {
			int next, d, en;
			tie(next, d, en) = e;
			int v = dfsn[next];
			// 한 간선을 두 번 처리하는 걸 막기 위해, 더 깊은 정점에 대해서만 처리
			if (depth[u] < depth[v]) {
				eVertex[en] = v; // 간선 번호(1부터 셈)를 보고 깊은 정점 번호를 알려주는 배열
				ST.A[MAX_ST / 2 + v] = d; // 세그먼트 트리의 리프값 초기화
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
		if (next != prev) { // 지나온 정점이 아닐 때만 DFS 계속함
			dfs1(next, curr);
			// 자식 DFS 후, 확실한 자식 리스트 및 서브트리 사이즈 갱신
			child[curr].push_back(next);
			tSize[curr] += tSize[next];
		}
	}
}

void HeavyLightDecomposition::dfs2(int curr, int prev, int currDepth) {
	// 새 정점 번호를 DFS 카운터 변수로 붙임
	int u = dfsn[curr] = dcnt++;
	// 현재 그룹에 이번 정점을 포함시킴
	cn[u] = C;
	// 정점의 깊이는 앞으로도 계속 쓸 것이므로 새 정점 번호에 대해 매김
	depth[u] = currDepth;
	// 이번 그룹의 cHead(제일 번호가 작은 정점, 즉 시작번호), cTail(제일 번호가 큰 정점, 즉 끝번호) 갱신
	if (cHead[C] < 0) cHead[C] = u;
	cTail[C] = u;
	// 리프 노드일 경우 이번 그룹을 매듭짓고 돌아감
	if (child[curr].empty()) {
		++C;
		return;
	}

	// chained: 무거운 간선 한 개를 찾음
	int chained = child[curr][0];
	for (int i = 1; i < child[curr].size(); ++i) {
		int next = child[curr][i];
		if (tSize[chained] < tSize[next]) chained = next;
	}
	// 무거운 간선 쪽으로 제일 먼저 DFS: 현재 그룹을 이어붙임
	dfs2(chained, curr, currDepth + 1);
	// 부모 정점 번호 역시 계속 사용할 것이므로 새 정점 번호에 대해 매김
	parent[dfsn[chained]] = u;
	// 나머지 간선들을 타고 내려가며 DFS를 통해 새 그룹을 만듦
	for (int next : child[curr]) {
		if (next != chained) dfs2(next, curr, currDepth + 1);
		// 부모 정점 매김
		int v = dfsn[next];
		parent[v] = u;
	}
}

void HeavyLightDecomposition::update(int e, int k) {
	ST.update(eVertex[e], k);
}

int HeavyLightDecomposition::getMax(int u, int v) {
	int result = -INF;
	// 먼저 u, v를 새 정점 번호로 바꿈
	u = dfsn[u];
	v = dfsn[v];

	// 서로 다른 그룹에 속해 있는 동안, 깊은 쪽 그룹부터 참조해가며 그룹을 갈아타며 올라옴
	if (cn[u] != cn[v]) {
		while (1) {
			int uHead = cHead[cn[u]], vHead = cHead[cn[v]];
			// u가 속한 그룹이 더 깊음
			if (depth[uHead] > depth[vHead]) {
				// 그룹 내 구간 연산
				result = max(ST.getMax(uHead, u + 1), result);
				// u를 그룹 맨 위의 바로 위 정점으로 옮겨감
				u = parent[uHead];
			}
			// v가 속한 그룹이 더 깊음
			else {
				// 그룹 내 구간 연산
				result = max(ST.getMax(vHead, v + 1), result);
				// v를 그룹 맨 위의 바로 위 정점으로 옮겨감
				v = parent[vHead];
			}
			// 둘이 같은 그룹에 속하면 break
			if (cn[u] == cn[v]) break;
		}
	}
	// u와 v가 동시에 속한 (마지막) 그룹 내 구간 연산
	result = max(ST.getMax(min(u, v) + 1, max(u, v) + 1), result);
	// 결과 리턴
	return result;
}