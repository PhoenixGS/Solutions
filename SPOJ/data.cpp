#include <cstdio>
#include <ctime>
#include <cstdlib>

int n, q;

int main()
{
	srand(time(NULL));
	n = 100000;
	printf("%d\n", n);
	for (int i = 2; i <= n; i++)
	{
		printf("%d %d\n", rand() % (i - 1) + 1, i);
	}
	q = 100000;
	printf("%d\n", q);
	for (int i = 1; i <= q; i++)
	{
		int cas = rand() & 1;
		if (cas)
		{
			printf("0 %d\n", rand() % n + 1);
		}
		else
		{
			printf("1 %d\n", rand() % n + 1);
		}
	}
	return 0;
}
