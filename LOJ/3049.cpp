#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct node
{
	int cas, pos, l, r;
};

const int _n = 200000 + 10;
int T;
int n, na, nb, m;
int zz;
int cnt[_n];
char s[_n];
int x[_n];
node z[2 * _n];
int SA[_n], tp[_n], rank[_n], height[_n];
int pre[_n][22], nxt[_n][22];
int edgenum;
int vet[36 * _n + 60 * _n + _n + _n + _n], nextx[36 * _n + 60 * _n + _n + _n + _n], head[_n + _n + 20 * _n];
int in[_n + _n + 20 * _n], flag[_n + _n + 20 * _n];
long long f[_n + _n + 20 * _n];
int root, knum;
int ch[20 * _n][2];
int pp[_n];
int la[_n], ra[_n];
std::queue<int> que;

bool comp(node x, node y)
{
	return (x.r - x.l + 1 > y.r - y.l + 1) || (x.r - x.l + 1 == y.r - y.l + 1 && x.cas < y.cas);
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
	in[v]++;
}

void RadixSort()
{
	for (int i = 0; i <= zz; i++)
	{
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[rank[tp[i]]]++;
	}
	for (int i = 1; i <= zz; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i >= 1; i--)
	{
		SA[cnt[rank[tp[i]]]--] = tp[i];
	}
}

int cmp(int *f, int x, int y, int w)
{
	return f[x] == f[y] && f[x + w] == f[y + w];
}

void Suffix()
{
	for (int i = 1; i <= n; i++)
	{
		rank[i] = x[i];
		tp[i] = i;
	}
	zz = 127;
	RadixSort();
	for (int w = 1, p = 1, i; p < n; w <<= 1, zz = p)
	{
		for (p = 0, i = n - w + 1; i <= n; i++)
		{
			p++;
			tp[p] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (SA[i] > w)
			{
				p++;
				tp[p] = SA[i] - w;
			}
		}
		RadixSort();
		std::swap(rank, tp);
		rank[SA[1]] = p = 1;
		for (int i = 2; i <= n; i++)
		{
			rank[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++p;
		}
	}
	int j, k = 0;
	for (int i = 1; i <= n; height[rank[i++]] = k)
	{
		for (k = k ? k - 1 : k, j = SA[rank[i] - 1]; x[i + k] == x[j + k]; k++);
	}
}

void change(int u, int &v, int l, int r, int pos, int from)
{
	knum++;
	v = knum;
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (l == r)
	{
		if (u != 0)
		{
			add(na + nb + v, na + nb + u);
		}
		add(na + nb + v, from);
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, pos, from);
	}
	else
	{
		change(ch[u][1], ch[v][1], mid + 1, r, pos, from);
	}
	if (ch[v][0])
	{
		add(na + nb + v, na + nb + ch[v][0]);
	}
	if (ch[v][1])
	{
		add(na + nb + v, na + nb + ch[v][1]);
	}
}

void query(int k, int l, int r, int L, int R, int from)
{
	if (L <= l && r <= R)
	{
		if (k != 0)
		{
			add(from, na + nb + k);
		}
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)
	{
		query(ch[k][0], l, mid, L, R, from);
	}
	if (R > mid)
	{
		query(ch[k][1], mid + 1, r, L, R, from);
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		edgenum = 0;
		for (int i = 1; i <= na + nb + knum; i++)
		{
			head[i] = 0;
			in[i] = flag[i] = f[i] = 0;
		}
		root = knum = 0;
		for (int i = 1; i <= n; i++)
		{
			SA[i] = rank[i] = height[i] = tp[i] = cnt[i] = 0;
		}

		scanf("%s", s + 1);
		n = strlen(s + 1);
		scanf("%d", &na);
		for (int i = 1; i <= na; i++)
		{
			z[i].cas = 0;
			z[i].pos = i;
			z[i].l = read();
			z[i].r = read();
			la[i] = z[i].l;
			ra[i] = z[i].r;
		}
		scanf("%d", &nb);
		for (int i = 1; i <= nb; i++)
		{
			z[na + i].cas = 1;
			z[na + i].pos = i;
			z[na + i].l = read();
			z[na + i].r = read();
		}
		std::sort(z + 1, z + na + nb + 1, comp);

		for (int i = 1; i <= n; i++)
		{
			x[i] = s[i];
		}
		Suffix();
		for (int i = 1; i <= n; i++)
		{
			pre[i][0] = height[i];
			nxt[i][0] = height[i];
		}
		for (int j = 1; j <= 20; j++)
		{
			for (int i = 1; i <= n; i++)
			{
				if (i - (1 << (j - 1)) >= 1)
				{
					pre[i][j] = std::min(pre[i][j - 1], pre[i - (1 << (j - 1))][j - 1]);
				}
				else
				{
					pre[i][j] = -1;
				}
				if (i + (1 << (j - 1)) <= n)
				{
					nxt[i][j] = std::min(nxt[i][j - 1], nxt[i + (1 << (j - 1))][j - 1]);
				}
				else
				{
					nxt[i][j] = -1;
				}
			}
		}

		for (int i = 1; i <= na + nb; i++)
		{
			if (z[i].cas == 0)
			{
				change(root, root, 1, n, rank[z[i].l], z[i].pos);
			}
			else
			{
				int ll = rank[z[i].l];
				for (int j = 20; j >= 0; j--)
				{
					if (pre[ll][j] >= z[i].r - z[i].l + 1)
					{
						ll = ll - (1 << j);
					}
				}
				int rr = rank[z[i].l];
				for (int j = 20; j >= 0; j--)
				{
					if (nxt[rr + 1][j] >= z[i].r - z[i].l + 1)
					{
						rr = rr + (1 << j);
					}
				}
				query(root, 1, n, ll, rr, na + z[i].pos);
			}
		}


/*
		for (int i = 1; i <= nb; i++)
		{
			int ll = rank[lb[i]];
			for (int j = 20; j >= 0; j--)
			{
				if (pre[ll][j] >= rb[i] - lb[i] + 1)
				{
					ll = ll - (1 << j);
				}
			}
			int rr = rank[lb[i]];
			for (int j = 20; j >= 0; j--)
			{
				if (nxt[rr + 1][j] >= rb[i] - lb[i] + 1)
				{
					rr = rr + (1 << j);
				}
			}
			link(1, 1, n, ll, rr, i);
		}
		for (int i = 1; i <= na; i++)
		{
			add(na + nb + pp[rank[la[i]]], i);
		}
		*/

		scanf("%d", &m);
		while (m--)
		{
			int x = read();
			int y = read();
			add(x, na + y);
		}
		for (int i = 1; i <= na + nb + knum; i++)
		{
			if (! in[i])
			{
				que.push(i);
			}
		}
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			flag[u] = 1;
			if (1 <= u && u <= na)
			{
				f[u] += ra[u] - la[u] + 1;
			}
			for (int i = head[u]; i; i = nextx[i])
			{
				int v = vet[i];
				f[v] = std::max(f[v], f[u]);
				in[v]--;
				if (! in[v])
				{
					que.push(v);
				}
			}
		}
		int fff = false;
		long long ans = 0;
		for (int i = 1; i <= na; i++)
		{
			if (flag[i] == 0)
			{
				fff = true;
				break;
			}
			ans = std::max(ans, f[i]);
		}
		if (fff)
		{
			puts("-1");
		}
		else
		{
			printf("%lld\n", ans);
		}
	}
	return 0;
}

