#include <cstdio>
#include <cmath>

const int M = 1000000007;
const int _knum = 1000000 + 10;
long long n;
long long knum;
int flag[_knum];
int last;
long long v[_knum];
int primenum;
long long prime[_knum], prime_sum[_knum];
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
		f[i] = (g[i] - h[i] + (v[i] >= 2 ? 2 : 0)) % M;
		f[i] = (f[i] + M) % M;
	}
	for (int i = primenum; i >= 1; i--)
	{
		for (int j = 1; j <= last && prime[i] * prime[i] <= v[j]; j++)
		{
			for (long long e = 1, t = prime[i]; t * prime[i] <= v[j]; e++, t = t * prime[i])
			{
				int op = v[j] / t <= knum ? pos1[v[j] / t] : pos2[n / (v[j] / t)];
				long long tmp = ((prime_sum[i] - i + (v[j] >= 2 ? 2 : 0)) % M + M) % M;
				f[j] = (f[j] + (prime[i] ^ e) * (f[op] - tmp) % M + (prime[i] ^ (e + 1)) % M) % M;
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
        h[last] = t - 1;
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
            g[j] = (g[j] + M) % M;
            h[j] = (h[j] - (h[op] - (i - 1)) % M) % M;
            h[j] = (h[j] + M) % M;
        }
    }
    long long ans = query();
    printf("%lld\n", ans);
    return 0;
}
