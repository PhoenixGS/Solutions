#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

int knum, last, root;
std::map<int, int> to[300000];
int len[300000], pre[300000];
int n;
long long ans;

void add(int c)
{
	knum++;
	int u = last;
	int v = knum;
	last = v;
	len[v] = len[u] + 1;
	for (; u && ! to[u][c]; u = pre[u])
	{
		to[u][c] = v;
	}
	if (! u)
	{
		pre[v] = root;
		ans = ans + len[v] - len[pre[v]];
		return;
	}
	int w = to[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		ans = ans + len[v] - len[pre[v]];
		return;
	}
	knum++;
	int neww = knum;
	pre[neww] = pre[w];
	len[neww] = len[w];
	to[neww] = to[w];
	pre[w] = pre[v] = neww;
	len[neww] = len[u] + 1;
	ans = ans + len[v] - len[pre[v]];
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}

int main()
{
	scanf("%d", &n);
	knum = root = last = 1;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(x);
		printf("%lld\n", ans);
	}
	return 0;
}
