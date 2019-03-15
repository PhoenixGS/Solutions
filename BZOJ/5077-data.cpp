#include <cstdio>
#include <ctime>
#include <cstdlib>

int n, m;
long long c0;
int f[1000000];

int main()
{
	srand(time(NULL));
	n = 10;
	m = 10;
	c0 = (long long)10000000 * 100000000;
	printf("%d %d %lld\n", n, m, c0);
	for (int i = 2; i <= n; i++)
	{
		int father = rand() % (i - 1);
		if (f[father])
		{
			printf("%d %d %d\n", 1, father, f[father]);
		}
		else
		{
			f[i - 1] = i - 1;
			printf("%d %d %d %d %d %d %d\n", 0, father, f[i - 1], rand() % 100, rand() % 100, rand() % 100, rand() % 100);
		}
	}
	for (int i = 1; i <= 100; i++)
	{
		printf("%d %d\n", rand() % n, rand());
	}
	return 0;
}
