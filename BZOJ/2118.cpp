#include <cstdio>
#include <queue>

int n;
long long l, r;
int x[20];
int edgenum;
int vet[7000000];
int val[7000000];
int nextx[7000000];
int head[600000];
std::queue<int> Q;
bool inque[600000];
long long dis[600000];
int kk;

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

long long calc(long long k)
{
	long long ans = 0;
	for (int i = 0; i < kk; i++)
	{
		if (k >= dis[i])
		{
			ans += (k - dis[i]) / (long long)kk + 1;
		}
	}
	return ans;
}

int main()
{
	edgenum = 0;
	scanf("%d%lld%lld", &n, &l, &r);
	kk = 1000000000;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		if (x[i] == 0)
		{
			i--;
			n--;
		}
		kk = std::min(kk, x[i]);
	}
	for (int i = 0; i < kk; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (x[j] % kk)
			{
				add(i, (i + x[j]) % kk, x[j]);
			}
		}
	}
	for (int i = 0; i < kk; i++)
	{
		dis[i] = 1000000000000000ll;
	}
	dis[0] = 0;
	Q.push(0);
	inque[0] = true;
	while (! Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inque[u] = false;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (dis[u] + cost < dis[v])
			{
				dis[v] = dis[u] + cost;
				if (! inque[v])
				{
					Q.push(v);
					inque[v] = true;
				}
			}
		}
	}
	printf("%lld\n", calc(r) - calc(l - 1));
	return 0;
}
