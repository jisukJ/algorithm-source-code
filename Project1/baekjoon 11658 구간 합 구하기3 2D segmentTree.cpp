#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int N, M;
int W, X, Y, C;
int X1, X2, Y1, Y2;
int MAP[1024][1024];
int querycnt;
struct segmentTree {
	int* arr;
	segmentTree()
	{
		arr = new int[N*N * 4];
		init(0, 0, N-1, N-1, 0);
	}
	int init(int lX, int lY, int uX, int uY, int node)
	{
		if (uX < lX || uY < lY)
			return 0;
		else if (uX == lX && uY == lY)
			return arr[node] = MAP[lY][lX];
		else
		{
			int mX = (lX + uX) / 2;
			int mY = (lY + uY) / 2;
			return arr[node] = init(lX, lY, mX, mY, node * 4 + 1) + init(mX + 1, lY, uX, mY, node * 4 + 2)
				+ init(lX, mY + 1, mX, uY, node * 4 + 3) + init(mX + 1, mY + 1, uX, uY, node * 4 + 4);
		}
	}
	int query(int x1, int y1, int x2, int y2, int lX, int lY, int uX, int uY, int node)
	{
		querycnt++;
		if (uX < lX || uY < lY||arr[node]==0)
			return 0;
		if (x1 <= lX && uX <= x2 && y1 <= lY && uY <= y2)
			return arr[node];
		if (x2 < lX || uX < x1 || y2 < lY || uY < y1)
			return 0;
		int mX = (lX + uX) / 2;
		int mY = (lY + uY) / 2;
		int ret = 0;
		ret += query(x1, y1, x2,y2, lX, lY, mX, mY, node * 4 + 1);
		ret += query(x1, y1, x2, y2, mX + 1, lY, uX, mY, node * 4 + 2);
		ret += query(x1, y1, x2, y2, lX, mY + 1, mX, uY, node * 4 + 3);
		ret += query(x1, y1, x2, y2, mX + 1, mY + 1, uX, uY, node * 4 + 4);
		return ret;
	}
	int query(int x1, int y1, int x2, int y2)
	{
		return query(x1, y1, x2, y2, 0, 0, N - 1, N - 1, 0);
	}
	int update(int x1, int y1, int val, int lX, int lY, int uX, int uY, int node)
	{
		querycnt++;
		if (uX < lX || uY < lY)
			return 0;
		else if (uX == lX && uY == lY)
			return arr[node] = MAP[lY][lX];
		if (x1 < lX || uX < x1 || y1 < lY || uY < y1)
			return arr[node];
		int mX = (lX + uX) / 2;
		int mY = (lY + uY) / 2;
		int ret = 0;
		ret += update(x1, y1, val, lX, lY, mX, mY, node * 4 + 1);
		ret += update(x1, y1, val, mX + 1, lY, uX, mY, node * 4 + 2);
		ret += update(x1, y1, val, lX, mY + 1, mX, uY, node * 4 + 3);
		ret += update(x1, y1, val, mX + 1, mY + 1, uX, uY, node * 4 + 4);
		return arr[node] = ret;
	}
	int update(int x1, int y1, int val)
	{
		return update(x1, y1, val, 0, 0, N - 1, N - 1, 0);
	}
};
int main()
{
	//scanf("%d %d", &N, &M);
	clock_t st, et;
	
	N = 1024; M = 100000;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			MAP[i][j] = rand() % 1001;
			//scanf("%d", &MAP[i][j]);
	segmentTree tmpT = segmentTree();
	st = clock();
	for (int i = 0; i < M; ++i)
	{
		//scanf("%d", &W);
		W = rand() % 2;
		if (W == 0)
		{
			//scanf("%d %d %d", &X, &Y, &C);
			X = rand() % 1024;
			Y = rand() % 1024;
			C = rand() % 1001;
			//X--; Y--;
			MAP[Y][X] = C;
			tmpT.update(X, Y, C);
		}
		else if (W == 1)
		{
			//scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
			X1 = rand() % 1024;
			Y1 = rand() % 1024;
			X2 = rand() % 1024;
			Y2 = rand() % 1024;
			tmpT.query(X1, Y1, X2, Y2);
			//X1--; Y1--; X2--; Y2--;
			//printf("%d\n",tmpT.query(X1, Y1, X2,Y2));
		}
	}
	et = clock();
	printf("걸린 시간: %d msec\n", et - st);
	printf("쿼리 호출: %d 번\n", querycnt);
}