#include <cstdio>
#include <cmath>
#include <algorithm>

double x0 = 0.5;
double tmp[20];
double tree[200000][20];
double key[200000][20];
int fa[200000], ch[200000][2], rev[200000];
int cas[200000];
double a[200000], b[200000];
char st[200];
char type[200];
double fact[200];
int n, m;
int top;
int stack[200000];

inline bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

inline void calc(int k)
{
	if (cas[k] == 1)
	{
		key[k][0] = sin(a[k] * x0 + b[k]);
		key[k][1] = cos(a[k] * x0 + b[k]) * a[k];
		for (int i = 2; i <= 16; i++)
		{
			key[k][i] = -key[k][i - 2] * a[k] * a[k];
		}
	}
	if (cas[k] == 2)
	{
		key[k][0] = exp(a[k] * x0 + b[k]);
		for (int i = 1; i <= 16; i++)
		{
			key[k][i] = key[k][i - 1] * a[k];
		}
	}
	if (cas[k] == 3)
	{
		key[k][0] = a[k] * x0 + b[k];
		key[k][1] = a[k];
		for (int i = 2; i <= 16; i++)
		{
			key[k][i] = 0;
		}
	}
}

inline void update(int k)
{
	for (int i = 0; i <= 16; i++)
	{
		tree[k][i] = tree[ch[k][0]][i] + tree[ch[k][1]][i] + key[k][i];
	}
}

inline void pushdown(int k)
{
	if (rev[k])
	{
		if (ch[k][0])
		{
			rev[ch[k][0]] ^= 1;
		}
		if (ch[k][1])
		{
			rev[ch[k][1]] ^= 1;
		}
		std::swap(ch[k][0], ch[k][1]);
		rev[k] = 0;
	}
}

inline void rotate(int x)
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

inline void splay(int x)
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
			if ((ch[y][1] == x) ^ (ch[z][1] == y))
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

inline void access(int x)
{
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		ch[x][1] = t;
		update(x);
	}
}

inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x] ^= 1;
}

inline void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
	access(x);
	splay(x);
}

inline void cut(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	ch[y][0] = fa[x] = 0;
	update(x);
}

inline int findanc(int x)
{
	for (; ! isroot(x); x = fa[x]);
	return x;
}

int main()
{
	fact[0] = 1.0;
	for (int i = 1; i <= 16; i++)
	{
		fact[i] = fact[i - 1] * (double)i;
	}
	scanf("%d%d%s", &n, &m, type + 1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%lf%lf", &cas[i], &a[i], &b[i]);
		calc(i);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", st + 1);
		if (st[1] == 'a')
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u++;
			v++;
			link(u, v);
		}
		if (st[1] == 'd')
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u++;
			v++;
			cut(u, v);
		}
		if (st[1] == 'm')
		{
			int pos;
			scanf("%d", &pos);
			pos++;
			splay(pos);
			scanf("%d%lf%lf", &cas[pos], &a[pos], &b[pos]);
			calc(pos);
			update(pos);
		}
		if (st[1] == 't')
		{
			int u, v;
			double x;
			scanf("%d%d%lf", &u, &v, &x);
			u++;
			v++;
			makeroot(u);
			access(v);
			splay(v);
			if (findanc(u) != v)
			{
				printf("unreachable\n");
				continue;
			}
			double ans = 0.0;
			double tmp = 1.0;
			for (int i = 0; i <= 16; i++)
			{
				ans += tree[v][i] * tmp / fact[i];
				tmp = tmp * (x - x0);
			}
			printf("%.8e\n", ans);
		}
	}
	return 0;
}
