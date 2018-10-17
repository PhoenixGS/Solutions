#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <map>
struct myhash   
{  
    size_t operator()(std::pair<int, int> __val) const  
    {  
        return static_cast<size_t>(__val.first * 101 + __val.second);  
    }  
};  
/*struct myhash
{
	size_t operator () (std::pair<int, int> x)const
	{
		return static_cast<size_t>(((long long)x.first * 10000 + x.second) % 998244353);
	}
};*/

std::unordered_set<std::pair<int, int>, myhash> set;
int edgenum;
int vet[2000000], nextx[2000000], head[400000];
int degree[400000];
int n, m, k;
int ans;
int cc;
int c[400000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool check(int x, int y)
{
	return degree[x] < degree[y] || (degree[x] == degree[y] && x < y);
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		set.clear();
		edgenum = 0;
		memset(head, 0, sizeof(head));
		memset(degree, 0, sizeof(degree));
		ans = 0;
		for (int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			degree[u]++;
			degree[v]++;
			set.insert(std::make_pair(u, v));
			set.insert(std::make_pair(v, u));
			add(u, v);
			add(v, u);
		}
		k = sqrt(m);
		for (int x = 1; x <= n; x++)
		{
			if (degree[x] <= k)
			{
				for (int i = head[x]; i; i = nextx[i])
				{
					int y = vet[i];
					if (check(x, y))
					{
						for (int j = head[x]; j; j = nextx[j])
						{
							int z = vet[i];
							if (check(y, z))
							{
								ans += (set.find(std::make_pair(y, z)) != set.end());
							}
						}
					}
				}
			}
		}
		cc = 0;
		for (int i = 1; i <= n; i++)
		{
			if (degree[i] > k)
			{
				cc++;
				c[cc] = i;
			}
		}
		for (int i = 1; i <= cc; i++)
		{
			for (int j = i + 1; j <= cc; j++)
			{
				for (int k = j + 1; k <= cc; k++)
				{
					ans += (set.find(std::make_pair(i, j)) != set.end() && set.find(std::make_pair(j, k)) != set.end() && set.find(std::make_pair(k, i)) != set.end());
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
