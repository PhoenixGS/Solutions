#include <cstdio>

int n, m;
int x[40000];
int pre[2000000];
int sum[2000000], ch[2000000][2];
int root[40000];
int num;

void change(int u, int &v, int l, int r, int pos, int delta)
{
	num++;
	v = num;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	sum[v] = sum[u] + delta;
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, pos, delta);
	}
}

int query(int k, int l, int r, int L, int R)
{
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

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		if (pre[x[i]] == 0)
		{
			change(root[i - 1], root[i], 1, n, i, 1);
			pre[x[i]] = i;
		}
		else
		{
			change(root[i - 1], root[i], 1, n, pre[x[i]], -1);
			change(root[i], root[i], 1, n, i, 1);
			pre[x[i]] = i;
		}
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(root[r], 1, n, l, n));
	}
	return 0;
}
