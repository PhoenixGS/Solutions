#include <cstdio>
#include <ctime>
#include <cstdlib>

int n, q;

int main()
{
	srand(time(NULL));
	n = 1000;
	printf("%d\n", n);
	for (int i = 2; i <= n; i++)
	{
		printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand() % 2001 - 1000);
	}
	q = 1000;
	printf("%d\n", q);
	for (int i = 1; i <= q; i++)
	{
		int cas = rand() & 1;
		if (cas)
		{
			printf("A\n");
		}
		else
		{
			printf("C %d\n", rand() % n + 1);
		}
	}
	return 0;
}
