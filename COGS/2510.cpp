#include <cstdio>
#include <cstring>
#include <queue>

std::queue<int> que;
char s[2000000];
int n;
int nextx[2000000];
long long maxx[2000000], maxy[2000000];
int degree[2000000];
long long ans;

void getnextx()
{
	int j = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = nextx[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		nextx[i] = j;
	}
}

int main()
{
	freopen("savemzx.in", "r", stdin);
	freopen("savemzx.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	getnextx();
	for (int i = 0; i <= n; i++)
	{
		maxx[i] = maxy[i] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		degree[nextx[i]]++;
	}
	for (int i = 0; i <= n; i++)
	{
		if (! degree[i])
		{
			que.push(i);
		}
	}
	ans = 0;
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		if (maxx[u] != -1)
		{
			ans = std::max(ans, maxx[u]);
		}
		if (maxy[u] != -1)
		{
			ans = std::max(ans, maxx[u] + maxy[u]);
		}
		long long tmp = std::max(maxx[u], 0ll) + (long long)(u - nextx[u]) * (u - nextx[u]);
		if (tmp > maxx[nextx[u]])
		{
			maxy[nextx[u]] = maxx[nextx[u]];
			maxx[nextx[u]] = tmp;
		}
		else
		{
			if (tmp > maxy[nextx[u]])
			{
				maxy[nextx[u]] = tmp;
			}
		}
		degree[nextx[u]]--;
		if (! degree[nextx[u]])
		{
			que.push(nextx[u]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
