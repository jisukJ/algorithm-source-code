#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int dx[2] = { -1,1 };
const int dy[2] = { 1,1 };
vector<string> board;
int id[2][8][8];
int n, m;
int adj[64][64];
int T, N;

vector<int> aMatch, bMatch;
vector<bool>visited;
int ec;
bool dfs(int a)
{
	if (visited[a])
		return false;
	visited[a] = true;
	for (int b = 0; b < m; ++b)
		if (adj[a][b])
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				aMatch[a] = b;
				bMatch[b] = a;
				
				return true;
			}
	return false;
}
int bipartiteMatch()
{
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; ++start)
	{
		visited = vector<bool>(n, false);
		
		if (dfs(start))
			++size;
	}
	return size;
}


int placeBishops() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 8; ++j)
			for (int k = 0; k < 8; ++k)
				id[i][j][k] = -1;
	int count[2] = { 0,0 };
	for (int dir = 0; dir < 2; ++dir)
		for (int y = 0; y < board.size(); ++y)
			for (int x = 0;x< board.size(); ++x)
				if (board[y][x] == '.'&&id[dir][y][x] == -1)
				{
					int cy = y, cx = x;
					while (0 <= cy && cy < board.size() && 0 <= cx && cx < board.size() && board[cy][cx] == '.')
					{
						id[dir][cy][cx] = count[dir];
						cy += dy[dir];
						cx += dx[dir];
					}
					count[dir]++;
				}
	n = count[0];
	m = count[1];
	for (int i = 0; i < 64; ++i)
		for (int j = 0; j < 64; ++j)
			adj[i][j] = 0;
	for (int y = 0; y < board.size(); ++y)
		for (int x = 0; x < board.size(); ++x)
			if (board[y][x] == '.')
				adj[id[0][y][x]][id[1][y][x]] = 1;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << id[0][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << id[1][i][j] << " ";
		}
		cout << endl;
	}
	return bipartiteMatch();
}

int main()
{
	cin >> T;
	for (int test = 0; test < T; ++test)
	{
		cin >> N;
		string tmp;
		board.clear();
		for (int i = 0; i < N; ++i)
		{
			cin >> tmp;
			board.push_back(tmp);
		}
		cout << placeBishops() << endl;
	}
}