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

const int _n = 100000 + 10;
int n, m;
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int cnt[_n];
int vis[_n];
int top;
int stack[_n], stac[_n];
int ff[_n];
int last;
int vv[_n], ss[_n];
long double f[_n], g[_n];
long double ans;

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void findc(int u, int father, int pre)
{
	vis[u] = 1;
	top++;
	stack[top] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if ((pre ^ i) != 1)
		{
			stac[top] = cost;
			if (vis[v])
			{
				if (! last)
				{
					last = 0;
					int k = top;
//					puts("V");
					for (; k >= 1 && stack[k] != v; k--);
//					puts("P");
					for (int i = k; i <= top; i++)
					{
//						printf("LL%d\n", stack[i]);
						ff[stack[i]] = 1;
						last++;
						vv[last - 1] = stack[i];
						ss[last - 1] = stac[i];
					}
				}
			}
			else
			{
				findc(v, u, i);
			}
		}
	}
	top--;
}

void dfs(int u, int father)
{
	if (u == 79)
	{
//		printf("XX%d\n", ff[u]);
	}
	cnt[u] = 0;
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! ff[v])
		{
			cnt[u]++;
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
//		if (u == 79) printf("O%d %.5f %d\n", v, (double)f[v], ff[v]);
		if (v != father && ! ff[v])
		{
			dfs(v, u);
			f[u] = f[u] + (f[v] + cost) / cnt[u];
		}
	}
}

void dfs2(int u, int father)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father && ! ff[v])
		{
			if (father == 0)
			{
				if (m == n - 1)
				{
					if (cnt[u] == 1)
					{
						g[v] = cost;
					}
					else
					{
						g[v] = (f[u] * cnt[u] - f[v] - cost) / (cnt[u] - 1) + cost;
					}
				}
				else
				{
					g[v] = (f[u] * cnt[u] - f[v] - cost + g[u]) / (cnt[u] + 1) + cost;
				}
			}
			else
			{
				g[v] = (f[u] * cnt[u] - f[v] - cost + g[u]) / cnt[u] + cost;
			}
			/*
			g[v] = father == 0 ? (f[u] * cnt[u] - f[v] - cost) / (cnt[u] - 1) + cost : (f[u] * cnt[u] - f[v] - cost + g[u]) / cnt[u] + cost;
			if (father == 0 && cnt[u] - 1 == 0)
			{
				g[v] = cost;
			}*/
			dfs2(v, u);
		}
	}
}

void solve()
{
	long double mul = 1.0;
	long double s = 0.0;
	long double mm = 1.0;
	long double sum = 0;
	for (int i = 0; i < last; i++)
	{
		mm = mm / (cnt[vv[i]] + 1);
	}
	sum = ss[0];
	for (int i = 1; i < last; i++)
	{
//		if (cnt[vv[i]] + (vv[i] != vv[last - 1]) == 0)
		if (i == last - 1)
		{
			s = s + mul * (f[vv[i]] + sum);
		}
		else
		{
//			s = s + mul * (f[vv[i]] + sum) * cnt[vv[i]] / (cnt[vv[i]] + (vv[i] != vv[last - 1]));
			s = s + mul * (f[vv[i]] + sum) * cnt[vv[i]] / (cnt[vv[i]] + 1);
		}
		mul = mul / (cnt[vv[i]] + 1);
		sum = sum + ss[i];
	}
//	printf("M%f\n", mul);
//	printf("S%f\n", sum);
	g[vv[0]] += s;
	for (int i = last - 1; i >= 1; i--)
	{
		s = s - mm * (cnt[vv[i]] + 1) * (cnt[vv[(i + 1) % last]] + 1) * (f[vv[i]] + sum - ss[i]);
		s = s / (cnt[vv[(i + 1) % last]] + 1);
		s = s + (f[vv[(i + 1) % last]]) * cnt[vv[(i + 1) % last]] / (cnt[vv[(i + 1) % last]] + 1);
		s = s - mm * (cnt[vv[i]] + 1) * (cnt[vv[(i - 1 + last) % last]] + 1) * (f[vv[(i - 1 + last) % last]] + sum - ss[(i - 1 + last) % last] - ss[i]) * cnt[vv[(i - 1 + last) % last]] / (cnt[vv[(i - 1 + last) % last]] + 1);
		s = s + mm * (cnt[vv[i]] + 1) * (cnt[vv[(i - 1 + last) % last]] + 1) * (f[vv[(i - 1 + last) % last]] + sum - ss[(i - 1 + last) % last] - ss[i]);
		s = s + ss[i];
//		s = (s - mm * (cnt[vv[i]] + 1) * (cnt[vv[(i + 1) % last]] + 1) * (f[vv[i]] + sum - ss[i])) / (cnt[vv[(i + 1) % last]] + 1) + f[vv[(i + 1) % last]] * cnt[vv[(i + 1) % last]] / (cnt[vv[(i + 1) % last]] + 1) + ss[i];
		g[vv[i]] += s;
	}
}

int main()
{
	n = read();
	m = read();
	edgenum = 1;
	for (int i = 1; i <= m; i++)
	{
		int u, v, cost;
		u = read();
		v = read();
		cost = read();
		add(u, v, cost);
		add(v, u, cost);
	}
	if (m == n - 1)
	{
		dfs(1, 0);
		dfs2(1, 0);
		ans = 0.0;
		for (int i = 1; i <= n; i++)
		{
			ans = ans + (i == 1 ? f[i] : f[i] * cnt[i] / (cnt[i] + 1) + g[i] / (cnt[i] + 1));
		}
		ans = ans / n;
		printf("%.5f\n", (double)ans);
	}
	else
	{
		findc(1, 0, 0);
/*		for (int i = 0; i < last; i++)
		{
			printf("%d ", vv[i]);
		}
		puts("");
		for (int i = 0; i < last; i++)
		{
			printf("%d ", ss[i]);
		}
		puts("");*/
		for (int i = 0; i < last; i++)
		{
			dfs(vv[i], 0);
		}
/*		for (int i = 0; i < last; i++)
		{
			printf("%d %d\n", vv[i], ss[i]);
		}*/
		solve();
/*		for (int i = 0; i < last; i++)
		{
			printf("L%d %f\n", vv[i], g[vv[i]]);
		}*/
		for (int i = 0; i < last / 2; i++)
		{
			std::swap(vv[i], vv[last - 1 - i]);
		}
		for (int i = 0; i < (last - 1) / 2; i++)
		{
			std::swap(ss[i], ss[last - 2 - i]);
		}
		solve();
		for (int i = 0; i < last; i++)
		{
			dfs2(vv[i], 0);
		}
		for (int i = 1; i <= n; i++)
		{
//			printf("%.5f %.5f\n", (double)f[i], (double)g[i]);
			if (ff[i])
			{
				ans = ans + (f[i] * cnt[i] + g[i]) / (cnt[i] + 2);
			}
			else
			{
				ans = ans + (f[i] * cnt[i] + g[i]) / (cnt[i] + 1);
			}
		}
		ans = ans / n;
		printf("%.5f\n", (double)ans);
	}
	return 0;
}
