#include <cstdio>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int n, k;
int edgenum;
int vet[300000];
int nextx[300000];
int head[200000];
int f[200000];
int ans;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	int minx = 1000000000;
	int maxx = -1000000000;
	bool flag = false;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			flag = true;
			dfs(v, u);
			minx = std::min(minx, f[v]);
			maxx = std::max(maxx, f[v]);
		}
	}
	if (! flag)
	{
		f[u] = -1;
	}
	else
	{
		if (minx <= -k)
		{
			ans++;
			f[u] = k;
		}
		else
		{
			if (minx + maxx > 0)
			{
				f[u] = maxx - 1;
			}
			else
			{
				f[u] = minx - 1;
			}
		}
	}
}

int main()
{
	edgenum = 0;
	n = read();
	k = read();
	for (int i = 1; i < n; i++)
	{
		int u, v;
		u = read();
		v = read();
		u++;
		v++;
		add(u, v);
		add(v, u);
	}
	if (k == 0)
	{
		printf("%d\n", n);
		return 0;
	}
	dfs(1, -1);
	if (f[1] < 0)
	{
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}

<<<<<<< HEAD
=======

>>>>>>> 984c9bc947b1ca2134dfae21c5962d44c66cb9c6
