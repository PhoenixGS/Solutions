#include <cstdio>
#include <cmath>
#include <cstring>

int flag[200000];
int primenum;
long long prime[200000];
unsigned long long sum[200000];
unsigned long long g[200000];
int knum;
int last;
long long v[200000];
int pos1[200000], pos2[200000];

void get_prime(int n)
{
	for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			sum[primenum] = sum[primenum - 1] + i;
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
	unsigned long long ans = 0;
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
<<<<<<< HEAD
		g[i] = (i & 1) ? ((i + 1) / 2 * i - 1) : (i / 2 * (i + 1) - 1);
=======
		g[i] = ((v[i] & 1) ? ((v[i] + 1) / 2 * v[i]) : (v[i] / 2 * (v[i] + 1))) - 1;
>>>>>>> bcf38710981f02940a7c31c06cdf0501cb03a467
	}
	for (int i = 1; i <= primenum; i++)
	{
		for (int j = 1; j <= last && prime[i] * prime[i] <= v[j]; j++)
		{
<<<<<<< HEAD
						int op = v[j] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
			g[j] = g[j] - (g[op] - (j - 1));
=======
			int op = v[j] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
			g[j] = g[j] - prime[i] * (g[op] - sum[i - 1]);
			if (j == 1)
			{
				ans += g[op] - sum[i - 1];
			}
>>>>>>> bcf38710981f02940a7c31c06cdf0501cb03a467
		}
	}
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
