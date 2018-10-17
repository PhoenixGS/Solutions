#include <cstdio>
#include <algorithm>
#include <map>

int n, m;
int x[60000];
int last;
int kk[120000];
int LL, RR;
int sum[10000005];
int ch[10000005][2];
int root[300000];
std::map<int, int> map, rev;
int cas[60000], l[60000], r[60000], k[60000], pos[60000];
int num;
int rootss;
int roots[100];

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void insert(int &k, int l, int r, int pos, int delta)
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
		insert(ch[k][0], l, mid, pos, delta);
	}
	else
	{
		insert(ch[k][1], mid + 1, r, pos, delta);
	}
	pushup(k);
}

void build(int k, int l, int r)
{
	for (int i = l; i <= r; i++)
	{
		insert(root[k], LL, RR, x[i], 1);
	}
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}

int query_sum(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid && ch[k][0])
	{
		ans += query_sum(ch[k][0], l, mid, L, R);
	}
	if (R > mid && ch[k][1])
	{
		ans += query_sum(ch[k][1], mid + 1, r, L, R);
	}
	return ans;
}

int query_sum(int k, int l, int r, int L, int R, int key)
{
	if (L <= l && r <= R)
	{
		return query_sum(root[k], LL, RR, 1, key);
	}
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid)
	{
		ans += query_sum(k << 1, l, mid, L, R, key);
	}
	if (R > mid)
	{
		ans += query_sum(k << 1 | 1, mid + 1, r, L, R, key);
	}
	return ans;
}

void init(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		rootss++;
		roots[rootss] = root[k];
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid)
	{
		init(k << 1, l, mid, L, R);
	}
	if (R > mid)
	{
		init(k << 1 | 1, mid + 1, r, L, R);
	}
}

int binary_search(int L, int R, int rank)
{
	rootss = 0;
	init(1, 1, n, L, R);
	int l = LL;
	int r = RR;
	while (l < r)
	{
		int mid = l + r >> 1;
		int ss = 0;
		for (int i = 1; i <= rootss; i++)
		{
			ss += sum[ch[roots[i]][0]];
		}
		if (rank <= ss)
		{
			for (int i = 1; i <= rootss; i++)
			{
				roots[i] = ch[roots[i]][0];
			}
			r = mid;
		}
		else
		{
			rank -= ss;
			for (int i = 1; i <= rootss; i++)
			{
				roots[i] = ch[roots[i]][1];
			}
			l = mid + 1;
		}
	}
	return l;
}

void update(int k, int l, int r, int pos, int key, int delta)
{
	insert(root[k], LL, RR, key, delta);
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		update(k << 1, l, mid, pos, key, delta);
	}
	else
	{
		update(k << 1 | 1, mid + 1, r, pos, key, delta);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	last = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		last++;
		kk[last] = x[i];
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &cas[i]);
		if (cas[i] == 1)
		{
			scanf("%d%d%d", &l[i], &r[i], &k[i]);
			last++;
			kk[last] = k[i];
		}
		if (cas[i] == 2)
		{
			scanf("%d%d%d", &l[i], &r[i], &k[i]);
		}
		if (cas[i] == 3)
		{
			scanf("%d%d", &pos[i], &k[i]);
			last++;
			kk[last] = k[i];
		}
		if (cas[i] == 4)
		{
			scanf("%d%d%d", &l[i], &r[i], &k[i]);
			last++;
			kk[last] = k[i];
		}
		if (cas[i] == 5)
		{
			scanf("%d%d%d", &l[i], &r[i], &k[i]);
			last++;
			kk[last] = k[i];
		}
	}
	std::sort(kk + 1, kk + last + 1);
	last = std::unique(kk + 1, kk + last + 1) - kk - 1;
	LL = 0;
	RR = last + 1;
	for (int i = 1; i <= last; i++)
	{
		map[kk[i]] = i;
		rev[i] = kk[i];
	}
	for (int i = 1; i <= n; i++)
	{
		x[i] = map[x[i]];
	}
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		if (cas[i] == 1)
		{
			printf("%d\n", query_sum(1, 1, n, l[i], r[i], map[k[i]] - 1) + 1);
		}
		if (cas[i] == 2)
		{
			printf("%d\n", rev[binary_search(l[i], r[i], k[i])]);
		}
		if (cas[i] == 3)
		{
			update(1, 1, n, pos[i], x[pos[i]], -1);
			update(1, 1, n, pos[i], map[k[i]], 1);
			x[pos[i]] = map[k[i]];
		}
		if (cas[i] == 4)
		{
			printf("%d\n", rev[binary_search(l[i], r[i], query_sum(1, 1, n, l[i], r[i], map[k[i]] - 1))]);
		}
		if (cas[i] == 5)
		{
			printf("%d\n", rev[binary_search(l[i], r[i], query_sum(1, 1, n, l[i], r[i], map[k[i]]) + 1)]);
		}
	}
	return 0;
}
