#include <cstdio>
#include <cstring>

int m, n;
int edgenum;
int vet[100000];
int nextx[100000];
int head[100000];
bool flag[100000];
int match[100000];
int ans;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool find(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! flag[v])
		{
			flag[v] = true;
			if (match[v] == -1 || find(match[v]))
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
	scanf("%d%d", &m, &n);
	edgenum = 0;
	int x, y;
	while (scanf("%d%d", &x, &y) == 2 && x != -1 && y != -1)
	{
		add(x, y + m);
	}
	ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 1; i <= n; i++)
	{
		memset(flag, 0, sizeof(flag));
		ans += find(i);
	}
	if (ans == 0)
	{
		printf("No Solution!\n");
	}
	else
	{
		printf("%d\n", ans);
	}
	return 0;
}
