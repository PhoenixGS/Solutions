#include <cstdio>

const int _n = 1000000 + 10;
int n, q;
long long tree[_n];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
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
		int x;
		scanf("%d", &x);
		add(i, x);
	}
	while (q--)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int pos, delta;
			scanf("%d%d", &pos, &delta);
			add(pos, delta);
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
