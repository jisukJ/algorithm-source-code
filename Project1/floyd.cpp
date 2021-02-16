#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int V;
const int MAX_V = 500;
int adj[MAX_V][MAX_V];
int via[MAX_V][MAX_V];
void floyd()
{
	for (int i = 0; i < V; ++i)
		adj[i][i] = 0;
	memset(via, -1, sizeof(via));
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
			{
				if (adj[i][j] > adj[i][k] + adj[k][j])
				{
					via[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}
			}
}

void reconstruct(int u, int v, vector<int>&path)
{
	if (via[u][v] == -1)
	{
		path.push_back(u);
		if (u != v)
			path.push_back(v);
	}
	else
	{
		int w = via[u][v];
		reconstruct(u, w, path);
		path.pop_back();
		reconstruct(w, v, path);
	}
	return;
}
int main()
{

}