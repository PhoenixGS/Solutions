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

const int _n = 500000 + 10;
int n;
double q[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
double val[2 * _n];
double f[_n], g[_n];
double ans;

void add(int u, int v, double cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void calc_f(int u, int father)
{
	f[u] = 1.0 - q[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i];
		if (v != father)
		{
			calc_f(v, u);
			f[u] = f[u] * (f[v] + (1 - f[v]) * (1 - cost));
		}
	}
}

void calc_g(int u, int father)
{
	double tmp = g[u] * (1.0 - q[u]);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i];
		if (v != father)
		{
			tmp = tmp * (f[v] + (1 - f[v]) * (1 - cost));
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i];
		if (v != father)
		{
			double t = tmp / (f[v] + (1 - f[v]) * (1 - cost));
			g[v] = t + (1 - t) * (1 - cost);
			calc_g(v, u);
		}
	}
}

int main()
{
	n = read();
	for (int i = 1; i < n; i++)
	{
		int u, v, p;
		u = read();
		v = read();
		p = read();
		add(u, v, (double)p / 100);
		add(v, u, (double)p / 100);
	}
	for (int i = 1; i <= n; i++)
	{
		q[i] = read();
		q[i] = q[i] / 100;
	}
	calc_f(1, 0);
	g[1] = 1.0;
	calc_g(1, 0);
	ans = 0.0;
	for (int i = 1; i <= n; i++)
	{
		ans += (1 - f[i] * g[i]);
	}
	printf("%.6f\n", ans);
	return 0;
}
