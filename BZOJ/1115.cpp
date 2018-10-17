#include <cstdio>

int T;
int n;
int x[2000];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
		}
		int tmp = 0;
		for (int i = n; i >= 1; i -= 2)
		{
			tmp = tmp ^ (x[i] - x[i - 1]);
		}
		if (tmp)
		{
			printf("TAK\n");
		}
		else
		{
			printf("NIE\n");
		}
	}
	return 0;
}
