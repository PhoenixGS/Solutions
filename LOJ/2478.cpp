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

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 300000 + 10;

struct sta
{
	long long f;
	int c;

	sta(long long _f = 0, int _c = 0): f(_f), c(_c){}

	sta operator + (const sta y)
	{
		return sta(f + y.f, c + y.c);
	}

	sta operator + (const long long del)
	{
		return sta(f + del, c);
	}
};

int n, k;
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
sta f[_n][3];
long long delta;

sta max(sta x, sta y)
{
	if (x.f > y.f || (x.f == y.f && x.c > y.c))
	{
		return x;
	}
	else
	{
		return y;
	}
}

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
	f[u][0] = sta(0, 0);
	f[u][1] = sta(delta, 1);
	f[u][2] = sta(delta, 1);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			dfs(v, u);
			f[u][2] = max(f[u][2] + f[v][0], f[u][1] + f[v][1] + sta(cost - delta, -1));
			f[u][1] = max(f[u][0] + f[v][1] + cost, f[u][1] + f[v][0]);
			f[u][0] = f[u][0] + f[v][0];
		}
	}
	f[u][0] = max(f[u][0], max(f[u][1], f[u][2]));
}

void check(long long mid)
{
	delta = mid;
	dfs(1, 0);
}

int main()
{
	scanf("%d%d", &n, &k);
	k++;
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		int cost = read();
		add(u, v, cost);
		add(v, u, cost);
	}
	long long l = -INF;
	long long r = INF;
	while (l < r)
	{
		long long mid = (l + r) >> 1;
		check(mid);
		if (f[1][0].c >= k)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	check(l);
	printf("%lld\n", f[1][0].f - (long long)k * l);
	return 0;
}
