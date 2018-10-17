#include <cstdio>
#include <algorithm>

int n, m;
int num;
long long key[400000];
int left[400000], right[400000];
long long tag1[400000];
long long tag2[400000];
int dis[400000];
int id[400000];
int deep[400000];
int ans[400000];
int cnt[400000];
int root[400000];
long long h[400000];
int f[400000];
long long a[400000];
long long v[400000];
long long s[400000];
int c[400000];

void add(long long kkey, int kk)
{
	num++;
	key[num] = kkey;
	left[num] =
	right[num] = 0;
	tag1[num] = 0;
	tag2[num] = 1;
	dis[num] = 0;
	id[num] = kk;
}

void pushdown(int x)
{
	key[x] = key[x] * tag2[x] + tag1[x];
	if (left[x])
	{
		int l = left[x];
		tag2[l] = tag2[l] * tag2[x];
		tag1[l] = tag1[l] * tag2[x] + tag1[x];
	}
	if (right[x])
	{
		int r = right[x];
		tag2[r] = tag2[r] * tag2[x];
		tag1[r] = tag1[r] * tag2[x] + tag1[x];
	}
	tag1[x] = 0;
	tag2[x] = 1;
}

int merge(int x, int y)
{
	if (x == 0)
	{
		return y;
	}
	if (y == 0)
	{
		return x;
	}
	pushdown(x);
	pushdown(y);
	if (key[x] * tag2[x] + tag1[x] > key[y] * tag2[y] + tag1[x])
	{
		std::swap(x, y);
	}
	right[x] = merge(right[x], y);
	if (dis[left[x]] < dis[right[x]])
	{
		std::swap(left[x], right[x]);
	}
	dis[x] = dis[right[x]] + 1;
	return x;
}

int del(int x)
{
	pushdown(x);
	return merge(left[x], right[x]);
}

void update(int k, long long t1, long long t2)
{
	tag2[k] = tag2[k] * t2;
	tag1[k] = tag1[k] * t2 + t1;
}

int main()
{
	num = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &h[i]);
		root[i] = 0;
	}
	for (int i = 2; i <= n; i++)
	{
		scanf("%d%lld%lld", &f[i], &a[i], &v[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%lld%d", &s[i], &c[i]);
		if (s[i] >= h[c[i]])
		{
			add(s[i], i);
			root[c[i]] = merge(root[c[i]], num);
		}
		else
		{
			ans[c[i]]++;
			cnt[i] = 0;
		}
	}
	for (int i = 2; i <= n; i++)
	{
		if (a[i] == 0)
		{
			update(root[i], v[i], 1);
		}
		else
		{
			update(root[i], 0, v[i]);
		}
		//printf("Y%d %d %lld %lld\n", i, root[i], tag1[root[i]], tag2[root[i]]);
	}
	deep[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		deep[i] = deep[f[i]] + 1;
	}
	for (int i = n; i >= 2; i--)
	{
		while (root[i] != 0 && key[root[i]] * tag2[root[i]] + tag1[root[i]] < h[f[i]])
		{
			//printf("%d %lld %lld %lld %lld\n", id[root[i]], key[root[i]] * tag2[root[i]] + tag1[root[i]], key[root[i]], tag1[root[i]], tag2[root[i]]);
			int k = id[root[i]];
			cnt[k] = deep[c[k]] - deep[f[i]];
			root[i] = del(root[i]);
			ans[f[i]]++;
		}
		if (a[f[i]] == 0)
		{
			update(root[i], v[f[i]], 1);
		}
		else
		{
			update(root[i], 0, v[f[i]]);
		}
		root[f[i]] = merge(root[f[i]], root[i]);
	}
	while (root[1] != 0)
	{
		int k = id[root[1]];
		cnt[k] = deep[c[k]] - deep[1] + 1;
		root[1] = del(root[1]);
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", ans[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", cnt[i]);
	}
	return 0;
}
