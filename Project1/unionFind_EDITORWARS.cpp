#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int C, N, M;
struct unionFind {
	vector<int>parent,rank,enemy,size;
	unionFind(int n) : parent(n), enemy(n,-1), rank(n, 1),size(n,1)
	{
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	int find(int a)
	{
		if (parent[a] == a)
			return a;
		return parent[a]=find(parent[a]);
	}
	int merge(int a, int b)
	{

		if (a == -1 || b == -1)
			return max(a, b);
		if (a == b)
			return a;
		if (rank[a] < rank[b])
			swap(a, b);
		parent[b] = a;
		size[a] += size[b];
		if (rank[a] == rank[b])
			rank[a]++;
		return a;
	}
	bool ask(int a, int b)
	{
		a = find(a); b = find(b);
		if (enemy[a]==b||enemy[b]==a)
			return false;
		int tmp1=merge(a, b);
		int tmp2 = merge(enemy[a], enemy[b]);
		enemy[tmp1] = tmp2;
		if(tmp2!=-1)
		enemy[tmp2] = tmp1;
		return true;
	}
	bool dis(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b)
			return false;
			int tmp1=merge(enemy[a], b);
			int tmp2=merge(a, enemy[b]);
			enemy[tmp1] = tmp2;
			enemy[tmp2] = tmp1;
			return true;
	}

	int maxparty()
	{
		int ans = 0;
		vector<int>check(N, 0);
		for (int i = 0; i < N; ++i)
		{
			if (find(i) == i && check[i] == 0)
			{
				int a = size[i];
				int b = 0;
				if (enemy[i] != -1)
				{
					b = size[enemy[i]];
					check[enemy[i]] = 1;
				}
				ans += max(a,b);
				check[i] = 1;
			}
		}
		return ans;
	}
};



int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N >> M;
		string str;
		int a, b;
		unionFind tmp(N);
		int flag = 0;
		for (int i = 1; i <= M;++i)
		{
			cin >> str >> a >> b;
			if (str == "ACK")
			{
				if (tmp.ask(a, b) == false&& flag == 0)
						flag = i;
			}
			else
			{
				if (tmp.dis(a, b) == false&&flag==0)
					flag = i;
			}
		}
		if (flag == 0)
			cout << "MAX PARTY SIZE IS "<<tmp.maxparty()<<endl;
		else
			cout << "CONTRADICTION AT " << flag << endl;
	}
}