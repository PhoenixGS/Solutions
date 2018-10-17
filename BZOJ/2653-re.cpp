#include <cstdio>
#include <algorithm>

struct T
{
	int x, id;
};

int num;
int left[500000], right[500000], sum[500000];
int ch[500000][2];
int root[500000];
int v[10];
int n, m;
int pred;
T x[40000];

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
	int mid = (l + r) >> 1;
	build(ch[k][0], l, mid);
	build(ch[k][1], mid + 1, r);
	pushup(k);
}

void change(int u, int &v, int l, int r, int key, int newvalue)
{
	num++;
	v = num;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (l == r)
	{
		left[v] = right[v] = sum[v] = newvalue;
		return;
	}
	int mid = (l + r) >> 1;
	if (key <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, key, newvalue);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, key, newvalue);
	}
	pushup(v);
}

int querysum(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	int ans = 0;
	int mid = (l + r) >> 1;
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
	if (L <= l && r <= R)
	{
		return left[k];
	}
	int mid = (l + r) >> 1;
	if (L > mid)
	{
		return queryleft(ch[k][1], mid + 1, r, L, R);
	}
	if (R <= mid)
	{
		return queryleft(ch[k][0], l, mid, L, R);
	}
	return std::max(queryleft(ch[k][0], l, mid, L, R), querysum(ch[k][0], l, mid, L, R) + queryleft(ch[k][1], mid + 1, r, L, R));
}

int queryright(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return right[k];
	}
	int mid = (l + r) >> 1;
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

bool check(int k, int a, int b, int c, int d)
{
	int tmp = 0;
	if (c - b >= 2)
	{
		tmp += querysum(root[k], 1, n, b + 1, c - 1);
	}
	tmp += queryright(root[k], 1, n, a, b);
	tmp += queryleft(root[k], 1, n, c, d);
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
		change(root[i - 1], root[i], 1, n, x[i - 1].id, -1);
	}
	scanf("%d", &m);
	pred = 0;
	while (m--)
	{
		scanf("%d%d%d%d", &v[1], &v[2], &v[3], &v[4]);
		for (int i = 1; i <= 4; i++)
		{
			v[i] = (v[i] + pred) % n + 1;
		}
		std::sort(v + 1, v + 4 + 1);
		int l = 1;
		int r = n;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (check(mid, v[1], v[2], v[3], v[4]))
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		printf("%d\n", x[l].x);
		pred = x[l].x;
	}
	return 0;
}
