#include <cstdio>
#include <algorithm>

int f[200][200];
int TIM;
int F[20000];
int T;
int n;
int ans;
bool flag;

int main()
{
	TIM = 0;
	for (int i = 2; i <= 100; i++)
	{
		for (int j = 2; j <= 100; j++)
		{
			if (i != j)
			{
				TIM++;
				for (int k = 1; k < i - 1; k++)
				{
					if (i - k != j)
					{
						F[f[i - k][j]] = TIM;
					}
				}
				for (int k = 1; k < j - 1; k++)
				{
					if (j - k != i)
					{
						F[f[i][j - k]] = TIM;
					}
				}
				for (int k = 1; k < std::min(i, j) - 1; k++)
				{
					F[f[i - k][j - k]] = TIM;
				}
				for (f[i][j] = 0; F[f[i][j]] == TIM; f[i][j]++);
			}
		}
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		ans = 0;
		flag = 0;
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x++;
			y++;
			if (x == 1 || y == 1 || x == y)
			{
				flag = 1;
			}
			ans = ans ^ f[x][y];
		}
		if (flag || ans)
		{
			puts("^o^");
		}
		else
		{
			puts("T_T");
		}
	}
	return 0;
}
