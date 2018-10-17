#include <cstdio>

#define root ch[0][1]

int n, m;
int times;
int in[200000], out[200000];
int v[300000], ff[300000];
int fa[300000], ch[300000][2];
int key[300000], sum[300000], kkk[300000], fff[300000], tag[300000];
int top;
int stack[300000];
int edgenum;
int vet[400000];
int nextx[400000];
int head[200000];
int x[200000];
char st[20];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	times++;
	in[u] = times;
	v[times] = x[u];
	ff[times] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	times++;
	out[u] = times;
	v[times] = -x[u];
	ff[times] = -1;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]] + key[k];
	fff[k] = fff[ch[k][0]] + fff[ch[k][1]] + kkk[k];
}

void pushdown(int k)
{
	if (tag[k])
	{
		if (ch[k][0])
		{
			sum[ch[k][0]] += fff[ch[k][0]] * tag[k];
			tag[ch[k][0]] += tag[k];
		}
		if (ch[k][1])
		{
			sum[ch[k][1]] += fff[ch[k][1]] * tag[k];
			tag[ch[k][1]] += tag[k];
		}
		tag[k] = 0;
	}
}

void build(int &k, int l, int r, int father)
{
	if (l > r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	k = mid;
	fa[k] = father;
	key[k] = v[mid];
	sum[k] = v[mid];
	kkk[k] = ff[mid];
	fff[k] = ff[mid];
	tag[k] = 0;
	build(ch[k][0], l, mid - 1, k);
	build(ch[k][1], mid + 1, r, k);
	pushup(k);
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int w = ch[y][1] == x;
	ch[z][ch[z][1] == y] = x;
	fa[x] = z;
	ch[y][w] = ch[x][w ^ 1];
	fa[ch[x][w ^ 1]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

void splay(int x, int &k)
{
	top++;
	stack[top] = x;
	for (int i = x; i != k; i = fa[i])
	{
		top++;
		stack[top] = fa[i];
	}
	while (top)
	{
		pushdown(stack[top]);
		top--;
	}
	while (x != k)
	{
		int y = fa[x];
		int z = fa[y];
		if (y != k)
		{
			if ((ch[z][1] == y) ^ (ch[y][1] == x))
			{
				rotate(x);
			}
			else
			{
				rotate(y);
			}
		}
		rotate(x);
	}
}

int split(int l, int r)
{
	printf("X1 %d\n", sum[root]);
	splay(l - 1, root);
	printf("X2 %d\n", sum[root]);
	splay(r + 1, ch[root][1]);
	printf("X3 %d\n", sum[root]);
	pushup(root);
	return ch[ch[root][1]][0];
}

int findlast(int x)
{
	return ch[x][1] ? findlast(ch[x][1]) : x;
}

int query(int l, int r)
{
	int tmp = split(l, r);
	return sum[tmp];
}

int del(int l, int r)
{
	printf("VB%d\n", sum[root]);
	int tmp = split(l, r);
	printf("VB%d %d\n", sum[root], fff[root]);
	fa[ch[ch[root][1]][0]] = 0;
	ch[ch[root][1]][0] = 0;
	pushup(ch[root][1]);
	pushup(root);
	return tmp;
}

void paste(int x, int y)
{
	printf("B%d %d\n", x, y);
	printf("BB%d\n", sum[root]);
	splay(x, root);
	printf("BB%d\n", sum[root]);
	int tmp = ch[x][1];
	ch[x][1] = y;
	fa[y] = x;
	pushup(x);
	int kk = findlast(y);
	splay(kk, root);
	ch[kk][1] = tmp;
	fa[tmp] = kk;
	pushup(kk);
}

void change(int l, int r, int delta)
{
	int tmp = split(l, r);
	sum[tmp] += fff[tmp] * delta;
	tag[tmp] += delta;
	printf("LLL%d %d %d %d %d\n", l, r, root, tmp, sum[root]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(x, i);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	times++;
	dfs(1, 0);
	times++;
	for (int i = 1; i <= n; i++)
	{
		printf("V%d %d %d\n", i, in[i], out[i]);
	}
	build(root, 1, times, 0);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		printf("VVV%d %d\n", sum[root], fff[root]);
		scanf("%s", st + 1);
		if (st[1] == 'Q')
		{
			int pos;
			scanf("%d", &pos);
			printf("%d\n", query(2, in[pos]));
			printf("NNN%d\n", sum[root]);
		}
		if (st[1] == 'C')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("XX%d\n", sum[root]);
			int tmp = del(in[x], out[x]);
			printf("YY%d\n", sum[root]);
			printf("GGG%d\n", ch[tmp][0]);
			paste(in[y], tmp);
		}
		if (st[1] == 'F')
		{
			int x, delta;
			scanf("%d%d", &x, &delta);
			change(in[x], out[x], delta);
		}
	}
	return 0;
}

