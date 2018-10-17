#include <cstdio>

#define root ch[0][1]

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int n, m;
int edgenum;
int vet[300000], nextx[300000], head[300000];
int times;
int in[300000], out[300000];
long long key[300000], sum[300000], tag[300000];
int flag[300000], fff[300000];
int fa[300000], ch[300000][2];
int top;
int stack[300000];
int x[300000];
char cas[20];

inline void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u)
{
	times++;
	in[u] = times;
	key[times] = x[u];
	flag[times] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		dfs(v);
	}
	times++;
	out[u] = times;
	key[times] = -x[u];
	flag[times] = -1;
}

inline void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]] + key[k];
	fff[k] = fff[ch[k][0]] + fff[ch[k][1]] + flag[k];
//	printf("G%d %lld %d\n", k, sum[k], fff[k]);
}

inline void pushdown(int k)
{
	if (tag[k])
	{
//		printf("GG\n");
		if (ch[k][0])
		{
//			printf("L%d %d\n", ch[k][0], fff[ch[k][0]]);
			tag[ch[k][0]] += tag[k];
			sum[ch[k][0]] += tag[k] * fff[ch[k][0]];
			key[ch[k][0]] += tag[k] * flag[ch[k][0]];
		}
		if (ch[k][1])
		{
//			printf("L%d %d\n", ch[k][1], fff[ch[k][1]]);
			tag[ch[k][1]] += tag[k];
			sum[ch[k][1]] += tag[k] * fff[ch[k][1]];
			key[ch[k][1]] += tag[k] * flag[ch[k][1]];
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
	int mid = l + r >> 1;
	k = mid;
	fa[k] = father;
	tag[k] = 0;
	build(ch[k][0], l, mid - 1, mid);
	build(ch[k][1], mid + 1, r, mid);
	pushup(k);
//	printf("%d %d %d\n", l, r, fff[k]);
//	printf("%d %d %d %d %d %d %d\n", l, r, sum[k], k, ch[k][0], ch[k][1], father);
}

inline void rotate(int x)
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

inline void splay(int x, int &k)
{
	top = 0;
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

int right(int x)
{
	return ch[x][1] ? right(ch[x][1]) : x;
}

int left(int x)
{
	return ch[x][0] ? left(ch[x][0]) : x;
}

inline int query_pre(int x)
{
//	printf("VX%d %d\n", x, ch[x][0]);
	splay(x, root);
	int ans = right(ch[x][0]);
	splay(ans, root);
	return ans;
}

inline int query_next(int x)
{
//	printf("VY%d %d\n", x, ch[x][1]);
	splay(x, root);
	int ans = left(ch[x][1]);
	splay(ans, root);
	return ans;
}

inline int split(int l, int r)
{
//	printf("GGG%d %d\n", l, r);
	int ll = query_pre(l);
	int rr = query_next(r);
//	printf("V%d %d %d %d\n", ll, l, r, rr);
	splay(ll, root);
	splay(rr, ch[root][1]);
	return ch[ch[root][1]][0];
}

inline long long query(int l, int r)
{
	int tmp = split(l, r);
	return sum[tmp];
}

inline int del(int l, int r)
{
	int tmp = split(l, r);
	ch[ch[root][1]][0] = 0;
	fa[tmp] = 0;
//	printf("VX%d %d\n", tmp, ch[root][1]);
	pushup(ch[root][1]);
	pushup(root);
	return tmp;
}

inline void paste(int x, int y)
{
	int kk = query_next(x);
	splay(x, root);
	splay(kk, ch[root][1]);
	ch[ch[root][1]][0] = y;
	fa[y] = ch[root][1];
//	printf("VY%d %d\n", y, ch[root][1]);
	pushup(ch[root][1]);
	pushup(root);
}

inline void change(int l, int r, int delta)
{
//	printf("%d %d\n", l, r);
	int tmp = split(l, r);
	tag[tmp] += delta;
	sum[tmp] += (long long)delta * fff[tmp];
	key[tmp] += delta * flag[tmp];
//	printf("VV%d %d %d\n", l, r, fff[tmp]);
	pushup(ch[root][1]);
	pushup(root);
}

int main()
{
//	freopen("galaxy.in", "r", stdin);
	n = read();
	for (int i = 2; i <= n; i++)
	{
		int father;
		father = read();
		add(father, i);
	}
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	times++;
	dfs(1);
	times++;
//	for (int i = 1; i <= times; i++)
//	{
//		printf("%d %d\n", i, key[i]);
//	}
	build(root, 1, times, 0);
	m = read();
	while (m--)
	{
		scanf("%s", cas);
		if (cas[0] == 'Q')
		{
			int pos;
			pos = read();
			printf("%lld\n", query(2, in[pos]));
		}
		if (cas[0] == 'C')
		{
			int x, y;
			x = read();
			y = read();
			int tmp = del(in[x], out[x]);
			paste(in[y], tmp);
		}
		if (cas[0] == 'F')
		{
			int x, delta;
			x = read();
			delta = read();
			change(in[x], out[x], delta);
		}
	}
	return 0;
}


