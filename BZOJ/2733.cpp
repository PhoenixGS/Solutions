#include <cstdio>

int n, m, k;
int root[4000000];
int ch[4000000][2];
int sum[4000000];
int num;
char st[20];
int ans[4000000];
int f[4000000];

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int &k, int l, int r, int pos, int delta)
{
	if (! k)
	{
		num++;
		k = num;
	}
	if (l == r)
	{
		sum[k] += delta;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos, delta);
	}
	pushup(k);
}

void unionx(int &x, int y)
{
	if (! y)
	{
		return;
	}
	if (! x)
	{
		x = y;
		return;
	}
	unionx(ch[x][0], ch[y][0]);
	unionx(ch[x][1], ch[y][1]);
	pushup(x);
}

int find(int k, int l, int r, int rank)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	if (rank <= sum[ch[k][0]])
	{
		return find(ch[k][0], l, mid, rank);
	}
	else
	{
		return find(ch[k][1], mid + 1, r, rank - sum[ch[k][0]]);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		ans[x] = i;
		change(root[i], 1, n, x, 1);
	}
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		int xx = findfather(x);
		int yy = findfather(y);
		if (xx != yy)
		{
			f[xx] = yy;
			unionx(root[yy], root[xx]);
		}
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++)
	{
		scanf("%s", st + 1);
		if (st[1] == 'Q')
		{
			int pos, rank;
			scanf("%d%d", &pos, &rank);
			int ff = findfather(pos);
			if (rank > sum[root[ff]])
			{
				printf("-1\n");
			}
			else
			{
				printf("%d\n", ans[find(root[ff], 1, n, rank)]);
			}
		}
		else
		{
			int x, y;
			scanf("%d%d", &x, &y);
			int xx = findfather(x);
			int yy = findfather(y);
			if (xx != yy)
			{
				f[xx] = yy;
				unionx(root[yy], root[xx]);
			}
		}
	}
	return 0;
}
