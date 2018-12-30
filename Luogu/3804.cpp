#include <cstdio>
#include <cstring>
#include <queue>

const int _n = 1000000 + 10;
int n;
char s[_n];
int last, knum;
int pre[2 * _n], len[2 * _n], size[2 * _n], to[2 * _n][26];
int in[2 * _n];
std::queue<int> que;
long long ans;

void extend(int c)
{
	knum++;
	int u = last;
	int v = knum;
	size[v] = 1;
	last = knum;
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
	len[neww] = len[u] + 1;
	for (int i = 0; i < 26; i++)
	{
		to[neww][i] = to[w][i];
	}
	pre[w] = pre[v] = neww;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}

int main()
{
	last = 1;
	knum = 1;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		extend(s[i] - 'a');
	}
	for (int i = 1; i <= knum; i++)
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
		size[pre[u]] += size[u];
		in[pre[u]]--;
		if (! in[pre[u]])
		{
			que.push(pre[u]);
		}
	}
	ans = 0;
	for (int i = 1; i <= knum; i++)
	{
		if (size[i] > 1)
		{
			ans = std::max(ans, (long long)len[i] * size[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
