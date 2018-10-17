#include <cstdio>

int n, s;
int knum;
int to[5000000][11];
int pre[5000000];
int len[5000000];
long long ans;
int in[300000];
int col[300000];
int edgenum;
int vet[300000], nextx[300000], head[300000];

void add_edge(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

int add(int last, int c)
{
	int u = last;
	if (to[u][c])
	{
		int w = to[u][c];
		if (len[u] + 1 == len[w])
		{
			return w;
		}
		knum++;
		int neww = knum;
		pre[neww] = pre[w];
		for (int i = 0; i < s; i++)
		{
			to[neww][i] = to[w][i];
		}
		len[neww] = len[u] + 1;
		pre[w] = neww;
		for (; u && to[u][c] == w; u = pre[u])
		{
			to[u][c] = neww;
		}
		return neww;
	}
	knum++;
	int v = knum;
	len[v] = len[u] + 1;
	for (; u && ! to[u][c]; u = pre[u])
	{
		to[u][c] = v;
	}
	if (! u)
	{
		pre[v] = 1;
		return v;
	}
	int w = to[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		return v;
	}
	knum++;
	int neww = knum;
	pre[neww] = pre[w];
	for (int i = 0; i < s; i++)
	{
		to[neww][i] = to[w][i];
	}
	len[neww] = len[u] + 1;
	pre[w] = pre[v] = neww;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
	return v;
}

void dfs(int u, int father, int last)
{
	last = add(last, col[u]);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u, last);
		}
	}
}

int main()
{
	knum = 1;
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
		in[u]++;
		in[v]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 1)
		{
			dfs(i, -1, 1);
		}
	}
	ans = 0;
	for (int i = 1; i <= knum; i++)
	{
		ans = ans + len[i] - len[pre[i]];
	}
	printf("%lld\n", ans);
	return 0;
}
