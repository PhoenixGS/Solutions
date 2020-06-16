#include <cstdio>
#include <vector>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 500000 + 10;
int n, q;
unsigned s;
int tt[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int root;
int fa[_n][22], deep[_n], len[_n], son[_n], top[_n];
std::vector<int> up[_n], down[_n];
int lastans;
long long ans;

inline unsigned get(unsigned x)
{
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
			if (len[v] > len[son[u]])
			{
				son[u] = v;
			}
		}
	}
	len[u] = len[son[u]] + 1;
}

void dfs2(int u, int father, int chain)
{
	top[u] = chain;
	if (u == chain)
	{
		for (int i = 0, v = u; i <= len[u]; i++, v = fa[v][0])
		{
			up[u].push_back(v);
		}
		for (int i = 0, v = u; i <= len[u]; i++, v = son[v])
		{
			down[u].push_back(v);
		}
	}
	if (son[u])
	{
		dfs2(son[u], u, chain);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != son[u])
		{
			dfs2(v, u, v);
		}
	}
}

int query(int x, int k)
{
	if (k == 0)
	{
		return x;
	}
	x = fa[x][tt[k]];
	k = k - (1 << tt[k]);
	k = k - (deep[x] - deep[top[x]]);
	x = top[x];
	if (k >= 0)
	{
		return up[x][k];
	}
	else
	{
		return down[x][-k];
	}
}

int main()
{
	scanf("%d%d%u", &n, &q, &s);
	for (int i = 2; i <= n; i++)
	{
		tt[i] = tt[i >> 1] + 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int fa = read();
		if (fa == 0)
		{
			root = i;
		}
		else
		{
			add(fa, i);
			add(i, fa);
		}
	}
	deep[root] = 1;
	dfs(root, 0);
	dfs2(root, 0, root);
	lastans = 0;
	for (int i = 1; i <= q; i++)
	{
		int x = ((get(s) ^ lastans) % n) + 1;
		int k = ((get(s) ^ lastans) % deep[x]);
		lastans = query(x, k);
		ans = ans ^ (1ll * i * lastans);
	}
	printf("%lld\n", ans);
	return 0;
}
