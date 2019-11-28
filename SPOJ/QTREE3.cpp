#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 100000 + 10;
int n, q;
int col[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int fa[_n][22];
int times;
int in[_n], out[_n];
int tree[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

inline int lowbit(int x)
{
	return x & -x;
}

void change(int pos, int delta)
{
	for (int i = pos; i <= n; i += lowbit(i))
	{
		tree[i] += delta;
	}
}

int query(int pos)
{
	int ans = 0;
	for (int i = pos; i; i -= lowbit(i))
	{
		ans += tree[i];
	}
	return ans;
}

void dfs(int u, int father)
{
	times++;
	in[u] = times;
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
			dfs(v, u);
		}
	}
	out[u] = times;
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	while (q--)
	{
		int op = read();
		if (op == 0)
		{
			int u = read();
			if (col[u] == 0)
			{
				change(in[u], 1);
				change(out[u] + 1, -1);
			}
			else
			{
				change(in[u], -1);
				change(out[u] + 1, 1);
			}
			col[u] ^= 1;
		}
		else
		{
			int u = read();
			if (query(in[u]) == 0)
			{
				puts("-1");
			}
			else
			{
				for (int i = 20; i >= 0; i--)
				{
					if (query(in[fa[u][i]]))
					{
						u = fa[u][i];
					}
				}
				printf("%d\n", u);
			}
		}
	}
	return 0;
}
