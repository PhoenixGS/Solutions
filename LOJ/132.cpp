#include <cstdio>

const int _n = 1000000 + 10;
int n, q;
long long x[_n], s[_n], ss[_n];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
	{
		s[i] += delta;
		ss[i] += (long long)delta * x;
	}
}

long long query(int x)
{
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += s[i] * (x + 1) - ss[i];
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		add(i, x[i] - x[i - 1]);
	}
	while (q--)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			add(l, x);
			add(r + 1, -x);
		}
		else
		{
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(r) - query(l - 1));
		}
	}
	return 0;
}
