#include <cstdio>
#include <queue>
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

const int INF = 1000000000;
const int _n = 500 + 10;
int n, m;
int g[_n][_n];
int lx[_n], ly[_n];
int visx[_n], visy[_n];
int matchx[_n], matchy[_n];
int pre[_n];
int slack[_n];
std::queue<int> que;
long long ans;

bool check(int v)
{
	visy[v] = true;
	if (matchy[v] != -1)
	{
		que.push(matchy[v]);
		visx[matchy[v]] = true;
		return false;
	}
	while (v != -1)
	{
		matchy[v] = pre[v];
		std::swap(v, matchx[pre[v]]);
	}
	return true;
}

void bfs(int s)
{
	for (int i = 1; i <= n; i++)
	{
		slack[i] = INF;
		visx[i] = visy[i] = 0;
	}
	que.push(s);
	visx[s] = 1;
	while (true)
	{
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			for (int v = 1; v <= n; v++)
			{
				if (! visy[v])
				{
					int delta = lx[u] + ly[v] - g[u][v];
					if (slack[v] >= delta)
					{
						pre[v] = u;
						if (delta)
						{
							slack[v] = delta;
						}
						else
						{
							if (check(v))
							{
								return;
							}
						}
					}
				}
			}
		}
		int mx = INF;
		for (int i = 1; i <= n; i++)
		{
			if (! visy[i])
			{
				mx = std::min(mx, slack[i]);
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (visx[i])
			{
				lx[i] -= mx;
			}
			if (visy[i])
			{
				ly[i] += mx;
			}
			else
			{
				slack[i] -= mx;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (! visy[i] && slack[i] == 0 && check(i))
			{
				return;
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			g[i][j] = -INF;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int u = read();
		int v = read();
		g[u][v] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			lx[i] = std::max(lx[i], g[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		matchx[i] = matchy[i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		bfs(i);
	}

	for (int i = 1; i <= n; i++)
	{
		ans += g[i][matchx[i]];
	}

	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", matchy[i]);
	}
	puts("");
	return 0;
}
