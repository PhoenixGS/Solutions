#include <cstdio>

void dfs(int u, int father)
{
	int fa = 0;
	for (int i = 0; i < (int)vec[u].size(); i++)
	{
		int v = vec[u][i].first;
		int cost = vec[u][i].second;
		if (v != father)
		{
			if (fa == 0)
			{
				add(u, v, cost);
				fa = u;
			}
			else
			{
				knum++;
				add(fa, knum, 0);
				add(knum, v, cost);
				fa = knum;
			}
			dfs(v, u);
		}
	}
}

void calcsz(int u, int father)
{
	sz[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! del[i])
		{
			calcsz(v, u);
			sz[u] += sz[v];
		}
	}
}

std::pair<int, int> getroot(int u, int father)
{
	std::pair<int, int> ans(INF, -1);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! del[i])
		{
			int tmp = std::max(sz[v], size - sz[v]);
			if (tmp < ans.first)
			{
				ans = std::make_pair(tmp, i);
			}
			std::pair<int, int> t = getroot(v, u);
			if (t.first < ans.first)
			{
				ans = t;
			}
		}
	}
	return ans;
}

int calc(int u)
{
	calcsize(u, 0);
	size = sz[u];
	int id = getroot(u, 0).second;
	if (id == -1)
	{
		return 0;
	}
	del[id] = del[id ^ 1] = 1;
	int 
}

int main()
{
	edgenum = 1;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v, cost;
		scanf("%d%d%d", &u, &v, &cost);
		vec[u].push_back(std::make_pair(v, cost));
		vec[v].push_back(std::make_pair(u, cost));
	}
	knum = n;
	dfs(1, 0);
	calc(1);
}
