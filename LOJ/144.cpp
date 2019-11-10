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
long long tree[4 * _n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void change(int k, int l, int r, int pos, int delta)
{
	if (l == r)
	{
		tree[k] += delta;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(k << 1, l, mid, pos, delta);
	}
	else
	{
		change(k << 1 | 1, mid + 1, r, pos, delta);
	}
	tree[k] = tree[k << 1] + tree[k << 1 | 1];
}

long long query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
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
		change(1, 1, n, in[i], x[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		int op = read();
		if (op == 1)
		{
			int pos = read();
			int delta = read();
			change(1, 1, n, in[pos], delta);
		}
		else
		{
			int pos = read();
			printf("%lld\n", query(1, 1, n, in[pos], out[pos]));
		}
	}
	return 0;
}
