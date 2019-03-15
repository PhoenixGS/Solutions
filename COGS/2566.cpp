#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

std::queue<int> que;
int n;
char s[2000000];
int nextx[2000000];
int degree[2000000];
int ss[2000000];
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
	freopen("string_maxval.in", "r", stdin);
	freopen("string_maxval.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	getnextx();
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
		ss[u]++;
		ans = std::max(ans, (long long)u * ss[u]);
		ss[nextx[u]] += ss[u];
		degree[nextx[u]]--;
		if (! degree[nextx[u]])
		{
			que.push(nextx[u]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
