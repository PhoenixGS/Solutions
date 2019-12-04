#include <cstdio>
#include <queue>
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

const int INF = 1000000000;
const int _n = 100000 + 10;

int n, q;

int col[_n];

//edge
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];

int deep[_n];

//ST
int times;
int dfn[_n], pos[2 * _n];

//div
int root, S;
int f[_n], size[_n];
int vis[_n];
int ff[_n], tag[_n];

struct HEAP
{
	std::priority_queue<int, std::vector<int>, std::greater<int> > A, B;

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

	void pop()
	{
		while (! A.empty() && ! B.empty() && A.top() == B.top())
		{
			A.pop();
			B.pop();
		}
		A.pop();
	}

	void push(int x)
	{
		A.push(x);
	}

	void del(int x)
	{
		B.push(x);
	}
};

struct ST
{
	int z[2 * _n];
	int st[2 * _n][22];

	int mx(int x, int y)
	{
		return deep[x] < deep[y] ? x : y;
	}

	void init()
	{
		z[1] = 0;
		for (int i = 2; i <= 2 * n - 1; i++)
		{
			z[i] = z[i >> 1] + 1;
		}
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			st[i][0] = pos[i];
		}
		for (int j = 1; (1 << j) <= 2 * n - 1; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= 2 * n - 1; i++)
			{
				st[i][j] = mx(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int query(int x, int y)
	{
		int l = dfn[x];
		int r = dfn[y];
		if (l > r)
		{
			std::swap(l, r);
		}
		int k = z[r - l + 1];
		return mx(st[l][k], st[r - (1 << k) + 1][k]);
	}
};

HEAP heap[_n], maxx[_n];
ST st;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	times++;
	dfn[u] = times;
	pos[times] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
			times++;
			pos[times] = u;
		}
	}
}

int dis(int x, int y)
{
	int lca = st.query(x, y);
	return deep[x] + deep[y] - 2 * deep[lca];
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

void calc(int u, int father, int root, int idx)
{
	size[u] = 1;
	if (col[u] == 0)
	{
		heap[idx].push(dis(root, u));
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			calc(v, u, root, idx);
			size[u] += size[v];
		}
	}
}

void solve(int u, int father)
{
	ff[u] = father;
	vis[u] = 1;
	if (col[u] == 0)
	{
		maxx[u].push(0);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			calc(v, u, u, i >> 1);
			if (! heap[i >> 1].empty())
			{
				maxx[u].push(heap[i >> 1].top());
			}
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			root = 0;
			S = size[v];
			getroot(v, 0);
			tag[root] = i >> 1;
			solve(root, u);
		}
	}
}

void change(int u)
{
	if (col[u] == 0)
	{
		maxx[u].push(0);
	}
	else
	{
		maxx[u].del(0);
	}
	int idx = tag[u];
	int now = ff[u];
	while (now)
	{
		if (! heap[idx].empty())
		{
			maxx[now].del(heap[idx].top());
		}
		if (col[u] == 0)
		{
			heap[idx].push(dis(now, u));
		}
		else
		{
			heap[idx].del(dis(now, u));
		}
		if (! heap[idx].empty())
		{
			maxx[now].push(heap[idx].top());
		}
		idx = tag[now];
		now = ff[now];
	}
}

int query(int u)
{
	int ans = INF;
	if (! maxx[u].empty())
	{
		ans = std::min(ans, maxx[u].top());
	}
	int idx = tag[u];
	int now = ff[u];
	while (now)
	{
		int xx = INF;
		if (! heap[idx].empty())
		{
			xx = heap[idx].top();
		}
		if (! maxx[now].empty())
		{
			if (maxx[now].top() != xx)
			{
				ans = std::min(ans, dis(u, now) + maxx[now].top());
			}
			else
			{
				maxx[now].pop();
				if (! maxx[now].empty())
				{
					ans = std::min(ans, dis(u, now) + maxx[now].top());
				}
				maxx[now].push(xx);
			}
		}
		idx = tag[now];
		now = ff[now];
	}
	return ans;
}

int main()
{
	edgenum = 1;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		col[i] = 1;
	}
	dfs(1, 0);
	st.init();
	f[0] = INF;
	root = 0;
	S = n;
	getroot(1, 0);
	solve(root, 0);
	scanf("%d", &q);
	while (q--)
	{
		int op = read();
		if (op == 0)
		{
			int u = read();
			col[u] ^= 1;
			change(u);
		}
		else
		{
			int u = read();
			int ans = query(u);
			printf("%d\n", ans == INF ? -1 : ans);
		}
	}
	return 0;
}
