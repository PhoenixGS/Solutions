#include <cstdio>
#include <cstring>
#include <algorithm>

const int M = 1000000007;
const int _n = 100000 + 10;
int T, n;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int f[_n];
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
	f[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			f[u] = (long long)f[u] * (f[v] + 1) % M;
		}
	}
	ans = (ans + f[u]) % M;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		edgenum = 0;
		memset(head, 0, sizeof(head));
		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			add(u, v);
			add(v, u);
		}
		ans = 0;
		dfs(1, 0);
		printf("%d\n", ans);
	}
	return 0;
}
