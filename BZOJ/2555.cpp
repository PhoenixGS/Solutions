#include <cstdio>
#include <cstring>
#include <algorithm>

int T;
char s[700000];
char cas[100];
int fa[2000000], ch[2000000][2], rev[2000000], tree[2000000], tag[2000000];
int to[2000000][27];
int knum, last;
int len[2000000];
int top;
int stack[2000000];
int pre[2000000];
int mask;

void getmask(char *s, int mask)
{
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		mask = (mask * 131 + i - 1) % n;
		std::swap(s[mask + 1], s[i]);
	}
}

bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void add(int x, int delta)
{
//	printf("G%d\n", delta);
	tag[x] += delta;
	tree[x] += delta;
}

void pushdown(int x)
{
	if (rev[x])
	{
		std::swap(ch[x][0], ch[x][1]);
		rev[ch[x][0]] ^= 1;
		rev[ch[x][1]] ^= 1;
		rev[x] = 0;
	}
	if (tag[x])
	{
		if (ch[x][0])
		{
			add(ch[x][0], tag[x]);
		}
		if (ch[x][1])
		{
			add(ch[x][1], tag[x]);
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
	//update(y);
	//update(x);
}

void splay(int x)
{
//	printf("K%d\n", x);
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
			if ((ch[z][1] == y) ^ (ch[y][1] == z))
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
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x] ^= 1;
}

void link(int x, int f)
{
	makeroot(x);
	fa[x] = f;
	access(f);
	splay(f);
	add(f, tree[x]);
}

void cut(int x, int f)
{
	access(x);
	splay(x);
	add(f, -tree[x]);
	ch[x][0] = fa[f] = 0;
}

void add(int c)
{
	knum++;
	int u = last;
	int v = knum;
	last = v;
	len[v] = len[u] + 1;
	tree[v] = 1;
	for (; u && ! to[u][c]; u = pre[u])
	{
//		printf("Y%d\n", u);
		to[u][c] = v;
	}
//	printf("X%d\n", u);
	if (! u)
	{
//		printf("%d %d\n", v, fa[v]);
		link(v, 1);
		pre[v] = 1;
		return;
	}
	int w = to[u][c];
	if (len[u] + 1 == len[w])
	{
		link(v, w);
		pre[v] = w;
		return;
	}
	knum++;
	int neww = knum;
	link(neww, pre[w]);
	pre[neww] = pre[w];
	for (int i = 0; i < 26; i++)
	{
		to[neww][i] = to[w][i];
	}
	cut(w, pre[w]);
	link(w, neww);
	pre[w] = neww;
	link(v, neww);
	pre[v] = neww;
	len[neww] = len[u] + 1;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}

void update(char* s)
{
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		add(s[i] - 'A');
	}
}

int query(char* s)
{
	int n = strlen(s + 1);
	int u = 1;
	for (int i = 1; i <= n; i++)
	{
//		printf("V%d %d %d\n", u, s[i] - 'A', to[u][s[i] - 'A']);
		if (! to[u][s[i] - 'A'])
		{
			return 0;
		}
		u = to[u][s[i] - 'A'];
	}
//	printf("G%d\n", u);
	splay(u);
	return tree[u] + tag[u];
}

int main()
{
	knum = 1;
	last = 1;
	scanf("%d", &T);
	scanf("%s", s + 1);
	update(s);
	while (T--)
	{
		scanf("%s%s", cas + 1, s + 1);
		if (cas[1] == 'A')
		{
			getmask(s, mask);
			update(s);
		}
		else
		{
			getmask(s, mask);
			int ans = query(s);
			printf("%d\n", ans);
			mask = mask ^ ans;
		}
	}
	return 0;
}
