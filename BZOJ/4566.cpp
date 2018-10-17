#include <cstdio>
#include <cstring>
#include <queue>

char s[300000];
int n;
int last, knum;
int len[1200000], to[1200000][27], pre[1200000], size[1200000][2];;
int cnt[1200000];
std::queue<int> que;
long long ans;

void add(int c, int cas)
{
	int u = last;
	if (to[u][c])
	{
		int w = to[u][c];
		if (len[u] + 1 == len[w])
		{
			last = w;
			size[w][cas]++;
			return;
		}
		knum++;
		int neww = knum;
		pre[neww] = pre[w];
		for (int i = 0; i < 26; i++)
		{
			to[neww][i] = to[w][i];
		}
		pre[w] = neww;
		len[neww] = len[u] + 1;
		for (; u && to[u][c] == w; u = pre[u])
		{
			to[u][c] = neww;
		}
		last = neww;
		size[neww][cas]++;
		return;
	}
	knum++;
	int v = knum;
	size[v][cas]++;
	last = v;
	len[v] = len[u] + 1;
	for (; u && ! to[u][c]; u = pre[u])
	{
		to[u][c] = v;
	}
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
	pre[w] = pre[v] = neww;
	len[neww] = len[u] + 1;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}

int main()
{
	knum = 1;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	last = 1;
	for (int i = 1; i <= n; i++)
	{
		add(s[i] - 'a', 0);
	}
	scanf("%s", s + 1);
	n = strlen(s + 1);
	last = 1;
	for (int i = 1; i <= n; i++)
	{
		add(s[i] - 'a', 1);
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
		size[pre[u]][0] += size[u][0];
		size[pre[u]][1] += size[u][1];
//		printf("G%d %d\n", pre[u], u);
		cnt[pre[u]]--;
		if (! cnt[pre[u]])
		{
			que.push(pre[u]);
		}
	}
	for (int i = 2; i <= knum; i++)
	{
		ans = ans + (long long)(len[i] - len[pre[i]]) * size[i][0] * size[i][1];
//		printf("%d %d %d\n", i, size[i][0], size[i][1]);
	}
	printf("%lld\n", ans);
	return 0;
}
