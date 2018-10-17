#include <cstdio>
#include <stack>
#include <cstring>

int edgenum;
int vet[300000];
int nextx[300000];
int head[20000];
int times;
int dfn[20000];
int low[20000];
int color[20000];
std::stack<int> stack;
int n, m;
int knum[20000];
int knumber;
int kedgenum;
int kvet[300000];
int knextx[300000];
int khead[20000];
int f[20000];
int in[20000];
int ans;
int x[20000];
int value[20000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void kadd(int u, int v)
{
	kedgenum++;
	kvet[kedgenum] = v;
	knextx[kedgenum] = khead[u];
	khead[u] = kedgenum;
}

void dfs(int u)
{
	times++;
	dfn[u] = times;
	low[u] = times;
	stack.push(u);
	color[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (color[v] == 0)
		{
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else
		{
			if (color[v] == 1)
			{
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (dfn[u] == low[u])
	{
		knumber++;
		while (stack.top() != u)
		{
			int v = stack.top();
			value[knumber] += x[v];
			knum[v] = knumber;
			color[v] = 2;
			stack.pop();
		}
		value[knumber] += x[u];
		knum[u] = knumber;
		color[u] = 2;
		stack.pop();
	}
}

int solve(int u)
{
	if (f[u] != -1)
	{
		return f[u];
	}
	int ans = 0;
	for (int i = khead[u]; i; i = knextx[i])
	{
		int v = kvet[i];
		ans = std::max(ans, solve(v));
	}
	return f[u] = ans + value[u];
}

int main()
{
	edgenum = 0;
	kedgenum = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	for (int i = 1; i <= n; i++)
	{
		if (color[i] == 0)
		{
			dfs(i);
		}
	}
	for (int u = 1; u <= n; u++)
	{
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			if (knum[u] != knum[v])
			{
				kadd(knum[u], knum[v]);
				in[knum[v]]++;
			}
		}
	}
	memset(f, -1, sizeof(f));
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0)
		{
			ans = std::max(ans, solve(i));
		}
	}
	printf("%d\n", ans);
	return 0;
}

