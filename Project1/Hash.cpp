#include <stdio.h>
#include <string.h>
#define MAX_TABLE 500000

int T;
int n;
char tmp[10000][11];
int tmpsize[10000];
char tmp2[11];

typedef struct
{
	char key[11];
}Hash;
Hash tb[MAX_TABLE];

unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	return hash % MAX_TABLE;
}

int find(const char *key)
{
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;
	while (tb[h].key[0] != 0 && cnt--)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			return 1;
		}
		h = (h + 1) % MAX_TABLE;
	}
	return 0;
}

int add(const char *key)
{
	unsigned long h = hash(key);
	while (tb[h].key[0] != 0)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			return 0;
		}
		h = (h + 1) % MAX_TABLE;
	}
	strcpy(tb[h].key, key);
	return 1;
}

int main()
{
	scanf("%d", &T);
	for (int test = 1; test <= T; ++test)
	{
		for (int i = 0; i < MAX_TABLE; ++i)
			for (int j = 0; j < 11; ++j)
				tb[i].key[j] = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", &tmp[i]);
			add(tmp[i]);
			int cnt = 0;
			while (tmp[i][cnt++] != 0);
			tmpsize[i] = cnt-1;
		}
		int flag = 0;
		for (int i = 0; i < n; ++i)
		{
			if (flag == 1)
				break;
			for(int a=0;a<tmpsize[i]-1;++a)
			{
				if (flag == 1)
					break;
				for (int j = 0; j <= a; ++j)
					tmp2[j] = tmp[i][j];
				if (find(tmp2) == 1)
				{
					flag = 1;
				}
				for (int j = 0; j <= a; ++j)
					tmp2[j] = 0;
			}
		}
		if (flag == 1)
			printf("NO\n");
		else
			printf("YES\n");
	}
}