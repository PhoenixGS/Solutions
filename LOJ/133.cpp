#include <cstdio>

const int _n = (1 << 12) + 10;
int n, m, op;
long long tree[_n][_n];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int y, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		for (int j = y; j <= m; j += lowbit(j))
		{
			tree[i][j] += delta;
		}
	}
}

long long query(int x, int y)
{
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		for (int j = y; j; j -= lowbit(j))
		{
			ans += tree[i][j];
		}
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	while (scanf("%d", &op) == 1)
	{
		if (op == 1)
		{
			int x, y, delta;
			scanf("%d%d%d", &x, &y, &delta);
			add(x, y, delta);
		}
		else
		{
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			printf("%lld\n", query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1));
		}
	}
	return 0;
}
