#include <cstdio>

int n;
int edgenum; 
int vet[3000000];
int nextx[3000000];
int head[2000000];
int match[2000000];
int ans;
int T;
int flag[2000000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool check(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (flag[v] != T)
		{
			flag[v] = T;
			if (! match[v] || check(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(i, n + x);
		add(n + x, i);
		add(i, n + y);
		add(n + y, i);
	}
	T = 1;
	for (ans = 1; check(n + ans); ans++, T++);
	printf("%d\n", ans - 1);
	return 0;
}
