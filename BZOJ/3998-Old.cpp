#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

char st[600000];
int n, cas;
long long k;
int knum, last;
int len[1200000], to[1200000][27], pre[1200000];
long long s[1200000], ss[1200000], kk[1200000];
int cnt[1200000];
std::queue<int> que;
int anss;
char ans[1200000];

void add(int c)
{
	int u = last;
	knum++;
	int v = knum;
	len[v] = len[u] + 1;
	last = v;
//	printf("X%d %d\n", c, u);
	for (; u && ! to[u][c]; u = pre[u])
	{
//		printf("G%d %d\n", u, to[u][c]);
		to[u][c] = v;
	}
//	printf("Y%d %d\n", c, u);
	if (! u)
	{
		pre[v] = 1;
		return;
	}
	int w = to[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		return;
	}
	knum++;
	int neww = knum;
	pre[neww] = pre[w];
	for (int i = 0; i < 26; i++)
	{
		to[neww][i] = to[w][i];
	}
	len[neww] = len[u] + 1;
	pre[w] = pre[v] = neww;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}

void dfs(int u)
{
	if (ss[u])
	{
		return;
	}
	if (cas == 0)
	{
		//ss[u] = len[u] - len[pre[u]];
		ss[u] = kk[u] = 1;
	}
	else
	{
		//ss[u] = s[u] * (len[u] - len[pre[u]]);
		ss[u] = kk[u] = s[u];
	}
	for (int i = 0; i < 26; i++)
	{
		if (to[u][i])
		{
			dfs(to[u][i]);
			ss[u] += ss[to[u][i]];
		}
	}
//	printf("O%d %lld %lld\n", u, kk[u], ss[u]);
}

void print()
{
	for (int i = 1; i <= anss; i++)
	{
		printf("%c", ans[i]);
	}
	puts("");
}

void solve(int u, long long k)
{
	if (k <= kk[u])
	{
//		printf("K%d %lld\n", u, kk[u]);
		print();
		std::exit(0);
	}
	k -= kk[u];
	for (int i = 0; i < 26; i++)
	{
		if (to[u][i])
		{
			if (k > ss[to[u][i]])
			{
				k -= ss[to[u][i]];
			}
			else
			{
				anss++;
				ans[anss] = i + 'a';
				solve(to[u][i], k);
			}
		}
	}
}

int main()
{
	scanf("%s", st + 1);
	n = strlen(st + 1);
	scanf("%d%lld", &cas, &k);
	knum = 1;
	last = 1;
	for (int i = 1; i <= n; i++)
	{
		add(st[i] - 'a');
		s[last]++;
	}
	for (int i = 2; i <= knum; i++)
	{
		cnt[pre[i]]++;
	}
	for (int i = 1; i <= knum; i++)
	{
		if (! cnt[i])
		{
			que.push(i);
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		s[pre[u]] += s[u];
		cnt[pre[u]]--;
		if (! cnt[pre[u]])
		{
			que.push(pre[u]);
		}
	}
	dfs(1);
	kk[1] = 0;
	solve(1, k);
	printf("-1\n");
//	printf("G%lld\n", ss[1]);
	return 0;
}
