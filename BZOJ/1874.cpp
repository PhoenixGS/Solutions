#include <cstdio>
#include <algorithm>

int n;
int x[2000];
int maxx;
int m;
int v[2000];
int T[2000];
int f[2000];

int main()
{
	maxx = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		maxx = std::max(maxx, x[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &v[i]);
	}
	std::sort(v + 1, v + m + 1);
	f[0] = 0;
	for (int i = 1; i <= maxx; i++)
	{
		for (int j = 1; j <= m && v[j] <= i; j++)
		{
			T[f[i - v[j]]] = i;
		}
		for (f[i] = 0; T[f[i]] == i; f[i]++);
	}
	int tmp = 0;
	for (int i = 1; i <= n; i++)
	{
		tmp = tmp ^ f[x[i]];
	}
	if (tmp)
	{
		puts("YES");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m && v[j] <= x[i]; j++)
			{
				if ((tmp ^ f[x[i]] ^ f[x[i] - v[j]]) == 0)
				{
					printf("%d %d\n", i, v[j]);
					return 0;
				}
			}
		}
	}
	else
	{
		puts("NO");
	}
	return 0;
}
