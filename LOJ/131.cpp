#include <cstdio>

const int _n = 1000000 + 10;
int n, q;
int x[_n];
long long tree[_n];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
	{
		tree[i] += delta;
	}
}

long long query(int x)
{
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += tree[i];
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
			int pos;
			scanf("%d", &pos);
			printf("%lld\n", query(pos));
		}
	}
	return 0;
}
