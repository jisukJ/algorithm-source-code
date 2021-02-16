#include <iostream>

using namespace std;

int arr[11][11];
int cnt;
void cover(int lX, int lY, int uX, int uY)
{
	if (uX == lX && uY == lY)
	{
		cnt++;
		arr[lY][lX] = 5;
		return;
	}
	if (uX < lX || uY < lY)
	{
		cout << lX << " " << lY << " " << uX << " " << uY << endl;
		return;
	}
	else
	{
		int mX = (lX + uX) / 2;
		int mY = (lY + uY) / 2;
		cover(lX, lY, mX, mY);
		if(mX+1<=uX)
		cover(mX + 1, lY, uX, mY);//mX+1
		if(mY+1<=uY)
		cover(lX, mY + 1, mX, uY);//mY+1
		if(mX + 1 <= uX&& mY + 1 <= uY)
		cover(mX + 1, mY + 1, uX, uY);//mX+1 mY+1
		return;
	}
}

int main()
{
	cnt = 0;
	cover(0, 0, 10, 10);
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << cnt;
}