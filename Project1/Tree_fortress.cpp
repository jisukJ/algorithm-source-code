#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int C, N;

struct TreeNode {
	int x, y, r;
	int num;
	TreeNode* parent;
	vector<TreeNode*> children;
};
vector<TreeNode> fortress(100);
vector<TreeNode> fortress2(100);

int isin(TreeNode a, TreeNode b)
{
	int d = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
	if ((a.r + b.r)*(a.r + b.r) <= d)
		return 0;
	else
	{
		if (a.r < b.r)
			return 2;
		else
			return 1;
	}
}

void merge(int a, int b)
{
	if (isin(fortress[a], fortress[b]) == 0)
		return;
	else
	{
		if (isin(fortress[a], fortress[b]) == 1)
		{
			for (int i = 0; i < fortress[a].children.size(); ++i)
			{
				if (isin((*(fortress[a].children[i])), fortress[b]) == 1)
				{
					return merge((*(fortress[a].children[i])).num, b);
				}
				if (isin((*(fortress[a].children[i])), fortress[b]) == 2)
				{
					int tmp = (*(fortress[a].children[i])).num;
					fortress[a].children[i] = &fortress[b];
					fortress[b].parent = &fortress[a];
					fortress[b].children.push_back(&fortress[tmp]);
					fortress[tmp].parent = &fortress[b];
					return;
				}
			}
			fortress[a].children.push_back(&fortress[b]);
			fortress[b].parent = &fortress[a];
			return;
		}
	}
}

int search(TreeNode a, int depth)
{
	if (a.children.size() == 0)
		return depth;
	else
	{
		int tmp1 = 0, tmp1where = -1;
		int tmp2 = 0, tmp2where = -1;
		vector<int> result(a.children.size());
		for (int i = 0; i < a.children.size(); ++i)
		{
			result[i] = search(*(a.children[i]), depth + 1);
		}
		if (a.children.size() == 1 || depth != 0)
			return *max_element(result.begin(), result.end());
		else
		{
			for (int i = 0; i < result.size(); ++i)
			{
				if (tmp1 <= result[i])
				{
					tmp2 = tmp1;
					tmp2where = tmp1where;
					tmp1 = result[i];
					tmp1where = i;
				}
				if (tmp2 < result[i] && tmp1where != i)
				{
					tmp2 = result[i];
					tmp2where = i;
				}
			}

			return tmp1 + tmp2;
		}
	}
}

int main()
{
	cin >> C;
	for (int test = 0; test < C; ++test)
	{
		cin >> N;
		for (int i = 0; i < N; ++i)
		{
			cin >> fortress[i].x >> fortress[i].y >> fortress[i].r;
			fortress[i].num = i;
			fortress[i].parent = NULL;
			fortress[i].children.clear();
		}
		for (int i = 1; i < N; ++i)
			merge(0, i);
		int ans = 0;
		for (int i = 0; i < N; ++i)
		{
			if (fortress[i].children.size() != 0)
			{
				ans = max(ans, search(fortress[i], 0));
			}
		}
		cout << ans << endl;
	}
}