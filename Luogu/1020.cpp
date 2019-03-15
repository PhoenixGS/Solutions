#include <cstdio>
#include <algorithm>

const int _n = 100000 + 10;
int n;
int x[_n];
int f[_n];
int tree[50000 + 10];
int ans;

inline int lowbit(int x)
{
	return x & -x;
}

void change(int x, int newvalue)
{
	for (int i = x; i <= 50001; i += lowbit(i))
	{
		tree[i] = std::max(tree[i], newvalue);
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans = std::max(ans, tree[i]);
	}
	return ans;
}

int main()
{
#ifdef debug
	freopen("1020.in", "r", stdin);
#endif
	n = 0;
	while (scanf("%d", &x[n + 1]) != EOF)
	{
		n++;
	}

	for (int i = 1; i <= n; i++)
	{
		x[i] = 50001 - x[i];
	}
	for (int i = 1; i <= 50001; i++)
	{
		tree[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		f[i] = query(x[i]) + 1;
		change(x[i], f[i]);
	}
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = std::max(ans, f[i]);
	}
	printf("%d\n", ans);

	for (int i = 1; i <= n; i++)
	{
		x[i] = 50001 - x[i];
	}
	for (int i = 1; i <= 50001; i++)
	{
		tree[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		f[i] = query(x[i] - 1) + 1;
		change(x[i], f[i]);
	}
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = std::max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
