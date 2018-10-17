#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct hash
{
	int operator () (const std::pair<int, int> x) const
	{
		return ((long long)x.first * 1001 + x.second) % 998244353;
	}
};

std::unordered_set<std::pair<int, int>, hash> set;
int n, m;
int edgenum;
int vet[3000000], nextx[3000000], head[2000];
int key[2000];
int maxx;
std::vector<int> vec[3000000];
int list[2000], rank[2000];
int vis[2000];
int last;
int kk[2000];
int ff[2000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void insert(int key, int x)
{
	vec[key].push_back(x);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
		set.insert(std::make_pair(u, v));
		set.insert(std::make_pair(v, u));
	}
	for (int i = 1; i <= n; i++)
	{
		key[i] = 0;
		insert(key[i], i);
	}
	maxx = 0;
	for (int i = n; i >= 1; i--)
	{
		int u = -1;
		while (u == -1)
		{
			while ((int)vec[maxx].size() > 0)
			{
				if (! ff[vec[maxx][vec[maxx].size() - 1]])
				{
					u = vec[maxx][vec[maxx].size() - 1];
					break;
				}
				vec[maxx].pop_back();
			}
			if (! vec[maxx].size())
			{
				maxx--;
			}
		}
		ff[u] = 1;
		list[i] = u;
		vis[u] = 1;
		for (int j = head[u]; j; j = nextx[j])
		{
			int v = vet[j];
			if (! vis[v])
			{
				key[v]++;
				vec[key[v]].push_back(v);
				maxx = std::max(maxx, key[v]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		rank[list[i]] = i;
	}
	bool flag = true;
	for (int i = 1; i <= n; i++)
	{
		int u = list[i];
		last = 0;
		for (int j = head[u]; j; j = nextx[j])
		{
			int v = vet[j];
			if (rank[v] > rank[u])
			{
				last++;
				kk[last] = v;
			}
		}
		int minx = kk[1];
		for (int j = 2; j <= last; j++)
		{
			if (rank[kk[j]] < rank[minx])
			{
				minx = kk[j];
			}
		}
		for (int j = 1; j <= last; j++)
		{
			if (minx != kk[j] && set.find(std::make_pair(minx, kk[j])) == set.end())
			{
				flag = false;
				break;
			}
		}
		if (! flag)
		{
			break;
		}
	}
	puts(flag ? "Perfect" : "Imperfect");
	return 0;
}
