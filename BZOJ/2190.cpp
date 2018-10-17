#include <cstdio>

int n;
int phi[100000];
int primenum;
int prime[100000];
int flag[100000];

int main()
{
	scanf("%d", &n);
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= n; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		ans = ans + phi[i];
	}
	printf("%d\n", ans * 2 + 1);
	return 0;
}
