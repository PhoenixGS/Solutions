#include <cstdio>

int num;
int sum[10000000];
int ch[10000000][2];
int root[200000];
int n, m;
int x[200000];
long long ans;
int id[200000];
int cnt = 0;

int lowbit(int x)
{
	return x & -x;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int &k, int l, int r, int pos, int delta)
{
	if (! k)
	{
		num++;
		k = num;
	}
	if (l == r)
	{
		sum[k] += delta;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos, delta);
	}
	pushup(k);
}

void change(int x, int pos, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		change(root[i], 0, n + 1, pos, delta);
	}
}

int query(int k, int l, int r, int L, int R)
{
	if (! k)
	{
		return 0;
	}
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	int ans = 0;
	int mid = l + r >> 1;
	if (L <= mid)
	{
		ans += query(ch[k][0], l, mid, L, R);
	}
	if (R > mid)
	{
		ans += query(ch[k][1], mid + 1, r, L, R);
	}
	return ans;
}

int query(int x, int l, int r)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += query(root[i], 0, n + 1, l, r);
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		id[x[i]] = i;
		change(i, x[i], 1);
	}
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += query(i - 1, x[i] + 1, n);
	}
	while (m--)
	{
		printf("%lld\n", ans);
		int pos;
		scanf("%d", &pos);
		pos = id[pos];
		ans -= query(pos - 1, x[pos] + 1, n) + query(n, 1, x[pos] - 1) - query(pos - 1, 1, x[pos] - 1);
		change(pos, x[pos], -1);
	}
	return 0;
}
