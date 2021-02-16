#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;
long long int dis(int x1, int y1, int x2, int y2)
{
	long long int ret = ((long long int)x1 - (long long int)x2)*((long long int)x1 - (long long int)x2) + ((long long int)y1 - (long long int)y2)*((long long int)y1 - (long long int)y2);
	return ret;
}

struct pointSet {
	int x;
	int y;
};
vector<pointSet> MAP[1001][1001];
int MAP_cnt[1001][1001];

struct SegmentTree {
	int* arr;
	SegmentTree()
	{
		arr = new int[1001 * 1001 * 4];
		init(0, 0, 1000, 1000, 0);
	}
	int init(int lX, int lY, int uX, int uY, int node)
	{
		if (uX < lX || uY < lY)
			return 0;
		if (uX == lX && uY == lY)
			return arr[node] = MAP_cnt[lY][lX];
		else
		{
			int mX = (lX + uX) / 2;
			int mY = (lY + uY) / 2;
			return arr[node] = init(lX, lY, mX, mY, node * 4 + 1) + init(mX + 1, lY, uX, mY, node * 4 + 2)
				+ init(lX, mY + 1, mX, uY, node * 4 + 3) + init(mX + 1, mY + 1, uX, uY, node * 4 + 4);
		}
	}
	int query(int x, int y, int r, int lX, int lY, int uX, int uY, int node)
	{
		if (uX < lX || uY < lY||arr[node]==0)
			return 0;
		int x0 = lX * 1000, y0 = lY * 1000, x1 = uX * 1000 + 999, y1 = lY * 1000,
			x2 = lX * 1000, y2 = uY * 1000 + 999, x3 = uX * 1000 + 999, y3 = uY * 1000 + 999;
		long long int d0, d1, d2, d3, d4;
		d0 = dis(x, y, x0, y0); d1 = dis(x, y, x1, y1); d2 = dis(x, y, x2, y2); d3 = dis(x, y, x3, y3);
		d4 = (long long int)r*(long long int)r;
		if (((x < x0 || x1 < x) && (y < y0 || y2 < y)) && d4 < d0 && d4 < d1 && d4 < d2 && d4 < d3)
			return 0;
		else if (x + r < x0 && y0 <= y && y <= y2 && d4 < d0 && d4 < d1 && d4 < d2 && d4 < d3)
			return 0;
		else if (x1 < x - r && y0 <= y && y <= y2 && d4 < d0 && d4 < d1 && d4 < d2 && d4 < d3)
			return 0;
		else if (x0 <= x && x <= x1 && y2 < y - r && d4 < d0 && d4 < d1 && d4 < d2 && d4 < d3)
			return 0;
		else if (x0 <= x && x <= x1 && y + r < y0 && d4 < d0 && d4 < d1 && d4 < d2 && d4 < d3)
			return 0;
		else if (d0 <= d4 && d1 <= d4 && d2 <= d4 && d3 <= d4)
		{
			return arr[node];
		}
		else if (uX == lX && uY == lY)
		{
			int ret = 0;

			for (int i = 0; i < MAP[lY][lX].size(); ++i)
			{
				if (dis(MAP[lY][lX][i].x, MAP[lY][lX][i].y, x, y) <= d4)
					++ret;
			}
			return ret;
		}
		else
		{
			int mX = (lX + uX) / 2;
			int mY = (lY + uY) / 2;
			int ret = 0;
			ret += query(x, y, r, lX, lY, mX, mY, node * 4 + 1);
			ret += query(x, y, r, mX + 1, lY, uX, mY, node * 4 + 2);
			ret += query(x, y, r, lX, mY + 1, mX, uY, node * 4 + 3);
			ret += query(x, y, r, mX + 1, mY + 1, uX, uY, node * 4 + 4);
				return ret;
		}

	}
	int query(int x, int y, int r)
	{
		return query(x, y, r, 0, 0, 1000, 1000, 0);
	}
};

int N, M, x, y, r;

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d %d", &x, &y);
		pointSet tmp;
		tmp.x = x;
		tmp.y = y;
		MAP[y / 1000][x / 1000].push_back(tmp);
		MAP_cnt[y / 1000][x / 1000]++;
	}
	SegmentTree segT = SegmentTree();
	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
	{
		scanf("%d %d %d", &x, &y, &r);
		printf("%d\n", segT.query(x, y, r));
	}
}