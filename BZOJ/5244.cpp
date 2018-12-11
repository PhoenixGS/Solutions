#include <cstdio>

void get_prime(int n)
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

unsigned long long solve(long long n)
{
	knum = sqrt(n);
	last = 0;
	for (long long i = 1, j, t; i <= n; i = j + 1)
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
	}
	for (int i = 2; i <= last; i++)
	{
		g[i] = (i & 1) ? ((i + 1) / 2 * i - 1) : (i / 2 * (i + 1) - 1);
	}
	for (int i = 1; i <= primenum; i++)
	{
		for (int j = 1; j <= last && prime[i] * prime[i] <= v[j]; j++)
		{
						int op = v[j] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
			g[j] = g[j] - (g[op] - (j - 1));
		}
	}
	ans = 0;
	query(n, 1);
	return ans;
}

int main()
{
	get_prime(100000);
	long long l, r;
	scanf("%lld %lld", &l, &r);
	printf("%llu\n", solve(r) - solve(l - 1));
	return 0;
}
