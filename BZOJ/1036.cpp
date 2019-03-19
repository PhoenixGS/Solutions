#include <cstdio>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int INF = 1000000000;
const int _n = 30000 + 10;
int n, m;
int x[_n];
int uuu[_n], vvv[_n];
char cas[10];
int ch[_n][2], sum[_n], maxx[_n], fa[_n], rev[_n];
int top;
int stack[_n];

bool isroot(int k)
{
	return ch[fa[k]][0] != k && ch[fa[k]][1] != k;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]] + x[k];
	maxx[k] = std::max(std::max(maxx[ch[k][0]], maxx[ch[k][1]]), x[k]);
}

void pushdown(int k)
{
	if (rev[k])
	{
		std::swap(ch[k][0], ch[k][1]);
		rev[ch[k][0]] ^= 1;
		rev[ch[k][1]] ^= 1;
		rev[k] = 0;
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
	fa[ch[y][w]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
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

void access(int x)
{
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		ch[x][1] = t;
		pushup(x);
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
}

void split(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
}

int main()
{
#ifdef debug
	freopen("1036.in", "r", stdin);
#endif
	maxx[0] = -INF;
	sum[0] = 0;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		uuu[i] = read();
		vvv[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i < n; i++)
	{
		link(uuu[i], vvv[i]);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", cas + 1);
		if (cas[1] == 'C')
		{
			int pos = read();
			int newvalue = read();
			splay(pos);
			x[pos] = newvalue;
			pushup(pos);
		}
		if (cas[2] == 'M')
		{
			int u = read();
			int v = read();
			split(u, v);
			printf("%d\n", maxx[v]);
		}
		if (cas[2] == 'S')
		{
			int u = read();
			int v = read();
			split(u, v);
			printf("%d\n", sum[v]);
		}
	}
	return 0;
}
