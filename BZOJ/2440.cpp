#include <cstdio>
#include <cmath>

int primenum;
int prime[600000];
bool flag[600000];
int mu[600000];
int T, k;

long long calc(long long x)
{
	long long ans = 0;
	int top = sqrt(x);
	for (int i = 1; i <= sqrt(x); i++)
	{
		ans += (long long)mu[i] * (x / i / i);
	}
	return ans;
}

int main()
{
	mu[1] = 1;
	for (int i = 2; i <= 500000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 500000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &k);
		long long l = 1;
		long long r = 10000000000;
		while (l < r)
		{
			long long mid = l + r >> 1;
			if (calc(mid) >= k)
			{
				r = mid;
			}
			else
			{
				l = mid + 1;
			}
		}
		printf("%lld\n", l);
	}
	return 0;
}
