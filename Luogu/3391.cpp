#include <cstdio>
#include <algorithm>

const int _n = 100000 + 10;
int n, m;
int root;
int fa[_n], ch[_n][2], size[_n], rev[_n];
int top;
int stack[_n];

void pushup(int k)
{
	size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
}

void pushdown(int k)
{
	if (rev[k])
	{
		rev[ch[k][0]] ^= 1;
		rev[ch[k][1]] ^= 1;
		std::swap(ch[k][0], ch[k][1]);
		rev[k] = 0;
	}
}

void build(int &k, int l, int r, int father)
{
	if (l > r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	k = mid;
	fa[k] = father;
	build(ch[k][0], l, mid - 1, mid);
	build(ch[k][1], mid + 1, r, mid);
	pushup(k);
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int w = ch[y][1] == x;
	ch[z][ch[z][1] == y] = x;
	fa[x] = z;
	ch[y][w] = ch[x][w ^ 1];
	fa[ch[x][w ^ 1]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

void splay(int x, int k = 0)
{
	top++;
	stack[top] = x;
	for (int i = x; fa[i] != k; i = fa[i])
	{
		top++;
		stack[top] = fa[i];
	}
	while (top)
	{
		pushdown(stack[top]);
		top--;
	}
	while (fa[x] != k)
	{
		int y = fa[x];
		int z = fa[y];
		if (z != k)
		{
			if ((ch[z][0] == y) ^ (ch[y][0] == x))
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
	if (! k)
	{
		root = x;
	}
}

int find(int k, int rank)
{
	pushdown(k);
	if (rank <= size[ch[k][0]])
	{
		return find(ch[k][0], rank);
	}
	if (rank == size[ch[k][0]] + 1)
	{
		return k;
	}
	return find(ch[k][1], rank - size[ch[k][0]] - 1);
}

void print(int k)
{
	if (! k)
	{
		return;
	}
	pushdown(k);
	print(ch[k][0]);
	if (k != 1 && k != n + 2)
	{
		printf("%d ", k - 1);
	}
	print(ch[k][1]);
}

int main()
{
#ifdef debug
	freopen("3391.in", "r", stdin);
#endif
	scanf("%d%d", &n, &m);
	build(root, 1, n + 2, 0);
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int ll = find(root, l);
		int rr = find(root, r + 2);
		splay(ll);
		splay(rr, ll);
		rev[ch[rr][0]] ^= 1;
	}
	print(root);
	puts("");
	return 0;
}
