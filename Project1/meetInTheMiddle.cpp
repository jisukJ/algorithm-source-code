#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	int x, y;
	vector<int>cell;
	Node() : Node(0) {}
	Node(int _size) {
		x = y = -1;
		cell.resize(_size*_size);
	}
};

int D, N;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
string str;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	while ((cin >> str >> D >> N)) {
		Node S[2];
		for (int k = 0; k < 2; ++k) {
			S[k] = Node(D);
			for (int i = 0; i < D; ++i) {
				for (int j = 0; j < D; ++j) {
					string tmp;
					cin >> tmp;
					if (tmp[0] == 'X') {
						S[k].x = j;
						S[k].y = i;
					} else {
						S[k].cell[i*D + j] = tmp[0] - '0';
					}
				}
			}
		}
		map<vector<int>, int>M[2];
		for (int k = 0; k < 2; ++k) {
			queue<Node>Q;
			M[k][S[k].cell] = 0;
			Q.push(S[k]);
			for (int i = 0; i < N / 2 + (N % 2 && k); ++i) {
				int qSize = Q.size();
				for (int j = 0; j < qSize; ++j) {
					Node currNode = Q.front();
					Q.pop();
					int cx = currNode.x, cy = currNode.y, cp = cy * D + cx;
					for (int d = 0; d < 4; ++d) {
						int nx = cx + dx[d], ny = cy + dy[d], np = ny * D + nx;
						if (nx < 0 || nx >= D || ny < 0 || ny >= D) {
							continue;
						}
						swap(currNode.cell[cp], currNode.cell[np]);
						if (M[k].find(currNode.cell) == M[k].end()) {
							currNode.x = nx;
							currNode.y = ny;
							M[k][currNode.cell] = i + 1;
							Q.push(currNode);
						}
						swap(currNode.cell[cp], currNode.cell[np]);
					}
				}
			}
		}

		int res = N + 1;
		for (auto iter1 : M[0]) {
			auto iter2 = M[1].find(iter1.first);
			if (iter2 != M[1].end()) {
				res = min(res, iter1.second + iter2->second);
			}
		}
		cin >> str;
		if (res <= N) {
			cout << "SOLVABLE WITHIN " << res << " MOVES\n\n";
		} else {
			cout << "NOT SOLVABLE WITHIN " << N << " MOVES\n\n";
		}

	}
}