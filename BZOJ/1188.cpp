#include <cstdio>

int T[1000];
int f[100];
int cas, n;
int x[100];
int ans;

int main()
{
	for (int i = 1; i <= 22; i++)
	{
		for (int j = 1; j < i; j++)
		{
			for (int k = 1; k <= j; k++)
			{
				T[f[j] ^ f[k]] = i;
			}
		}
		for (f[i] = 0; T[f[i]] == i; f[i]++);
	}
	scanf("%d", &cas);
	while (cas--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
		}
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			if (x[i] & 1)
			{
				ans = ans ^ f[n - i + 1];
			}
		}
		if (ans)
		{
			int cnt = 0;
			int ansi, ansj, ansk;
			for (int i = 1; i <= n; i++)
			{
				for (int j = i + 1; j <= n; j++)
				{
					for (int k = j; k <= n; k++)
					{
						if (x[i])
						{
							if ((ans ^ f[n - i + 1] ^ f[n - j + 1] ^ f[n - k + 1]) == 0)
							{
								if (! cnt)
								{
									ansi = i;
									ansj = j;
									ansk = k;
								}
								cnt++;
							}
						}
					}
				}
			}
			ansi--;
			ansj--;
			ansk--;
			printf("%d %d %d\n%d\n", ansi, ansj, ansk, cnt);
		}
		else
		{
			printf("-1 -1 -1\n0\n");
		}
	}
	return 0;
}
