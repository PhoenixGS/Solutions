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

const int INF = 1000000000;
const int _n = 200000 + 10;
int n;
int fa[_n];
long long le[_n];
long long p[_n], q[_n], l[_n];
long long deep[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
long long val[2 * _n];
int size[_n];
long long f[_n];
int ff[_n];
int vis[_n];
int root;
int last;
int vv[_n];
int stack[_n];
int top;

bool comp(int x, int y)
{
	return deep[x] - l[x] > deep[y] - l[y];
}

void add(int u, int v, long long cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void init(int u, int father, long long dep)
{
	deep[u] = dep;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != father)
		{
			init(v, u, dep + cost);
		}
	}
}

void getroot(int u, int father, int S)
{
	size[u] = 1;
	ff[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			getroot(v, u, S);
			size[u] += size[v];
			ff[u] = std::max(ff[u], size[v]);
		}
	}
	ff[u] = std::max(ff[u], S - size[u]);
	if (ff[u] < ff[root])
	{
		root = u;
	}
}

void dfs(int u, int father)
{
	last++;
	vv[last] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u);
		}
	}
}

inline long long up(int x, int y)
{
	return f[x] - f[y];
}

inline long long down(int x, int y)
{
	return deep[x] - deep[y];
}

inline long long calc(int u, int v)
{
	return f[v] + (deep[u] - deep[v]) * p[u] + q[u];
}

void solve(int u, int S)
{
	printf("K%d %d\n", u, S);
	vis[u] = true;
	if (S == 1)
	{
		return;
	}
	int k = fa[u];
	while (k && ! vis[k])
	{
		k = fa[k];
	}
	if (fa[u] != 0 && ! vis[fa[u]])
	{
		root = 0;
		getroot(fa[u], 0, S - size[u]);
		solve(root, S - size[u]);
		int v = fa[u];
		while (v != k && deep[u] - deep[v] <= l[u])
		{
			f[u] = std::min(f[u], f[v] + p[u] * (deep[u] - deep[v]) + q[u]);
			printf("OOO%d %d %lld\n", u, v, f[v] + p[u] * (deep[u] - deep[v]) + q[u]);
			v = fa[v];
		}
	}
	last = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != fa[u] && ! vis[v])
		{
			dfs(v, 0);
		}
	}
	std::sort(vv + 1, vv + last + 1, comp);
	int now = u;
	top = 0;
	printf("#");
	printf("%d\n", u);
	for (int i = 1; i <= last; i++)
	{
		printf("M%d %d\n", vv[i], u);
		while (now != k && deep[vv[i]] - deep[now] <= l[vv[i]])
		{
			while (top >= 2 && up(stack[top], stack[top - 1]) * down(stack[top], now) <= up(stack[top], now) * down(stack[top - 1], stack[top]))
			{
				printf("^%lld %lld %lld\n", up(stack[top], stack[top - 1]), down(stack[top], now), up(stack[top], stack[top - 1]) * down(stack[top], now) );
				top--;
			}
			top++;
			stack[top] = now;
			printf("??%d %lld %lld\n", now, deep[vv[i]] - deep[now], l[vv[i]]);
			now = fa[now];
		}
		printf("X%d\n", top);
		if (top)
		{
			int l = 1;
			int r = top;
			while (l < r)
			{
				int mid = (l + r) >> 1;
				if (calc(vv[i], stack[mid]) < calc(vv[i], stack[mid + 1]))
				{
					r = mid;
				}
				else
				{
					l = mid + 1;
				}
			}
			printf("L%d %d\n", vv[i], stack[l]);
			for (int j = 1; j <= top; j++)
			{
				printf("LL%d %lld\n", stack[j], calc(vv[i], stack[j]));
			}
			puts("");
			f[vv[i]] = std::min(f[vv[i]], calc(vv[i], stack[l]));
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != fa[u] && ! vis[v])
		{
			root = 0;
			getroot(v, 0, size[v]);
			solve(root, size[v]);
		}
	}
}

int main()
{
	n = read();
	int cas = read();
	for (int i = 2; i <= n; i++)
	{
		fa[i] = read();
		le[i] = read();
		add(i, fa[i], le[i]);
		add(fa[i], i, le[i]);
		p[i] = read();
		q[i] = read();
		l[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		f[i] = (long long)INF * INF;
	}
	f[1] = 0;
	init(1, 0, 0);
	ff[0] = INF;
	root = 0;
	getroot(1, 0, n);
	solve(root, n);
	for (int i = 2; i <= n; i++)
	{
		printf("%lld\n", f[i]);
	}
	puts("");
	return 0;
}
