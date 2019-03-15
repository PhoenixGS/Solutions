#include <cstdio>
#include <cmath>
#include <algorithm>

struct QUES
{
	int id;
	int l, r;
	int lca;
};

int n, m;
int x[50000];
int tmp[50000];
int n1;
int times;
int in[50000], out[50000];
int pos[100000];
int fa[50000][21], deep[50000];
int cc[50000], cnt[50000];
int ans;
int anss[200000];
int knumber;
int knum[200000];
QUES ques[200000];
int edgenum;
int vet[100000], nextx[100000], head[50000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool comp(QUES x, QUES y)
{
	if (knum[x.l] != knum[y.l])
	{
		return knum[x.l] < knum[y.l];
	}
	if (knum[x.l] & 1)
	{
		return x.r < y.r;
	}
	else
	{
		return x.r > y.r;
	}
}

void dfs(int u)
{
	times++;
	in[u] = times;
	pos[times] = u;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! in[v])
		{
			fa[v][0] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
		}
	}
	times++;
	out[u] = times;
	pos[times] = u;
}

int querylca(int x, int y)
{
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if (deep[fa[x][i]] >= deep[y])
		{
			x = fa[x][i];
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

void add(int k)
{
	cc[pos[k]]++;
	if (cc[pos[k]] == 2)
	{
		cnt[x[pos[k]]]--;
		if (cnt[x[pos[k]]] == 0)
		{
			ans--;
		}
	}
	else
	{
		cnt[x[pos[k]]]++;
		if (cnt[x[pos[k]]] == 1)
		{
			ans++;
		}
	}
}

void del(int k)
{
	cc[pos[k]]--;
	if (cc[pos[k]] == 0)
	{
		cnt[x[pos[k]]]--;
		if (cnt[x[pos[k]]] == 0)
		{
			ans--;
		}
	}
	else
	{
		cnt[x[pos[k]]]++;
		if (cnt[x[pos[k]]] == 1)
		{
			ans++;
		}
	}
}

int main()
{
	edgenum = 0;
	times = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		tmp[i] = x[i];
	}
	std::sort(tmp + 1, tmp + n + 1);
	n1 = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for (int i = 1; i <= n; i++)
	{
		x[i] = std::lower_bound(tmp + 1, tmp + n1 + 1, x[i]) - tmp;
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	deep[1] = 1;
	dfs(1);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (in[u] > in[v])
		{
			std::swap(u, v);
		}
		ques[i].id = i;
		ques[i].l = in[u] + 1;
		ques[i].r = out[v] - 1;
		ques[i].lca = querylca(u, v);
	}
	int knumber = sqrt(times);
	for (int i = 1; i <= times; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + m + 1, comp);
	ans = 0;
	int l = 1;
	int r = 0;
	for (int i = 1; i <= m; i++)
	{
		while (r < ques[i].r)
		{
			r++;
			add(r);
		}
		while (l > ques[i].l)
		{
			l--;
			add(l);
		}
		while (r > ques[i].r)
		{
			del(r);
			r--;
		}
		while (l < ques[i].l)
		{
			del(l);
			l++;
		}
		anss[ques[i].id] = ans + (cnt[x[ques[i].lca]] == 0);
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", anss[i]);
	}
	return 0;
}
