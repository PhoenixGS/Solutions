#include <cstdio>
#include <vector>
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

const int _n = 500000 + 10;
int n, m, root;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int f[_n], s[_n], t[_n];
int vis[_n];
std::vector<std::pair<int, int> > vec[_n];
int ans[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void dfs(int u, int father)
{
	vis[u] = 1;
	for (int i = 0; i < (int)vec[u].size(); i++)
	{
		if (vis[vec[u][i].first])
		{
			ans[vec[u][i].second] = t[findfather(vec[u][i].first)];
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			int xx = findfather(u);
			int yy = findfather(v);
			if (s[yy] > s[xx])
			{
				f[xx] = yy;
				t[yy] = t[xx];
			}
			else
			{
				if (s[xx] == s[yy])
				{
					s[xx]++;
				}
				f[yy] = xx;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= m; i++)
	{
		int u = read();
		int v = read();
		vec[u].push_back(std::make_pair(v, i));
		vec[v].push_back(std::make_pair(u, i));
	}
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
		s[i] = 1;
		t[i] = i;
	}
	dfs(root, 0);
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}

