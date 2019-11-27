#include <cstdio>
#include <cmath>
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

struct QUES
{
	int l, r, times, idx;
};

const int _n = 100000 + 10;
int n, m, q;
int val[_n], w[_n];
int col[_n], tmp[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int deep[_n];
int fa[_n][22];
int knumber;
int knum[2 * _n];
int times;
int in[_n], out[_n];
int idx[2 * _n];
int qnum;
QUES ques[_n];
int cnum;
int cpos[_n], cpre[_n], cnxt[_n];
int cnt[_n];
int ll, rr, tt;
long long anss;
long long ans[_n];
int app[_n];

bool comp(QUES x, QUES y)
{
	return knum[x.l] < knum[y.l] || (knum[x.l] == knum[y.l] && knum[x.r] < knum[y.r]) || (knum[x.l] == knum[y.l] && knum[x.r] == knum[y.r] && x.times < y.times);
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	times++;
	in[u] = times;
	idx[times] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
		}
	}
	times++;
	out[u] = times;
	idx[times] = u;
}

void add(int u)
{
	if (app[u] == 0)
	{
		cnt[col[u]]++;
		anss += (long long)val[col[u]] * w[cnt[col[u]]];
	}
	else
	{
		anss -= (long long)val[col[u]] * w[cnt[col[u]]];
		cnt[col[u]]--;
	}
	app[u] ^= 1;
}

void change(int u, int newvalue)
{
	if (in[u] <= ll)
	{
		add(u);
	}
	if (in[u] <= rr)
	{
		add(u);
	}
	if (out[u] <= ll)
	{
		add(u);
	}
	if (out[u] <= rr)
	{
		add(u);
	}
	col[u] = newvalue;
	if (in[u] <= ll)
	{
		add(u);
	}
	if (in[u] <= rr)
	{
		add(u);
	}
	if (out[u] <= ll)
	{
		add(u);
	}
	if (out[u] <= rr)
	{
		add(u);
	}
}

int query_lca(int x, int y)
{
	if (deep[x] > deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) & (deep[y] - deep[x]))
		{
			y = fa[y][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &val[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
	{
		col[i] = read();
		tmp[i] = col[i];
	}
	qnum = cnum = 0;
	for (int i = 1; i <= q; i++)
	{
		int cas = read();
		if (cas == 0)
		{
			int pos = read();
			int newvalue = read();
			cnum++;
			cpos[cnum] = pos;
			cpre[cnum] = tmp[pos];
			tmp[pos] = newvalue;
			cnxt[cnum] = tmp[pos];
		}
		else
		{
			int u = read();
			int v = read();
			qnum++;
			ques[qnum].l = in[u];
			ques[qnum].r = in[v];
			if (ques[qnum].l > ques[qnum].r)
			{
				std::swap(ques[qnum].l, ques[qnum].r);
			}
			ques[qnum].times = cnum;
			ques[qnum].idx = qnum;
		}
	}
	knumber = pow(n, (double)2 / 3);
	for (int i = 1; i <= 2 * n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + q + 1, comp);
	ll = 0;
	rr = 0;
	tt = 0;
	anss = 0;
	for (int i = 1; i <= q; i++)
	{
		while (ll > ques[i].l)
		{
			add(idx[ll]);
			ll--;
		}
		while (rr < ques[i].r)
		{
			rr++;
			add(idx[rr]);
		}
		while (ll < ques[i].l)
		{
			ll++;
			add(idx[ll]);
		}
		while (rr > ques[i].r)
		{
			add(idx[rr]);
			rr--;
		}
		while (tt < ques[i].times)
		{
			tt++;
			change(cpos[tt], cnxt[tt]);
		}
		while (tt > ques[i].times)
		{
			change(cpos[tt], cpre[tt]);
			tt--;
		}
		int lca = query_lca(idx[ques[i].l], idx[ques[i].r]);
//		fprintf(stderr, "%d %d %d %d %d %d\n", app[lca], idx[ques[i].l], idx[ques[i].r], lca, ques[i].l, ques[i].r);
		ans[ques[i].idx] = anss + (long long)val[col[lca]] * w[cnt[col[lca]] + 1];
	}
	for (int i = 1; i <= qnum; i++)
	{
		printf("%lld\n", ans[i]);
	}
	return 0;
}
