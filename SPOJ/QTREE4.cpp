#include <cstdio>
#include <algorithm>
#include <queue>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct HEAP
{
	std::priority_queue<int> A, B;

	bool empty()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		return A.empty();
	}

	int top()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		return A.top();
	}

	void push(int x)
	{
		A.push(x);
	}

	void del(int x)
	{
		B.push(x);
	}

	void pop()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		A.pop();
	}
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n, q;
int z[2 * _n];
char s[20];
int col[_n];
int times;
int dfn[_n];
int pos[2 * _n];
int st[2 * _n][22];
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
HEAP heap[_n], maxx[_n], ans;
int fa[_n][22];
int deep[_n], dist[_n];
int root, S;
int f[_n], size[_n];
int vis[_n], ff[_n], tag[_n];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	times++;
	dfn[u] = times;
	pos[times] = u;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dist[v] = dist[u] + cost;
			dfs(v, u);
			times++;
			pos[times] = u;
		}
	}
}

int query_lca(int x, int y)
{
	int l = dfn[x], r = dfn[y];
	if (l > r)
	{
		std::swap(l, r);
	}
	int k = z[r - l + 1];
	if (deep[st[l][k]] < deep[st[r - (1 << k) + 1][k]])
	{
		return st[l][k];
	}
	else
	{
		return st[r - (1 << k) + 1][k];
	}
	/*
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 0; i <= 20; i++)
	{
		if ((1 << i) & (deep[x] - deep[y]))
		{
			x = fa[x][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
	*/
}

int dis(int x, int y)
{
	int lca = query_lca(x, y);
	return dist[x] + dist[y] - 2 * dist[lca];
}

void getroot(int u, int father)
{
	f[u] = 0;
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			getroot(v, u);
			size[u] += size[v];
			f[u] = std::max(f[u], size[v]);
		}
	}
	f[u] = std::max(f[u], S - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void calc(int u, int father, int idx, int root)
{
	size[u] = 1;
	if (col[u] == 0)
	{
		heap[idx].push(dis(u, root));
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			calc(v, u, idx, root);
			size[u] += size[v];
		}
	}
}

int calcmax(int u)
{
	int mx = -INF;
	if (! maxx[u].empty())
	{
		int xx = maxx[u].top();
		maxx[u].pop();
		if (! maxx[u].empty())
		{
			int yy = maxx[u].top();
			mx = xx + yy;
		}
		maxx[u].push(xx);
	}
	return mx;
}

void solve(int u, int father)
{
	ff[u] = father;
	vis[u] = 1;
	if (col[u] == 0)
	{
		maxx[u].push(0);
		maxx[u].push(0);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			calc(v, u, i / 2, u);
			if (! heap[i / 2].empty())
			{
				maxx[u].push(heap[i / 2].top());
			}
		}
	}
	ans.push(calcmax(u));
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			root = 0;
			S = size[v];
			getroot(v, u);
			tag[root] = i / 2;
			solve(root, u);
		}
	}
}

void change(int u)
{
	ans.del(calcmax(u));
	if (col[u] == 0)
	{
		maxx[u].push(0);
		maxx[u].push(0);
	}
	else
	{
		maxx[u].del(0);
		maxx[u].del(0);
	}
	ans.push(calcmax(u));
	int idx = tag[u];
	int now = ff[u];
	while (now)
	{
		ans.del(calcmax(now));
		if (! heap[idx].empty())
		{
			maxx[now].del(heap[idx].top());
		}
		if (col[u] == 0)
		{
			heap[idx].push(dis(u, now));
		}
		else
		{
			heap[idx].del(dis(u, now));
		}
		if (! heap[idx].empty())
		{
			maxx[now].push(heap[idx].top());
		}
		ans.push(calcmax(now));
		idx = tag[now];
		now = ff[now];
	}
}

int main()
{
#ifdef DEBUG
	freopen("QTREE4.in", "r", stdin);
#endif
	edgenum = 1;
	scanf("%d", &n);
	z[1] = 0;
	for (int i = 2; i <= 2 * n - 1; i++)
	{
		z[i] = z[i >> 1] + 1;
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		int cost = read();
		add(u, v, cost);
		add(v, u, cost);
	}
	dfs(1, 0);
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		st[i][0] = pos[i];
	}
	for (int j = 1; (1 << j) <= 2 * n - 1; j++)
	{
		for (int i = 1; i + (1 << j) <= 2 * n - 1; i++)
		{
			if (deep[st[i][j - 1]] < deep[st[i + (1 << (j - 1))][j - 1]])
			{
				st[i][j] = st[i][j - 1];
			}
			else
			{
				st[i][j] = st[i + (1 << (j - 1))][j - 1];
			}
		}
	}
	f[0] = INF;
	root = 0;
	S = n;
	getroot(1, 0);
	tag[root] = 0;
	solve(root, 0);
	scanf("%d", &q);
	while (q--)
	{
		scanf("%s", s + 1);
		if (s[1] == 'C')
		{
			int u = read();
			col[u] ^= 1;
			change(u);
		}
		else
		{
			if (ans.top() == -INF)
			{
				puts("They have disappeared.");
			}
			else
			{
				printf("%d\n", ans.top());
			}
		}
	}
	return 0;
}
