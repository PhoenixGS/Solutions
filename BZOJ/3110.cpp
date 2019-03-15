#include <cstdio>
#include <cstring>
#include <algorithm>

struct node
{
	int cas, l, r, pos;
	long long c;
};

const int _n = 50000 + 10, _m = 50000 + 10;
int n, m;
node x[_m], t[_m];
long long bit0[_m], bit1[_m];
int belong[_m];
int last;
long long v[_m];
int ans[_m];

inline int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
	{
		bit0[i] += delta;
		bit1[i] += delta * x;
	}
}

long long query(int x)
{
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += (long long)(x + 1) * bit0[i] - bit1[i];
	}
	return ans;
}

void solve(int L, int R, int l, int r)
{
	if (L > R)
	{
		return;
	}
	if (l == r)
	{
		for (int i = L; i <= R; i++)
		{
			if (x[i].cas == 2)
			{
				ans[x[i].pos] = l;
			}
		}
		return;
	}
	int mid = (l + r) >> 1;
	for (int i = L; i <= R; i++)
	{
		if (x[i].cas == 1)
		{
			if (x[i].c > mid)
			{
				add(x[i].l, 1);
				add(x[i].r + 1, -1);
				belong[i] = 1;
			}
			else
			{
				belong[i] = 0;
			}
		}
		else
		{
			if (query(x[i].r) - query(x[i].l - 1) > x[i].c - 1)
			{
				belong[i] = 1;
			}
			else
			{
				x[i].c -= query(x[i].r) - query(x[i].l - 1);
				belong[i] = 0;
			}
		}
	}
	for (int i = L; i <= R; i++)
	{
		if (x[i].cas == 1)
		{
			if (x[i].c > mid)
			{
				add(x[i].l, -1);
				add(x[i].r + 1, 1);
			}
		}
	}
	int now = L - 1;
	for (int i = L; i <= R; i++)
	{
		if (belong[i] == 0)
		{
			now++;
			t[now] = x[i];
		}
	}
	int M = now;
	for (int i = L; i <= R; i++)
	{
		if (belong[i] == 1)
		{
			now++;
			t[now] = x[i];
		}
	}
	for (int i = L; i <= R; i++)
	{
		x[i] = t[i];
	}
	solve(L, M, l, mid);
	solve(M + 1, R, mid + 1, r);
}

int main()
{
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%lld", &x[i].cas, &x[i].l, &x[i].r, &x[i].c);
		x[i].pos = i;
		if (x[i].cas == 1)
		{
			last++;
			v[last] = x[i].c;
		}
	}
	std::sort(v + 1, v + last + 1);
	last = std::unique(v + 1, v + last + 1) - v - 1;
	for (int i = 1; i <= m; i++)
	{
		if (x[i].cas == 1)
		{
			x[i].c = std::lower_bound(v + 1, v + last + 1, x[i].c) - v;
		}
	}
	memset(ans, -1, sizeof(ans));
	solve(1, m, 1, last);
	for (int i = 1; i <= m; i++)
	{
		if (ans[i] != -1)
		{
			printf("%lld\n", v[ans[i]]);
		}
	}
	return 0;
}
