#include <cstdio>

void get_prime(long long n)
{
	for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= n; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
}

long long solve(long long n, long long j)
{
	long long ans = g[n] - (j - 1);
	for (int i = j; i <= primenum; i++)
	{
		for (long long t = prime[j], e = 1; t <= n; t = t * prime[j], e++)
		{
			int op = n / t <= knum
		}
	}
}

long long solve(long long n)
{
	long long ans = 0;
	knum = sqrt(n);
	last = 0;
	for (int i = 1, j, t; i <= n; i = j + 1)
	{
		j = n / (n / i);
		t = n / i;
		last++;
		v[last] = t;
		if (t <= knum)
		{
			pos1[t] = last;
		}
		else
		{
			pos2[n / t] = last;
		}
		g[last] = t - 1;
	}
	for (int i = 1; i <= primenum; i++)
	{
		for (int j = 1; j <= last; j++)
		{
			int op = v[last] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
			g[j] = g[j] - (g[op] - (i - 1));
		}
	}
	return solve(n, 1);
}

int main()
{
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}
