#include <cstdio>

const int _n = 2048 + 10;
int n, m;
long long ss1[_n][_n], ss2[_n][_n], ss3[_n][_n], ss4[_n][_n];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int y, int delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
	{
		for (int j = y; j <= m + 1; j += lowbit(j))
		{
			ss1[i][j] += delta;
			ss2[i][j] += (long long)x * delta;
			ss3[i][j] += (long long)y * delta;
			ss4[i][j] += (long long)x * y * delta;
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
			ans += ss1[i][j] * (x * y + x + y + 1);
			ans -= ss2[i][j] * (y + 1);
			ans -= ss3[i][j] * (x + 1);
			ans += ss4[i][j];
		}
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	int op;
	while (scanf("%d", &op) == 1)
	{
		if (op == 1)
		{
			int a, b, c, d, x;
			scanf("%d%d%d%d%d", &a, &b, &c, &d, &x);
			add(a, b, x);
			add(a, d + 1, -x);
			add(c + 1, b, -x);
			add(c + 1, d + 1, x);
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
