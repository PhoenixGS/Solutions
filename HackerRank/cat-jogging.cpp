#include <cstdio>

int n, m;
int degree[60000];
int edgenum;
int vet[300000], nextx[300000], head[60000];
int vedgenum;
int vvet[300000], vnextx[300000], vhead[60000];
int cnt[60000];
long long ans;

int check(int u, int v)
{
	return degree[u] < degree[v] || (degree[u] == degree[v] && u < v);
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void vadd(int u, int v)
{
	vedgenum++;
	vvet[vedgenum] = v;
	vnextx[vedgenum] = vhead[u];
	vhead[u] = vedgenum;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		degree[u]++;
		degree[v]++;
		add(u, v);
		add(v, u);
	}
	for (int u = 1; u <= n; u++)
	{
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			if (check(u, v))
			{
				vadd(u, v);
				vadd(v, u);
			}
		}
	}
	for (int x = 1; x <= n; x++)
	{
		for (int i = head[x]; i; i = nextx[i])
		{
			int y = vet[i];
			for (int j = vhead[y]; j; j = vnextx[j])
			{
				int z = vvet[j];
				if (check(x, z) && check(y, z))
				{
					ans -= (long long)cnt[z] * (cnt[z] - 1) / 2;
					cnt[z]++;
					ans += (long long)cnt[z] * (cnt[z] - 1) / 2;
				}
			}
		}
		for (int i = head[x]; i; i = nextx[i])
		{
			int y = vet[i];
			for (int j = vhead[y]; j; j = vnextx[j])
			{
				int z = vvet[j];
				if (check(x, z) && check(y, z))
				{
					cnt[z]--;
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
