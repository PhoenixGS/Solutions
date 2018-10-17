#include <cstdio>
#include <algorithm>

struct EDGE
{
	int u, v, x, y;
};

EDGE edge[200000];
int key[300000];
int fa[300000], ch[300000][2], tree[300000], maxx[300000], rev[300000];;
int f[300000];
int n, m;
int ans;
int top;
int stack[300000];

bool comp(EDGE x, EDGE y)
{
	return x.x < y.x;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void update(int x)
{
	if (tree[ch[x][0]] > tree[ch[x][1]])
	{
		tree[x] = tree[ch[x][0]];
		maxx[x] = maxx[ch[x][0]];
	}
	else
	{
		tree[x] = tree[ch[x][1]];
		maxx[x] = maxx[ch[x][1]];
	}
	if (key[x] > tree[x])
	{
		tree[x] = key[x];
		maxx[x] = x;
	}
}

void pushdown(int x)
{
	if (rev[x])
	{
		rev[ch[x][0]] ^= 1;
		rev[ch[x][1]] ^= 1;
		std::swap(ch[x][0], ch[x][1]);
		rev[x] = 0;
	}
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int w = ch[y][1] == x;
	if (! isroot(y))
	{
		ch[z][ch[z][1] == y] = x;
	}
	fa[x] = z;
	ch[y][w] = ch[x][w ^ 1];
	fa[ch[x][w ^ 1]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	update(y);
	update(x);
}

void splay(int x)
{
	top = 0;
	top++;
	stack[top] = x;
	for (int i = x; ! isroot(i); i = fa[i])
	{
		top++;
		stack[top] = fa[i];
	}
	while (top)
	{
		pushdown(stack[top]);
		top--;
	}
	while (! isroot(x))
	{
		int y = fa[x];
		int z = fa[y];
		if (! isroot(y))
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

void access(int x)
{
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		ch[x][1] = t;
		update(x);
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x] ^= 1;
}

void split(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
}

void link(int u, int v)
{
	makeroot(u);
	fa[u] = v;
}

void cut(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	ch[v][0] = fa[u] = 0;
	update(v);
}

void add(EDGE x, int pos)
{
	int xx = findfather(x.u);
	int yy = findfather(x.v);
	if (xx != yy)
	{
		f[xx] = yy;
		link(x.u, pos + n);
		link(pos + n, x.v);
	}
	else
	{
		split(x.u, x.v);
		if (tree[x.v] > x.y)
		{
			int vv = maxx[x.v] - n;
			cut(edge[vv].u, vv + n);
			cut(vv + n, edge[vv].v);
			link(x.u, pos + n);
			link(pos + n, x.v);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &edge[i].u, &edge[i].v, &edge[i].x, &edge[i].y);
	}
	std::sort(edge + 1, edge + m + 1, comp);
	for (int i = 1; i <= m; i++)
	{
		key[i + n] = edge[i].y;
	}
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	ans = 1000000000;
	int now = 1;
	while (now <= m)
	{
		add(edge[now], now);
		while (now < m && edge[now + 1].x == edge[now].x)
		{
			add(edge[now + 1], now + 1);
			now++;
		}
		if (findfather(1) == findfather(n))
		{
			split(1, n);
			ans = std::min(ans, edge[now].x + tree[n]);
		}
		now++;
	}
	if (ans == 1000000000)
	{
		puts("-1");
	}
	else
	{
		printf("%d\n", ans);
	}
	return 0;
}

