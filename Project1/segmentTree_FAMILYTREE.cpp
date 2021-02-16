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
	//array[index]=newValue�� �ٲ���� �� node�� ��Ʈ�� �ϴ�
	//���� Ʈ���� �����ϰ� ��尡 ǥ���ϴ� ������ �ּ�ġ�� ��ȯ�Ѵ�
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight)
	{
		//index�� ��尡 ǥ���ϴ� ������ ������� ��쿣 �����Ѵ�
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		//Ʈ���� �������� ������ ���
		if (nodeLeft == nodeRight)
			return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int update(int index, int newValue)
	{
		return update(index, newValue, 1, 0, n - 1);
	}
};
int N;
vector<int> child[MAXN];
//Ʈ���� ��ȣ�� �Ϸ� ��ȣ ������ ���� ����
int no2serial[MAXN], serial2no[MAXN];
//�� ��尡 trip�� ó�� �����ϴ� ��ġ, �׸��� �� ����� ����
int locInTrip[MAXN], depth[MAXN];
//���� �ϷĹ�ȣ
int nextSerial;
//���̰� d�� ��� here ���ϸ� ���� Ž��(preorder Traversal)
void traverse(int here, int d, vector<int> &trip)
{
	//traverse()�� ó�� �湮���ڸ��� �Ϸ� ��ȣ�� �ο�
	//�̷��� �ϸ� �׻� �θ�� �ڼպ��� ���� �Ϸ� ��ȣ�� ���� �ȴ�
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;
	//���� ���
	depth[here] = d;
	//trip�� ���� ����� �Ϸ� ��ȣ�� �߰�
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	//��� �ڽ� ��鸣 �湮
	for (int i = 0; i < child[here].size(); i++)
	{
		traverse(child[here][i], d + 1, trip);
		//�ڽ� ��带 �湮�ϰ� ���� ���� ���� ������ �ٽ� �߰�
		trip.push_back(no2serial[here]);
	}
}
//Ʈ���� ��ȸ�ϸ� ���� �ʿ��� ������ ����ϰ�
//RMQ ���� Ʈ���� ����� ��ȯ
RMQ *prepareRMQ(void)
{
	nextSerial = 0;
	//��ȸ �������� ������ ������ �Ϸ� ��ȣ�� ��´�
	vector<int> trip;
	traverse(0, 0, trip);
	for (int i = 0; i < trip.size(); ++i)
		cout<<trip[i]<<" ";
	return new RMQ(trip);
}
//u�� v ������ �Ÿ��� ����Ѵ�
int distance(RMQ *rmq, int u, int v)
{
	//trip[] �迭���� u�� v�� ù ���� ��ġ�� ã�´�
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv)
		swap(lu, lv);
	//rmq�� u�� v�� �ּ� ���� ������ �ϷĹ�ȣ�� ��ȯ
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
		int N, Q; //������ ���Ե� ����� ��, �̼��� ����� �� ����� ��
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