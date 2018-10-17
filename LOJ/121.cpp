#include <cstdio>
#include <map>

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
int min[600000], pos[600000], me[600000], fa[600000], ch[600000][2], rev[600000];
int ff[5005][5005];
int top;
int stack[600000];
int last[600000], pred[600000];
int cas[600000], x[600000], y[600000];

inline bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

inline void pushup(int k)
{
	if (min[ch[k][0]] < min[ch[k][1]])
	{
		min[k] = min[ch[k][0]];
		pos[k] = pos[ch[k][0]];
	}
	else
	{
		min[k] = min[ch[k][1]];
		pos[k] = pos[ch[k][1]];
	}
	if (me[k] < min[k])
	{
		min[k] = me[k];
		pos[k] = k;
	}
}

inline void pushdown(int k)
{
	if (rev[k])
	{
		std::swap(ch[k][0], ch[k][1]);
		if (ch[k][0])
		{
			rev[ch[k][0]] ^= 1;
		}
		if (ch[k][1])
		{
			rev[ch[k][1]] ^= 1;
		}
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
	fa[ch[y][w]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

inline void splay(int x)
{
//	printf("S%d\n", x);
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
//		printf("G%d\n", x);
		splay(x);
		ch[x][1] = t;
		pushup(x);
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
}

inline void cut(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	ch[y][0] = fa[x] = 0;
	pushup(y);
}

inline int findleft(int x)
{
	int ans = x;
	while (ch[ans][0])
	{
		ans = ch[ans][0];
	}
	return ans;
}

inline int query(int x, int y)
{
//	printf("V%d %d\n", x, y);
	makeroot(x);
//	printf("M%d\n", x);
	access(y);
	splay(y);
	int kk = findleft(y);
	splay(kk);
	return x == kk;
}

inline std::pair<int, int> querymin(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	return std::make_pair(min[y], pos[y]);
}

inline void add(int u, int v, int cost, int id)
{
	min[id] = cost;
	pos[id] = id;
	me[id] = cost;
	if (query(u, v))
	{
		std::pair<int, int> t = querymin(u, v);
		if (cost > t.first)
		{
			cut(t.second, x[t.second - n]);
			cut(t.second, y[t.second - n]);
			link(u, id);
			link(v, id);
		}
	}
	else
	{
		link(u, id);
		link(v, id);
	}
}

inline void del(int x, int y, int id)
{
	if (query(x, id))
	{
		cut(x, id);
		cut(y, id);
	}
}

int main()
{
	n = read();
	m = read();
	for (int i = 0; i <= n; i++)
	{
		me[i] = min[i] = 1000000000;
		pos[i] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		cas[i] = read();
		x[i] = read();
		y[i] = read();
		if (x[i] > y[i])
		{
			std::swap(x[i], y[i]);
		}
		if (cas[i] == 0)
		{
			ff[x[i]][y[i]] = i;
		}
		if (cas[i] == 1)
		{
			last[ff[x[i]][y[i]]] = i;
			pred[i] = ff[x[i]][y[i]];
			ff[x[i]][y[i]] = 0;
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (ff[i][j])
			{
				last[ff[i][j]] = m + 1;
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		if (cas[i] == 0)
		{
//			printf("A%d %d %d %d\n", x[i], y[i], last[i], n + i);
			add(x[i], y[i], last[i], n + i);
		}
		if (cas[i] == 1)
		{
//			printf("D%d %d %d\n", x[i], y[i], n + pred[i]);
			del(x[i], y[i], n + pred[i]);
		}
		if (cas[i] == 2)
		{
			printf(query(x[i], y[i]) ? "Y\n" : "N\n");
		}
	}
	return 0;
}
