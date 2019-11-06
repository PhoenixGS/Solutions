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

struct edge
{
	int u, v, cost, col;
};

const int _n = 50000 + 10, _m = 100000 + 10;
int n, m, need;
edge z[_m];
int f[_n];
int ans;

bool comp(edge x, edge y)
{
	return x.cost < y.cost || (x.cost == y.cost && x.col < y.col);
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

int check(int mid)
{
	for (int i = 1; i <= m; i++)
	{
		if (z[i].col == 0)
		{
			z[i].cost -= mid;
		}
	}
	std::sort(z + 1, z + m + 1, comp);
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	ans = 0;
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		int xx = findfather(z[i].u);
		int yy = findfather(z[i].v);
		if (xx != yy)
		{
			ans += z[i].cost;
			f[xx] = yy;
			if (z[i].col == 0)
			{
				cnt++;
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		if (z[i].col == 0)
		{
			z[i].cost += mid;
		}
	}
	return cnt;
}

int main()
{
	scanf("%d%d%d", &n, &m, &need);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &z[i].u, &z[i].v, &z[i].cost, &z[i].col);
		z[i].u++;
		z[i].v++;
	}
	int l = -105;
	int r = 105;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid) >= need)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	check(l);
	printf("%d\n", ans + l * need);
	return 0;
}

