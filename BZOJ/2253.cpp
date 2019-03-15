#include <cstdio>
#include <algorithm>

struct node
{
	int x, y, z, pos;
};

const int INF = 1000000000;
const int _n = 50000 + 10;
int a, p, n;
int times;
int bit[3 * _n], tim[3 * _n];
node x[_n];
int last;
int v[3 * _n];
int f[_n];
int ans;

inline int abss(int x)
{
	return x > 0 ? x : -x;
}

bool compx(node x, node y)
{
	return x.x < y.x;
}

bool compy(node x, node y)
{
	return x.y < y.y;
}

inline int lowbit(int x)
{
	return x & -x;
}

void change(int x, int newvalue)
{
	for (int i = x; i <= last; i += lowbit(i))
	{
		if (tim[i] != times)
		{
			tim[i] = times;
			bit[i] = 0;
		}
		bit[i] = std::max(bit[i], newvalue);
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		if (tim[i] != times)
		{
			tim[i] = times;
			bit[i] = 0;
		}
		ans = std::max(ans, bit[i]);
	}
	return ans;
}

void solve(int l, int r)
{
	int mid = (l + r) >> 1;
	int xx = INF;
	for (int i = l; i < r; i++)
	{
		if (x[i].x != x[i + 1].x)
		{
			if (abss(i - mid) < abss(xx - mid))
			{
				xx = i;
			}
		}
	}
	if (xx == INF)
	{
		for (int i = l; i <= r; i++)
		{
			f[x[i].pos] = std::max(f[x[i].pos], 1);
			ans = std::max(ans, f[x[i].pos]);
		}
		std::sort(x + l, x + r + 1, compy);
		return;
	}
	mid = xx;
	solve(l, mid);
	std::sort(x + l, x + mid + 1, compy);
	std::sort(x + mid + 1, x + r + 1, compy);
	times++;
	int now = l;
	for (int i = mid + 1; i <= r; i++)
	{
		while (now <= mid && x[now].y < x[i].y)
		{
			change(x[now].z, f[x[now].pos]);
			now++;
		}
		f[x[i].pos] = std::max(f[x[i].pos], query(x[i].z - 1) + 1);
	}
	std::sort(x + mid + 1, x + r + 1, compx);
	solve(mid + 1, r);
	std::sort(x + l, x + r + 1, compy);
}

int main()
{
#ifdef debug
	freopen("2253.in", "r", stdin);
#endif
	scanf("%d%d%d", &a, &p, &n);
	int tmp = 1;
	for (int i = 1; i <= n; i++)
	{
		tmp = (long long)tmp * a % p;
		x[i].x = tmp;
		last++;
		v[last] = tmp;
		tmp = (long long)tmp * a % p;
		last++;
		v[last] = tmp;
		x[i].y = tmp;
		tmp = (long long)tmp * a % p;
		last++;
		v[last] = tmp;
		x[i].z = tmp;
		x[i].pos = i;
	}
	std::sort(v + 1, v + last + 1);
	last = std::unique(v + 1, v + last + 1) - (v + 1);
	for (int i = 1; i <= n; i++)
	{
		x[i].x = std::lower_bound(v + 1, v + last + 1, x[i].x) - v;
		x[i].y = std::lower_bound(v + 1, v + last + 1, x[i].y) - v;
		x[i].z = std::lower_bound(v + 1, v + last + 1, x[i].z) - v;
		if (x[i].x > x[i].y)
		{
			std::swap(x[i].x, x[i].y);
		}
		if (x[i].x > x[i].z)
		{
			std::swap(x[i].x, x[i].z);
		}
		if (x[i].y > x[i].z)
		{
			std::swap(x[i].y, x[i].z);
		}
	}
	std::sort(x + 1, x + n + 1, compx);
	solve(1, n);
#ifdef debug
	for (int i = 1; i <= n; i++)
	{
		printf("??%d %d %d %d %d\n", x[i].x, x[i].y, x[i].z, x[i].pos, f[x[i].pos]);
	}
#endif
	printf("%d\n", ans);
	return 0;
}
