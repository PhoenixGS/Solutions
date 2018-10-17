#include <cstdio>
#include <algorithm>
#include <cstring>

int edgenum;
int vet[3000000];
int nextx[3000000];
int head[3000];
int dfn[3000];
int low[3000];
bool instack[3000];
int top;
int stack[3000];
int n, m;
int times;
int knumber;
int knum[3000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void Tarjan(int u)
{
	times++;
	dfn[u] = times;
	low[u] = times;
	top++;
	stack[top] = u;
	instack[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! dfn[v])
		{
			Tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else
		{
			if (instack[v])
			{
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (low[u] == dfn[u])
	{
		knumber++;
		int v;
		do
		{
			v = stack[top];
			knum[v] = knumber;
			instack[v] = 0;
			top--;
		}while (v != u);
	}
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		edgenum = 0;
		times = 0;
		memset(head, 0, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(instack, 0, sizeof(instack));
		for (int i = 1; i <= m; i++)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
			int x = x1 * 2 + y1;
			int y = x2 * 2 + y2;
			add(x, y ^ 1);
			add(y, x ^ 1);
		}
		knumber = 0;
		for (int i = 0; i < 2 * n; i++)
		{
			if (! dfn[i])
			{
				Tarjan(i);
			}
		}
		bool flag = true;
		for (int i = 0; i < n; i++)
		{
			if (knum[i * 2] == knum[i * 2 + 1])
			{
				flag = false;
			}
		}
		if (flag)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
