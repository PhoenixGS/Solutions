#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
char s[1000000];
int edgenum;
int vet[1000000], nextx[1000000], head[1000000];
int fail[1000000];
int times;
int pos[1000000];
int left[1000000], right[1000000];
int f[1000000];
int maxx;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void getfail()
{
	int j = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		fail[i] = j;
	}
}

void dfs(int u)
{
	times++;
	pos[times] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! f[v])
		{
			dfs(v);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (f[v])
		{
			dfs(v);
		}
	}
}

void c()
{
	int now = n;
	while (now)
	{
		f[now] = 1;
		now = fail[now];
	}
}

void del(int x)
{
	maxx = std::max(maxx, right[x] - left[x]);
	left[right[x]] = left[x];
	right[left[x]] = right[x];
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	getfail();
	c();
	for (int i = 1; i <= n; i++)
	{
		add(fail[i], i);
	}
	dfs(0);
	for (int i = 1; i <= n; i++)
	{
		left[i] = i - 1;
		right[i] = i + 1;
	}
	maxx = 1;
	for (int i = 2; i <= n + 1; i++)
	{
		if (f[pos[i]])
		{
			if (maxx <= pos[i])
			{
				printf("%d\n", pos[i]);
				return 0;
			}
		}
		del(pos[i]);
	}
	return 0;
}
