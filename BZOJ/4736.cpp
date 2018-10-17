#include <cstdio>
#include <algorithm>

const int INF = 1e9;
int n, m;
int uuu[400000], vvv[400000];
int x[500000], tem[500000];
int minx[500000], pos[500000], sum[500000], rev[500000];
int fa[500000], ch[500000][2];
int top;
int stack[500000];
int f[500000];
char st[100];

inline void update(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]] + x[k];
	if (minx[ch[k][0]] < minx[ch[k][1]])
	{
		minx[k] = minx[ch[k][0]];
		pos[k] = pos[ch[k][0]];
	}
	else
	{
		minx[k] = minx[ch[k][1]];
		pos[k] = pos[ch[k][1]];
	}
	if (tem[k] < minx[k])
	{
		minx[k] = tem[k];
		pos[k] = k;
	}
}

inline bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

inline void pushdown(int k)
{
	if (rev[k])
	{
		rev[ch[k][0]] ^= 1;
		rev[ch[k][1]] ^= 1;
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

inline void split(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
}

inline void link(int u, int v)
{
	makeroot(u);
	fa[u] = v;
}

inline void cut(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	ch[v][0] = fa[u] = 0;
	update(v);
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

inline void add(int u, int v, int id)
{
	int xx = findfather(u);
	int yy = findfather(v);
	if (xx != yy)
	{
		f[xx] = yy;
		link(u, id + n);
		link(id + n, v);
	}
	else
	{
		split(u, v);
		if (minx[v] < tem[id + n])
		{
			int vv = pos[v];
			cut(uuu[vv - n], vv);
			cut(vv, vvv[vv - n]);
			link(u, id + n);
			link(id + n, v);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	for (int i = 0; i <= n + m; i++)
	{
		tem[i] = minx[i] = INF;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", st + 1);
		if (st[1] == 'f')
		{
			int id;
			scanf("%d", &id);
			id++;
			scanf("%d%d%d%d", &uuu[id], &vvv[id], &tem[id + n], &x[id + n]);
			uuu[id]++;
			vvv[id]++;
			add(uuu[id], vvv[id], id);
		}
		if (st[1] == 'm')
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u++;
			v++;
			int xx = findfather(u);
			int yy = findfather(v);
			if (xx != yy)
			{
				puts("-1");
			}
			else
			{
				split(u, v);
				printf("%d\n", sum[v]);
			}
		}
		if (st[1] == 'c')
		{
			int id, newvalue;
			scanf("%d%d", &id, &newvalue);
			id++;
			splay(id + n);
			x[id + n] = newvalue;
			update(id + n);
		}
	}
	return 0;
}
