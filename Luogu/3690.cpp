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
int n, m;

namespace LCT
{
	int key[_n], sum[_n], ch[_n][2], fa[_n], tag[_n];
	int top;
	int stack[_n];

	bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}

	void pushup(int x)
	{
		sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ key[x];
	}

	void pushdown(int x)
	{
		if (tag[x])
		{
			std::swap(ch[x][0], ch[x][1]);
			if (ch[x][0])
			{
				tag[ch[x][0]] ^= 1;
			}
			if (ch[x][1])
			{
				tag[ch[x][1]] ^= 1;
			}
			tag[x] = 0;
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

	int findroot(int x)
	{
		access(x);
		splay(x);
		pushdown(x);
		while (ch[x][0])
		{
			x = ch[x][0];
			pushdown(x);
		}
		splay(x);
		return x;
	}

	void makeroot(int x)
	{
		access(x);
		splay(x);
		tag[x] ^= 1;
	}

	void link(int x, int y)
	{
		makeroot(x);
		if (findroot(y) == x)
		{
			return;
		}
		fa[x] = y;
	}

	void cut(int x, int y)
	{
		makeroot(x);
		if (findroot(y) != x || fa[y] != x || ch[y][0])
		{
			return;
		}
		fa[y] = 0;
		ch[x][1] = 0;
	}
}

int main()
{
	using namespace LCT;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		key[i] = read();
	}
	while (m--)
	{
		int op = read();
		int x = read();
		int y = read();
		if (op == 0)
		{
			makeroot(x);
			access(y);
			splay(y);
			printf("%d\n", sum[y]);
		}
		if (op == 1)
		{
			link(x, y);
		}
		if (op == 2)
		{
			cut(x, y);
		}
		if (op == 3)
		{
			access(x);
			splay(x);
			key[x] = y;
			pushup(x);
		}
	}
	return 0;
}
