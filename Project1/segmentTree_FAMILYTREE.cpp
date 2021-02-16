#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
const int MAX = numeric_limits<int>::max();

struct RMQ{
	int n;
	vector<int> rangeMin;
	RMQ(const vector<int> &array)
	{
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	int init(const vector<int> &array, int left, int right, int node)
	{
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (right < nodeLeft || nodeRight < left)
			return MAX;
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}
	//array[index]=newValue로 바뀌었을 떄 node를 루트로 하는
	//구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight)
	{
		//index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight)
			return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue)
	{
		return update(index, newValue, 1, 0, n - 1);
	}
};
int N;
vector<int> child[MAXN];
//트리의 번호와 일렬 번호 사이의 대응 관계
int no2serial[MAXN], serial2no[MAXN];
//각 노드가 trip에 처음 등장하는 위치, 그리고 각 노드의 깊이
int locInTrip[MAXN], depth[MAXN];
//다음 일렬번호
int nextSerial;
//깊이가 d인 노드 here 이하를 전위 탐색(preorder Traversal)
void traverse(int here, int d, vector<int> &trip)
{
	//traverse()가 처음 방문하자마자 일렬 번호를 부여
	//이렇게 하면 항상 부모는 자손보다 작은 일렬 번호를 갖게 된다
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;
	//깊이 계산
	depth[here] = d;
	//trip에 현재 노드의 일렬 번호를 추가
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	//모든 자식 노들르 방문
	for (int i = 0; i < child[here].size(); i++)
	{
		traverse(child[here][i], d + 1, trip);
		//자식 노드를 방문하고 현재 노드로 들어올 때마다 다시 추가
		trip.push_back(no2serial[here]);
	}
}
//트리를 순회하며 각종 필요한 정보를 계산하고
//RMQ 구간 트리를 만들어 반환
RMQ *prepareRMQ(void)
{
	nextSerial = 0;
	//순회 과정에서 만나는 노드들의 일렬 번호를 담는다
	vector<int> trip;
	traverse(0, 0, trip);
	for (int i = 0; i < trip.size(); ++i)
		cout<<trip[i]<<" ";
	return new RMQ(trip);
}
//u와 v 사이의 거리를 계산한다
int distance(RMQ *rmq, int u, int v)
{
	//trip[] 배열에서 u와 v의 첫 출현 위치를 찾는다
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv)
		swap(lu, lv);
	//rmq는 u와 v의 최소 공통 조상의 일렬번호를 반환
	int lca = serial2no[rmq->query(lu, lv)]; //least common ancestor
	return depth[u] + depth[v] - 2 * depth[lca];
}
int main(void)
{
	int test_case;
	cin >> test_case;
	for (int i = 0; i < test_case; i++)
	{
		for (int j = 0; j < MAXN; j++)
			child[j].clear();
		int N, Q; //족보에 포함된 사람의 수, 촌수를 계산할 두 사람의 수
		cin >> N >> Q;
		for (int j = 1; j < N; j++)
		{
			int parent;
			cin >> parent;
			child[parent].push_back(j);
		}
		nextSerial = 0;
		RMQ *pRmq = prepareRMQ();
		/*for (int j = 0; j < Q; j++)
		{
			int a, b;
			cin >> a >> b;
			cout << distance(pRmq, a, b) << endl;
		}*/
	}
	return 0;
}