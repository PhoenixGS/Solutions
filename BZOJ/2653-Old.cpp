#include <cstdio>
#include <algorithm>

#define mid (l + r >> 1)

struct T
{
	int x, id;
};

int num;
int ch[900000][2];
int sum[900000], left[900000], right[900000];
int v[10];
int n, m;
int root[30000];
T x[30000];

bool comp(T x, T y)
{
	return x.x < y.x;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	left[k] = std::max(left[ch[k][0]], sum[ch[k][0]] + left[ch[k][1]]);
	right[k] = std::max(right[ch[k][1]], sum[ch[k][1]] + right[ch[k][0]]);
}

void build(int &k, int l, int r)
{
	num++;
	k = num;
	if (l == r)
	{
		left[k] = right[k] = sum[k] = 1;
		return;
	}
	build(ch[k][0], l, mid);
	build(ch[k][1], mid + 1, r);
	pushup(k);
}

void change(int &u, int v, int l, int r, int pos, int newvalue)
{
	num++;
	u = num;
	ch[u][0] = ch[v][0];
	ch[u][1] = ch[v][1];
	if (l == r)
	{
		left[u] = right[u] = sum[u] = newvalue;
		return;
	}
	if (pos <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, pos, newvalue);
	}
	if (pos > mid)
	{
		change(ch[u][1], ch[v][1], mid + 1, r, pos, newvalue);
	}
	pushup(u);
//	printf("LL%d %d %d %d %d\n", l, r, sum[u], left[u], right[u]);
}

int querysum(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	int ans = 0;
	if (L <= mid)
	{
		ans += querysum(ch[k][0], l, mid, L, R);
	}
	if (R > mid)
	{
		ans += querysum(ch[k][1], mid + 1, r, L, R);
	}
	return ans;
}

int queryleft(int k, int l, int r, int L, int R)
{
//	printf("V%d %d %d\n", l, r, left[k]);
	if (L <= l && r <= R)
	{
		return left[k];
	}
	if (L > mid)
	{
		return queryleft(ch[k][1], mid + 1, r, L, R);
	}
	if (R <= mid)
	{
		return queryleft(ch[k][0], l, mid, L, R);
	}
//	printf("BB%d %d %d %d\n", l, r, queryleft(ch[k][0], l, mid, L, R), sum[ch[k][0]] + queryleft(ch[k][1], mid + 1, r, L, R));
	return std::max(queryleft(ch[k][0], l, mid, L, R), querysum(ch[k][0], l, mid, L, R) + queryleft(ch[k][1], mid + 1, r, L, R));
}

int queryright(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return right[k];
	}
	if (L > mid)
	{
		return queryright(ch[k][1], mid + 1, r, L, R);
	}
	if (R <= mid)
	{
		return queryright(ch[k][0], l, mid, L, R);
	}
	return std::max(queryright(ch[k][1], mid + 1, r, L, R), querysum(ch[k][1], mid + 1, r, L, R) + queryright(ch[k][0], l, mid, L, R));
}

bool check(int x, int a, int b, int c, int d)
{
	int tmp = 0;
	if (c - b > 1)
	{
		tmp += querysum(root[x], 1, n, b + 1, c - 1);
	}
	tmp += queryright(root[x], 1, n, a, b);
	tmp += queryleft(root[x], 1, n, c, d);
//	printf("X%d %d %d %d\n", x, tmp, queryright(root[x], 1, n, a, b), queryleft(root[x], 1, n, c, d));
	return tmp >= 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i].x);
		x[i].id = i;
	}
	std::sort(x + 1, x + n + 1, comp);
	build(root[1], 1, n);
	for (int i = 2; i <= n; i++)
	{
		change(root[i], root[i - 1], 1, n, x[i - 1].id, -1);
//		printf("KK%d %d %d\n", i, x[i - 1].id, sum[root[i]]);
	}
	int pre = 0;
	scanf("%d", &m);
	while (m--)
	{
		for (int i = 1; i <= 4; i++)
		{
			scanf("%d", &v[i]);
			v[i] = (v[i] + pre) % n + 1;
		}
		std::sort(v + 1, v + 4 + 1);
//		printf("%d %d %d %d\n", v[1], v[2], v[3], v[4]);
		int l = 1;
		int r = n;
		while (l < r)
		{
			int midx = (l + r + 1) >> 1;
			if (check(midx, v[1], v[2], v[3], v[4]))
			{
				l = midx;
			}
			else
			{
				r = midx - 1;
			}
		}
		printf("%d\n", x[l].x);
		pre = x[l].x;
	}
	return 0;
}
