#include <cstdio>
#include <algorithm>

struct T
{
	int l, x, r, id;
};

int n, m;
int f[200000];
T x[200000];
int bit[200000];
int ans;

bool comp1(T x, T y)
{
	return x.r <= y.r;
}

bool comp2(T x, T y)
{
	return x.x <= y.x;
}

bool comp3(T x, T y)
{
	return x.id <= y.id;
}

int lowbit(int x)
{
	return x & -x;
}

void update(int x, int key)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		bit[i] = std::max(bit[i], key);
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans = std::max(ans, bit[i]);
	}
	return ans;
}

void del(int x)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		bit[i] = 0;
	}
}

void solve(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	std::sort(x + l, x + mid + 1, comp1);
	std::sort(x + mid + 1, x + r + 1, comp2);
	int now = l;
	for (int i = mid + 1; i <= r; i++)
	{
		while (now <= mid && x[now].r <= x[i].x)
		{
			update(x[now].x, f[x[now].id]);
			now++;
		}
		f[x[i].id] = std::max(f[x[i].id], query(x[i].l) + 1);
	}
	for (int i = l; i <= mid; i++)
	{
		del(x[i].x);
	}
	std::sort(x + l, x + r + 1, comp3);
	solve(mid + 1, r);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i].x);
		x[i].l = x[i].r = x[i].x;
		x[i].id = i;
	}
	for (int i = 1; i <= m; i++)
	{
		int idx, k;
		scanf("%d%d", &idx, &k);
		x[idx].l = std::min(x[idx].l, k);
		x[idx].r = std::max(x[idx].r, k);
	}
	f[0] = 0;
	x[0].l = x[0].x = x[0].r = 1;
	solve(0, n);
	ans = 0;
	for (int i = 0; i <= n; i++)
	{
		ans = std::max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
