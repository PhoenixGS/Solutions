#include <cstdio>
#include <algorithm>

struct T
{
	int x, query, pos, cas;
};

int edgenum;
int vet[60000], nextx[60000], head[60000];
int fa[60000], size[60000];
int sz;
int pos[60000], top[60000];
int sum[250000], tag[250000];
int n, m;
int last;
T ques[120000];
int ans[120000];

bool comp(T x, T y)
{
	return x.x < y.x;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs1(int u)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		dfs1(v);
		size[u] += size[v];
	}
}

void dfs2(int u, int chain)
{
	int k = 0;
	sz++;
	pos[u] = sz;
	top[u] = chain;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (size[v] > size[k])
		{
			k = v;
		}
	}
	if (k)
	{
		dfs2(k, chain);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != k)
		{
			dfs2(v, v);
		}
	}
}

void pushdown(int k, int l, int r)
{
	if (tag[k])
	{
		int mid = l + r >> 1;
		sum[k << 1] += (mid - l + 1) * tag[k];
		tag[k << 1] += tag[k];
		sum[k << 1 | 1] += (r - mid) * tag[k];
		tag[k << 1 | 1] += tag[k];
		tag[k] = 0;
	}
}

void pushup(int k)
{
	sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void change(int k, int l, int r, int L, int R, int delta)
{
	if (L <= l && r <= R)
	{
		sum[k] += (r - l + 1) * delta;
		tag[k] += delta;
		return;
	}
	pushdown(k, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, delta);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, delta);
	}
	pushup(k);
}

int query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return sum[k];
	}
	pushdown(k, l, r);
	int ans = 0;
	int mid = l + r >> 1;
	if (L <= mid)
	{
		ans += query(k << 1, l, mid, L, R);
	}
	if (R > mid)
	{
		ans += query(k << 1 | 1, mid + 1, r, L, R);
	}
	return ans;
}

void update(int x)
{
	while (x)
	{
		change(1, 1, sz, pos[top[x]], pos[x], 1);
		x = fa[top[x]];
	}
}

int solve(int x)
{
	int ans = 0;
	while (x)
	{
		ans += query(1, 1, sz, pos[top[x]], pos[x]);
		x = fa[top[x]];
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++)
	{
		int father;
		scanf("%d", &father);
		father++;
		fa[i] = father;
		add(father, i);
	}
	dfs1(1);
	dfs2(1, 1);
	last = 0;
	for (int i = 1; i <= m; i++)
	{
		int l, r, z;
		scanf("%d%d%d", &l, &r, &z);
		l++;
		r++;
		z++;
		last++;
		ques[last].x = l - 1;
		ques[last].query = z;
		ques[last].pos = i;
		ques[last].cas = -1;
		last++;
		ques[last].x = r;
		ques[last].query = z;
		ques[last].pos = i;
		ques[last].cas = 1;
	}
	std::sort(ques + 1, ques + last + 1, comp);
	int now = 1;
	while (now <= last && ques[now].x == 0)
	{
		now++;
	}
	for (; now <= last; now++)
	{
		for (int i = ques[now - 1].x + 1; i <= ques[now].x; i++)
		{
			update(i);
		}
		ans[ques[now].pos] += ques[now].cas * solve(ques[now].query);
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i] % 201314);
	}
	return 0;
}
