#include <cstdio>
#include <algorithm>

int n;
int x[10005];
short int f[10005][10005];
short int ans;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	std::sort(x + 1, x + n + 1);
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			f[i][j] = 2;
		}
	}
	for (int j = 2; j < n; j++)
	{
		int i = j - 1;
		int k = j + 1;
		while (i >= 1 && k <= n)
		{
			if (x[i] + x[k] < 2 * x[j])
			{
				k++;
			}
			else
			{
				if (x[i] + x[k] > 2 * x[j])
				{
					i--;
				}
				else
				{
					f[j][k] = f[i][j] + 1;
					if (f[j][k] > ans)
					{
						ans = f[j][k];
					}
					i--;
					k++;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
