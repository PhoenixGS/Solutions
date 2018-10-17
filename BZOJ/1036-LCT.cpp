#include <cstdio>
#include <algorithm>

int n, m, top;
int stack[40000];
int fa[40000];
int ch[40000][2];
int u[40000];
int v[40000];
long long tree[40000];
long long sum[40000];
long long maxx[40000];
bool rev[40000];
char st[1000];

bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void update(int x)
{
	int l = ch[x][0];
	int r = ch[x][1];
	sum[x] = sum[l] + sum[r] + tree[x];
	maxx[x] = std::max(tree[x], std::max(tree[l], tree[r]));
}

void pushdown(int x)
{
	int l = ch[x][0];
	int r = ch[x][1];
	if (rev[x])
	{
		rev[x] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		std::swap(ch[x][0], ch[x][1]);
	}
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int l = (ch[y][1] == x);
	int r = l ^ 1;
	if (! isroot(y))
	{
		ch[z][ch[z][1] == y] = x;
	}
	fa[ch[x][r]] = y;
	fa[y] = x;
	fa[x] = z;
	ch[y][l] = ch[x][r];
	ch[x][r] = y;
	update(y);
	update(x);
}

void splay(int x)
{
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
			if (ch[y][0] == x ^ ch[z][0] == y)
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

void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
	splay(x);
}

void split(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
}

int main()
{
	scanf("%d", &n);
	maxx[0] = -1000000000;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &u[i], &v[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &tree[i]);
		maxx[i] = sum[i] = tree[i];
	}
	for (int i = 1; i < n; i++)
	{
		link(u[i], v[i]);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", st + 1);
		if (st[1] == 'C')
		{
			int x, k;
			scanf("%d%d", &x, &k);
			splay(x);
			tree[x] = k;
			update(x);
		}
		else
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if (st[2] == 'M')
			{
				split(u, v);
				printf("%lld\n", maxx[v]);
			}
			else
			{
				split(u, v);
				printf("%lld\n", sum[v]);
			}
		}
	}
	return 0;
}
