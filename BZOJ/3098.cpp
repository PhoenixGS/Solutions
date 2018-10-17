#include <cstdio>
#include <cstdlib>

int main()
{
	printf("100000 20\n");
	for (int i = 1; i <= 100000; i++)
	{
		printf("%c", rand() % 26 + 'a');
	}
	puts("");
	return 0;
}
