#include <cstdio>
#include <algorithm>

int n, m;
int fa[60000], ch[60000][2];
long long key[60000], sumx[60000], sum[60000], suml[60000], sumr[60000], tag[60000], size[60000];
int rev[60000];
int top;
int stack[60000];
int x[60000];

long long gcd(long long x, long long y)
{
	return y == 0 ? x : gcd(y, x % y);
}

bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void change(int k, int delta)
{
	tag[k] += delta;
	key[k] += delta;
	sumx[k] += size[k] * (size[k] + 1) * (size[k] + 2) / 6 * delta;
	sum[k] += size[k] * delta;
	suml[k] += size[k] * (size[k] + 1) / 2 * delta;
	sumr[k] += size[k] * (size[k] + 1) / 2 * delta;
}

void pushup(int k)
{
	sumx[k] = sumx[ch[k][0]] + sumx[ch[k][1]] + (size[ch[k][1]] + 1) * suml[ch[k][0]] + (size[ch[k][0]] + 1) * sumr[ch[k][1]] + key[k] * (size[ch[k][0]] + 1) * (size[ch[k][1]] + 1);
	//printf("%d %lld %lld %d %d %lld %lld %lld %lld %lld\n", k, suml[ch[k][0]], sumr[ch[k][1]], ch[k][0], ch[k][1], size[ch[k][0]], size[ch[k][1]], sumx[ch[k][0]], sumx[ch[k][1]], sumx[k]);
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]] + key[k];
	suml[k] = suml[ch[k][0]] + suml[ch[k][1]] + (size[ch[k][0]] + 1) * sum[ch[k][1]] + (size[ch[k][0]] + 1) * key[k];
	sumr[k] = sumr[ch[k][1]] + sumr[ch[k][0]] + (size[ch[k][1]] + 1) * sum[ch[k][0]] + (size[ch[k][1]] + 1) * key[k];
	size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
}

void pushdown(int k)
{
	if (tag[k])
	{
		if (ch[k][0])
		{
			change(ch[k][0], tag[k]);
		}
		if (ch[k][1])
		{
			change(ch[k][1], tag[k]);
		}
		tag[k] = 0;
	}
	if (rev[k])
	{
		rev[ch[k][0]] ^= 1;
		rev[ch[k][1]] ^= 1;
		std::swap(suml[ch[k][0]], sumr[ch[k][0]]);
		std::swap(suml[ch[k][1]], sumr[ch[k][1]]);
		std::swap(ch[k][0], ch[k][1]);
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
	fa[ch[x][w ^ 1]] = y;
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
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		ch[x][1] = t;
		pushup(x);
	}
}

void makeroot(int u)
{
	access(u);
	splay(u);
	rev[u] ^= 1;
}

void cut(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	ch[v][0] = fa[u] = 0;
	pushup(v);
}

void link(int u, int v)
{
	makeroot(u);
	fa[u] = v;
	access(u);
}

void change(int u, int v, int delta)
{
	makeroot(u);
	access(v);
	splay(v);
	change(v, delta);
}

int findroot(int u)
{
	return isroot(u) ? u : findroot(fa[u]);
}

bool check(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	int tmp = findroot(u);
	splay(u);
	return tmp == v;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		key[i] = x[i];
		size[i] = 1;
		sumx[i] = x[i];
		sum[i] = x[i];
		suml[i] = x[i];
		sumr[i] = x[i];
		tag[i] = 0;
	}
	for (int i = 2; i <= n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		link(u, v);
		//printf("%lld %lld %lld %lld %d\n", sumx[v], sum[v], suml[v], sumr[v]);
	}
	//puts("X");
	//makeroot(1);
	//printf("%lld\n", sumx[1]);
	//makeroot(2);
	//printf("%lld\n", sumx[2]);
	for (int i = 1; i <= m; i++)
	{
		int cas;
		scanf("%d", &cas);
		if (cas == 1)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if (check(u, v))
			{
				cut(u, v);
			}
		}
		if (cas == 2)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if (! check(u, v))
			{
				link(u, v);
			}
		}
		if (cas == 3)
		{
			int u, v, delta;
			scanf("%d%d%d", &u, &v, &delta);
			if (check(u, v))
			{
				change(u, v, delta);
			}
		}
		if (cas == 4)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if (check(u, v))
			{
				makeroot(u);
				access(v);
				splay(v);
				long long up = sumx[v];
				long long down = size[v] * (size[v] + 1) / 2;
				long long d = gcd(up, down);
				up /= d;
				down /= d;
				printf("%lld/%lld\n", up, down);
			}
			else
			{
				printf("-1\n");
			}
		}
	}
	return 0;
}
