#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 1000000 + 10;
int n, m, root;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int times;
int in[_n], out[_n];
long long tree[4 * _n], tag[4 * _n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void pushdown(int k, int l, int r)
{
	if (tag[k])
	{
		int mid = (l + r) >> 1;
		tag[k << 1] += tag[k];
		tree[k << 1] += tag[k] * (mid - l + 1);
		tag[k << 1 | 1] += tag[k];
		tree[k << 1 | 1] += tag[k] * (r - mid);
		tag[k] = 0;
	}
}

void pushup(int k)
{
	tree[k] = tree[k << 1] + tree[k << 1 | 1];
}

void change(int k, int l, int r, int L, int R, int delta)
{
	if (L <= l && r <= R)
	{
		tag[k] += delta;
		tree[k] += (long long)delta * (r - l + 1);
		return;
	}
	pushdown(k, l, r);
	int mid = (l + r) >> 1;
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

long long query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
	pushdown(k, l, r);
	int mid = (l + r) >> 1;
	long long ans = 0;
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

void dfs(int u, int father)
{
	times++;
	in[u] = times;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	out[u] = times;
}

int main()
{
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(root, 0);
	for (int i = 1; i <= n; i++)
	{
		change(1, 1, n, in[i], in[i], x[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		int op = read();
		if (op == 1)
		{
			int pos = read();
			int delta = read();
			change(1, 1, n, in[pos], out[pos], delta);
		}
		else
		{
			int pos = read();
			printf("%lld\n", query(1, 1, n, in[pos], out[pos]));
		}
	}
	return 0;
}

