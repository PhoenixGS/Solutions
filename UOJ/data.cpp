#include <cstdio>
#include <ctime>
#include <cstdlib>

int n;

int main()
{
	srand(time(NULL));
	n = 10;
	printf("%d %d %d\n", n, 1, n * n);
	printf("1\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", 1);
	}
	puts("");
	for (int i = 2; i <= n; i++)
	{
		printf("%d %d\n", i, rand() % (i - 1) + 1);
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", 1);
	}
	puts("");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			printf("1 %d %d\n", i, j);
		}
	}
	puts("");
	return 0;
}
