#include <cstdio>

int root[500000];
int multi[30000000], ch[30000000][2];
int n, m;
const int M = 998244353;
int num;

int powmod(int x, int p)
{
	long long tmp = x;
	long long ans = 1;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * tmp % M;
		}
		tmp = tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int merge(int x, int y)
{
	return (((long long)x * y) % M + ((long long)1 - x + M) * ((long long)1 - y + M) % M) % M;
}

void change(int &k, int l, int r, int L, int R, int mul)
{
	if (! k)
	{
		num++;
		k = num;
		multi[k] = 1;
	}
	if (L <= l && r <= R)
	{
		multi[k] = merge(multi[k], mul);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid)
	{
		change(ch[k][0], l, mid, L, R, mul);
	}
	if (R > mid)
	{
		change(ch[k][1], mid + 1, r, L, R, mul);
	}
}

void change(int k, int l, int r, int L, int R, int ll, int rr, int mul)
{
	if (L <= l && r <= R)
	{
		change(root[k], 0, n + 1, ll, rr, mul);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, ll, rr, mul);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, ll, rr, mul);
	}
}

int query(int k, int l, int r, int pos)
{
	if (! k)
	{
		return 1;
	}
	if (l == r)
	{
		return multi[k];
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		return merge(multi[k], query(ch[k][0], l, mid, pos));
	}
	else
	{
		return merge(multi[k], query(ch[k][1], mid + 1, r, pos));
	}
}

int query(int k, int l, int r, int pos, int poss)
{
	if (l == r)
	{
		return query(root[k], 0, n + 1, poss);
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		return merge(query(root[k], 0, n + 1, poss), query(k << 1, l, mid, pos, poss));
	}
	else
	{
		return merge(query(root[k], 0, n + 1, poss), query(k << 1 | 1, mid + 1, r, pos, poss));
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int cas, l, r;
		scanf("%d%d%d", &cas, &l, &r);
		if (cas == 1)
		{
			int tmp = powmod(r - l + 1, M - 2);
			if (l > 1)
			{
				change(1, 0, n + 1, 1, l - 1, l, r, (1 - tmp + M) % M);
				//printf("%d %d %d %d %d\n", 1, l - 1, l, r, (1 - tmp + M) % M);
				change(1, 0, n + 1, 0, 0, 1, l - 1, 0);
				//printf("%d %d %d %d %d\n", 0, 0, 1, l - 1, 0);
			}
			if (r < n)
			{
				change(1, 0, n + 1, l, r, r + 1, n, (1 - tmp + M) % M);
				//printf("%d %d %d %d %d\n", l, r, r + 1, n, (1 - tmp + M) % M);
				change(1, 0, n + 1, 0, 0, r + 1, n, 0);
				//printf("%d %d %d %d %d\n", 0, 0, r + 1, n, 0);
			}
			change(1, 0, n + 1, l, r, l, r, (1 - 2 * tmp % M + M) % M);
			//printf("%d %d %d %d %d\n", l, r, l, r, (1 - 2 * tmp % M + M) % M);
			change(1, 0, n + 1, 0, 0, l, r, tmp);
			//printf("%d %d %d %d %d\n", 0, 0, l, r, tmp);
		}
		else
		{
			printf("%d\n", query(1, 0, n + 1, l - 1, r));
		}
	}
	return 0;
}
