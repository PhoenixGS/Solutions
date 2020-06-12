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
int T, n, na, nb, m;
char s[_n];
int len[_n];
node z[2 * _n];
int pre[_n][22], nxt[_n][22];
int edgenum;
int vet[100 * _n], nextx[100 * _n], head[100 * _n];
int in[22 * _n];
int root, knum;
int ch[20 * _n][2];
long long f[22 * _n];
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

namespace suf
{
	int zz;
	int cnt[_n];
	int sa[_n], tp[_n], rank[_n], height[_n];

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
			sa[cnt[rank[tp[i]]]--] = tp[i];
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
			rank[i] = s[i];
			tp[i] = i;
		}
		zz = 127;
		RadixSort();
		for (int w = 1, p; p < n; w <<= 1, zz = p)
		{
			p = 0;
			for (int i = n - w + 1; i <= n; i++)
			{
				p++;
				tp[p] = i;
			}
			for (int i = 1; i <= n; i++)
			{
				if (sa[i] > w)
				{
					p++;
					tp[p] = sa[i] - w;
				}
			}
			RadixSort();
			std::swap(rank, tp);
			rank[sa[1]] = p = 1;
			for (int i = 2; i <= n; i++)
			{
				rank[sa[i]] = cmp(tp, sa[i], sa[i - 1], w) ? p : ++p;
			}
		}
		int j, k = 0;
		for (int i = 1; i <= n; height[rank[i++]] = k)
		{
			for (k = k ? k - 1 : k, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
		}
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
		if (u)
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
		if (k)
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
			in[i] = f[i] = 0;
		}
		root = knum = 0;
		for (int i = 1; i <= n; i++)
		{
			suf::sa[i] = suf::rank[i] = suf::height[i] = suf::tp[i] = suf::cnt[i] = 0;
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
			len[i] = z[i].r - z[i].l + 1;
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

		suf::Suffix();
		for (int i = 1; i <= n; i++)
		{
			pre[i][0] = suf::height[i];
			nxt[i][0] = suf::height[i];
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
				change(root, root, 1, n, suf::rank[z[i].l], z[i].pos);
			}
			else
			{
				int ll = suf::rank[z[i].l];
				for (int j = 20; j >= 0; j--)
				{
					if (pre[ll][j] >= z[i].r - z[i].l + 1)
					{
						ll = ll - (1 << j);
					}
				}
				int rr = suf::rank[z[i].l];
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
			if (1 <= u && u <= na)
			{
				f[u] += len[u];
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
			if (in[i])
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
