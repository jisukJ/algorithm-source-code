#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
using namespace std;


struct TrieNode {
	int terminal;
	TrieNode* children[26];
	TrieNode* fail;
	vector<int> output;
	TrieNode() : terminal(-1) {
		for (int i = 0; i < 26; ++i)
			children[i] = nullptr;
		fail = nullptr;
	}
	~TrieNode()
	{
		for (int i = 0; i < 26; ++i)
			if (children[i])
				delete children[i];
		output.clear();
	}
	void insert(int id,const char* key)
	{
		if (*key == 0)
		{
			terminal = id;
			return;
		}
		else
		{
			int next = *key - 'a';
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			children[next]->insert(id,key + 1);
		}
	}
	TrieNode* find(const char* key)
	{
		if (*key == 0&&terminal!=-1)
			return this;
		else
		{
			int next = *key - 'a';
			if (children[next] == nullptr)
				return nullptr;
			return children[next]->find(key + 1);
		}
	}
};

void computeFailFunc(TrieNode* root)
{
	queue<TrieNode*>q;
	q.push(root);
	root->fail = root;
	while (!q.empty())
	{
		TrieNode* here = q.front();
		q.pop();
		for (int i = 0; i < 26; ++i)
		{
			TrieNode* child = here->children[i];
			if (child == nullptr)
				continue;
			if (here == root)
				child->fail = root;
			else
			{
				TrieNode* tmp = here->fail;
				while (tmp != root && tmp->children[i] == nullptr)
					tmp = tmp->fail;
				if (tmp->children[i])
					tmp = tmp->children[i];
				child->fail = tmp;
			}
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

vector<pair<int, int>>ahoCorasick(const string& s, TrieNode* root)
{
	vector<pair<int, int>>ret;
	TrieNode* state = root;
	for (int i = 0; i < s.size(); ++i)
	{
		int chr = s[i] - 'a';
		while (state != root && state->children[chr] == nullptr)
			state = state->fail;
		if (state->children[chr])
			state = state->children[chr];
		for (int j = 0; j < state->output.size(); ++j)
			ret.push_back(make_pair(i, state->output[j]));
	}
	return ret;
}
int main()
{
	TrieNode* Trie = new TrieNode();
	const char* a[2];
	a[1]= "APPLE";
	a[2]= "NOTE";
	for(int i=0;i<2;++i)
	Trie->insert(i,a[i]);
	computeFailFunc(Trie);
	vector<pair<int, int>>ret =
		ahoCorasick("NOTEBAANAPPLENOTEBOOK", Trie);
	for (int i = 0; i < ret.size(); ++i)
	{
		cout << ret[i].first << " " << ret[i].second << endl;
	}

}