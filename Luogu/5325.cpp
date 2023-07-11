#include <cstdio>
#include <cmath>

const int M = 1000000007, inv2 = 500000004, inv3 = 333333336;
const int _knum = 200000 + 10;
long long n;
long long knum;
int flag[_knum];
int last;
long long v[_knum];
int primenum;
long long prime[_knum], prime_sum[_knum], prime_sum2[_knum];
long long f[_knum], g[_knum], h[_knum];
long long pos1[_knum], pos2[_knum];

void calc_prime(int n)
{
for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			prime_sum[primenum] = (prime_sum[primenum - 1] + i) % M;
			prime_sum2[primenum] = (prime_sum2[primenum - 1] + (long long)i * i % M) % M;
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

long long query()
{
	for (int i = 1; i <= last; i++)
	{
		f[i] = (h[i] - g[i]) % M;
		f[i] = (f[i] + M) % M;
	}
	for (int i = primenum; i >= 1; i--)
	{
		for (int j = 1; j <= last && prime[i] * prime[i] <= v[j]; j++)
		{
			for (long long e = 1, t = prime[i]; t * prime[i] <= v[j]; e++, t = t * prime[i])
			{
				int op = v[j] / t <= knum ? pos1[v[j] / t] : pos2[n / (v[j] / t)];
				long long tmp = (prime_sum2[i] - prime_sum[i]) % M;
				long long z = t % M, zz = t % M * prime[i] % M;
				f[j] = (f[j] + z * (z - 1) % M * (f[op] - tmp) % M + zz * (zz - 1) % M) % M;
//				f[j] = (f[j] + t % M * ((t % M) - 1) % M * (f[op] - tmp) % M + (t % M * prime[i] % M) * (t % M * prime[i] % M - 1) % M) % M;
			}
		}
	}
	return (f[1] + 1) % M;
}

int main()
{
	scanf("%lld", &n);
	knum = sqrt(n);

	calc_prime(knum);

	last = 0;
	for (long long i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		last++;
		v[last] = n / i;
		long long t = n / i;
		t = t % M;
		g[last] = (long long)(t + 1) * t / 2 - 1;
		h[last] = (long long)t * (t + 1) % M * (2 * t + 1) % M * inv2 % M * inv3 % M - 1;
		if (n / i <= knum)
		{
			pos1[n / i] = last;
		}
		else
		{
			pos2[j] = last;
		}
	}
	for (int i = 1; i <= primenum; i++)
	{
		for (int j = 1; j <= last; j++)
		{
			if ((long long)prime[i] * prime[i] > v[j])
			{
				break;
			}
			int op = v[j] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
			g[j] = (g[j] - (long long)prime[i] * (g[op] - prime_sum[i - 1]) % M) % M;
			h[j] = (h[j] - (long long)prime[i] * prime[i] % M * (h[op] - prime_sum2[i - 1]) % M) % M;
		}
	}
	long long ans = query();
	printf("%lld\n", ans);
	return 0;
}

