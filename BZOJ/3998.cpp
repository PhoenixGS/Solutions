#include <cstdio>
#include <cstring>
#include <queue>

const int _n = 500000 + 10;
int n;
int cas;
long long rank;
char st[_n];
int last, knum;
int pre[2 * _n], len[2 * _n], ch[2 * _n][26];
int cnt[2 * _n];
long long sum[2 * _n];
int vis[2 * _n];
int in[2 * _n];
std::queue<int> que;

void extend(int c)
{
	knum++;
	int u = last;
	int v = knum;
	len[v] = len[u] + 1;
	last = v;
	for (; u && ! ch[u][c]; u = pre[u])
	{
		ch[u][c] = v;
	}
	if (! u)
	{
		pre[v] = 1;
		return;
	}
	int w = ch[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		return;
	}
	knum++;
	int neww = knum;
	pre[neww] = pre[w];
	len[neww] = len[u] + 1;
	for (int i = 0; i < 26; i++)
	{
		ch[neww][i] = ch[w][i];
	}
	pre[w] = pre[v] = neww;
	for (; u && ch[u][c] == w; u = pre[u])
	{
		ch[u][c] = neww;
	}
}

void dfs(int u)
{
	if (vis[u])
	{
		return;
	}
	vis[u] = 1;
	for (int i = 0; i < 26; i++)
	{
		if (ch[u][i])
		{
			dfs(ch[u][i]);
			sum[u] += sum[ch[u][i]];
		}
	}
	if (u != 1)
	{
		sum[u] += cas == 0 ? 1 : cnt[u];
	}
}

void find(int u, long long rank)
{
	if (u != 1)
	{
		rank -= (cas == 0 ? 1 : cnt[u]);
	}
	if (rank <= 0)
	{
		return;
	}
	for (int i = 0; i < 26; i++)
	{
		if (rank > sum[ch[u][i]])
		{
			rank -= sum[ch[u][i]];
		}
		else
		{
			printf("%c", i + 'a');
			find(ch[u][i], rank);
			return;
		}
	}
}

int main()
{
#ifdef debug
	freopen("3998.in", "r", stdin);
#endif
	scanf("%s", st + 1);
	scanf("%d%lld", &cas, &rank);
	n = strlen(st + 1);
	last = 1;
	knum = 1;
	for (int i = 1; i <= n; i++)
	{
		extend(st[i] - 'a');
		cnt[last]++;
	}
	for (int i = 2; i <= knum; i++)
	{
		in[pre[i]]++;
	}
	for (int i = 1; i <= knum; i++)
	{
		if (! in[i])
		{
			que.push(i);
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		cnt[pre[u]] += cnt[u];
		in[pre[u]]--;
		if (! in[pre[u]])
		{
			que.push(pre[u]);
		}
	}
	dfs(1);
	if (rank > sum[1])
	{
		puts("-1");
	}
	else
	{
		find(1, rank);
		puts("");
	}
	return 0;
}
