#include <cstdio>
#include <queue>
#include <vector>
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

struct heap
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
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n, q;
char cas[20];
int col[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int dep[_n], fa[_n][22];
heap sub[_n], dis[_n], ans;
int root, sum;
int f[_n], size[_n], vis[_n];
int ff[_n], tp[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void calc(int u, int cas)
{
	if (cas == 1)
	{
		if (! dis[u].empty())
		{
			int mx = dis[u].top();
			dis[u].del(mx);
			if (! dis[u].empty())
			{
				int my = dis[u].top();
//				printf("++%d %d\n", u, mx + my);
				ans.push(mx + my);
			}
			dis[u].push(mx);
		}
	}
	else
	{
		if (! dis[u].empty())
		{
			int mx = dis[u].top();
			dis[u].del(mx);
			if (! dis[u].empty())
			{
				int my = dis[u].top();
//				printf("--%d %d\n", u, mx + my);
				ans.del(mx + my);
			}
			dis[u].push(mx);
		}
	}
}

void cad(int v, int u, int cas)
{
	if (cas == 1)
	{
		if (! sub[v].empty())
		{
//			printf("+%d %d\n", u, sub[v].top() + 1);
			dis[u].push(sub[v].top() + 1);
		}
	}
	else
	{
		if (! sub[v].empty())
		{
//			printf("-%d %d\n", u, sub[v].top() + 1);
			dis[u].del(sub[v].top() + 1);
		}
	}
}

void dfs0(int u, int father)
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
			dep[v] = dep[u] + 1;
			dfs0(v, u);
		}
	}
}

int querylca(int u, int v)
{
	if (dep[u] > dep[v])
	{
		std::swap(u, v);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) & (dep[v] - dep[u]))
		{
			v = fa[v][i];
		}
	}
	if (u == v)
	{
		return u;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

int calcdis(int u, int v)
{
	int lca = querylca(u, v);
	return dep[u] + dep[v] - 2 * dep[lca];
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
	f[u] = std::max(f[u], sum - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void dfs(int u, int father)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void cc(int u, int father, int deep)
{
	sub[root].push(deep);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			cc(v, u, deep + 1);
		}
	}
}

void solve(int u, int father, int top)
{
	vis[u] = 1;
	ff[u] = father;
	tp[u] = top;
//	printf("..%d %d %d\n", u, father, tp[u]);
	dis[u].push(0);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u);
			root = 0;
			sum = size[v];
			getroot(v, u);
			cc(v, u, 0);
			cad(root, u, 1);
			solve(root, u, v);
		}
	}
	calc(u, 1);
}

void change(int u)
{
	if (col[u] == 1)
	{
		int v = u;
		calc(v, -1);
		dis[v].del(0);
		calc(v, 1);
		while (ff[v])
		{
			calc(ff[v], -1);
			cad(v, ff[v], -1);
//			printf("!!%d %d\n", v, calcdis(u, tp[v]));
			sub[v].del(calcdis(u, tp[v]));
			cad(v, ff[v], 1);
			calc(ff[v], 1);
			v = ff[v];
		}
	}
	else
	{
		int v = u;
		calc(v, -1);
		dis[v].push(0);
		calc(v, 1);
		while (ff[v])
		{
			calc(ff[v], -1);
			cad(v, ff[v], -1);
			sub[v].push(calcdis(u, tp[v]));
			cad(v, ff[v], 1);
			calc(ff[v], 1);
			v = ff[v];
		}
	}
	col[u] ^= 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs0(1, 0);
	for (int i = 1; i <= n; i++)
	{
		col[i] = 1;
	}
	f[0] = INF;
	root = 0;
	sum = n;
	getroot(1, 0);
	solve(root, 0, 0);
	scanf("%d", &q);
	while (q--)
	{
		scanf("%s", cas + 1);
		if (cas[1] == 'G')
		{
//			printf("E%d\n", ans.empty());
			if (ans.empty())
			{
				puts("-1");
			}
			else
			{
				printf("%d\n", ans.top());
			}
		}
		else
		{
			int u = read();
			change(u);
		}
	}
	return 0;
}
