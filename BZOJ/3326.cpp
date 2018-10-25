#include <cstdio>

struct node
{
	int f, g, s;

	node(int _f = 0, int _g = 0, int _s = 0)
	{
		f = _f, g = _g, s = _s;
	}
};

node dfs(int pos, int limit, int lead)
{
	if (pos = 0)
	{
		return (node)(1, 0, 0);
	}
	int top = limit ? v[pos] : 9;
	node ans(0, 0, 0);
	for (int i = 0; i <= top; i++)
	{
		node tmp = dfs(pos - 1, limit && i == top, lead && i == 0);
		(ans.f += tmp.f) %= M;
		(ans.g += (tmp.f + (long long)i * tmp.f % M) % M) %= M;
		(ans.s += )
	}
}

int solve()
{
	return dfs(n, 1, 1).s;
}

int main()
{
	B = read();
	ans = 0;
	n = read();
	for (int i = n; i >= 1; i--)
	{
		v[i] = read();
	}
	ans = solve();
	n = read();
	for (int i = n; i >= 1; i--)
	{
		v[i] = read();
	}
	v[1]--;
	for (int i = 1; i <= n && v[i] < 0; i++)
	{
		v[i] += 10;
		v[i + 1]--;
	}
	ans = ans - solve();
	ans = (ans % M + M) % M;
	printf("%d\n", ans);
	return 0;
}