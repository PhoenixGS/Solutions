#include <cstdio>
#include <cstring>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct node
{
	int f, g, h, s;

	node(int _f = 0, int _g = 0, int _h = 0, int _s = 0)
	{
		f = _f, g = _g, h = _h, s = _s;
	}
};

const int M = 20130427;
const int _n = 100000 + 10;
int B;
int n;
int v[_n];
node f[_n];
int ans;

node dfs(int pos, int limit, int lead)
{
	if (pos == 0)
	{
		node t(1, 0, 0, 0);
		return t;
	}
	if (! limit && ! lead && f[pos].f)
	{
		return f[pos];
	}
	int top = limit ? v[pos] : (B - 1);
	node ans(0, 0, 0, 0);
	node tmp = dfs(pos - 1, limit, lead && top == 0);
	(ans.f += tmp.f) %= M;
	(ans.g += ((long long)tmp.g * B % M + tmp.f) % M) %= M;
	(ans.h += (tmp.h + (long long)top * ((long long)tmp.g * B % M + tmp.f) % M) % M) %= M;
	(ans.s += (tmp.s + (! (lead && top == 0)) * (tmp.h + (long long)top * ((long long)tmp.g * B % M + tmp.f) % M) % M) % M) %= M;
	if (top > 1)
	{
		node tmp = dfs(pos - 1, 0, 0);
		(ans.f += (long long)(top - 1) * tmp.f % M) %= M;
		(ans.g += ((long long)(top - 1) * tmp.g % M * B % M + (long long)(top - 1) * tmp.f % M) % M) %= M;
		(ans.h += ((long long)(top - 1) * tmp.h % M + (long long)top * (top - 1) / 2 % M * ((long long)tmp.g * B % M + tmp.f) % M) % M) %= M;
		(ans.s += (((long long)(top - 1) * tmp.s % M + (long long)(top - 1) * tmp.h % M) % M + (long long)top * (top - 1) / 2 % M * ((long long)tmp.g * B % M + tmp.f) % M) % M) %= M;
	}
	if (top != 0)
	{
		node tmp = dfs(pos - 1, limit && 0 == top, lead && 0 == 0);
		(ans.f += tmp.f) %= M;
		(ans.g += ((long long)tmp.g * B % M + tmp.f) % M) %= M;
		(ans.h += (tmp.h + (long long)0 * ((long long)tmp.g * B % M + tmp.f) % M) % M) %= M;
		(ans.s += (tmp.s + (! (lead && 0 == 0)) * (tmp.h + (long long)0 * ((long long)tmp.g * B % M + tmp.f) % M) % M) % M) %= M;
	}
	if (! limit && ! lead)
	{
		f[pos] = ans;
	}
	return ans;
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
	if (! (n == 1 && v[1] == 0))
	{
		v[1]--;
		for (int i = 1; i <= n && v[i] < 0; i++)
		{
			v[i] += B;
			v[i + 1]--;
		}
		(ans = ans - solve()) %= M;
	}
	n = read();
	for (int i = n; i >= 1; i--)
	{
		v[i] = read();
	}
	(ans = ans + solve()) %= M;
	ans = (ans % M + M) % M;
	printf("%d\n", ans);
	return 0;
}