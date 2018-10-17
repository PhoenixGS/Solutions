#include <cstdio>

int pre, cnt, n, x;

int main()
{
	pre = 0;
	cnt = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if (x == pre)
		{
			cnt++;
		}
		else
		{
			if (cnt)
			{
				cnt--;
			}
			else
			{
				pre = x;
				cnt = 1;
			}
		}
	}
	printf("%d\n", pre);
	return 0;
}
