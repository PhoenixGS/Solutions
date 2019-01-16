#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 300000 + 10;
int n, m, lim;
int x[_n];
int knum;
int root[_n];
int sum[20 * _n], ch[20 * _n][2];
int ans;

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int &v, int u, int l, int r, int pos, int delta)
{
	knum++;
	v = knum;
	sum[v] = sum[u];
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (l == r)
	{
		sum[v] += delta;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[v][0], ch[u][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[v][1], ch[u][1], mid + 1, r, pos, delta);
	}
	pushup(v);
}

int find(int u, int v, int l, int r, int s)
{
	if (l == r)
	{
		if ((sum[u] - sum[v]) * 2 > s)
		{
			return l;
		}
		return -1;
	}
	int mid = (l + r) >> 1;
	if (sum[ch[u][0]] - sum[ch[v][0]] > sum[ch[u][1]] - sum[ch[v][1]])
	{
		return find(ch[u][0], ch[v][0], l, mid, s);
	}
	else
	{
		return find(ch[u][1], ch[v][1], mid + 1, r, s);
	}
}

int main()
{
#ifdef debug
	freopen("2223.in", "r", stdin);
#endif
	scanf("%d%d", &n, &lim);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		change(root[i], root[i - 1], 1, lim, x[i], 1);
	}
	scanf("%d", &m);
	while (m--)
	{
		int l = read();
		int r = read();
		ans = find(root[r], root[l - 1], 1, lim, r - l + 1);
		if (ans == -1)
		{
			puts("no");
		}
		else
		{
			printf("yes %d\n", ans);
		}
	}
	return 0;
}
