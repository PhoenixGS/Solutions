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

const int _n = 100000 + 10;
int n, q;
int col[_n];

namespace LCT
{
	int ch[_n][2], fa[_n], sum[_n];
	int rev[_n];

	int top;
	int stack[_n];

	bool isroot(int u)
	{
		return ch[fa[u]][0] != u && ch[fa[u]][1] != u;
	}

	void pushup(int u)
	{
		sum[u] = sum[ch[u][0]] + sum[ch[u][1]] + col[u];
	}

	void pushdown(int u)
	{
		if (rev[u])
		{
			rev[ch[u][0]] ^= 1;
			rev[ch[u][1]] ^= 1;
			std::swap(ch[u][0], ch[u][1]);
			rev[u] = 0;
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
		for (int i = x, t = 0; i; t = i, i = fa[i])
		{
			splay(i);
			ch[i][1] = t;
			pushup(i);
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

	int query(int x)
	{
		while (! (sum[ch[x][0]] == 0 && col[x]))
		{
			if (sum[ch[x][0]])
			{
				x = ch[x][0];
			}
			else
			{
				x = ch[x][1];
			}
		}
		return x;
	}
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		LCT::link(u, v);
	}
	LCT::makeroot(1);
	while (q--)
	{
		int op = read();
		if (op == 0)
		{
			int u = read();
			LCT::access(u);
			LCT::splay(u);
			col[u] ^= 1;
			LCT::pushup(u);
		}
		else
		{
			int u = read();
			LCT::access(u);
			LCT::splay(u);
			if (LCT::sum[u] == 0)
			{
				puts("-1");
			}
			else
			{
				printf("%d\n", LCT::query(u));
			}
		}
	}
	return 0;
}
