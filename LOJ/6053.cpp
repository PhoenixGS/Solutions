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
long long g[_knum], h[_knum];
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

long long query(long long x, int j)
{
    if (x <= 1 || prime[j] > x)
    {
        return 0ll;
    }
    int op = x <= knum ? pos1[x] : pos2[n / x];
    long long ans = ((g[op] - h[op]) % M - (prime_sum[j - 1] - (j - 1)) % M) % M;
    ans = (ans + M) % M;
    if (j == 1)
    {
        ans = (ans + 2) % M;
    }
    for (int k = j; k <= primenum && prime[k] * prime[k] <= x; k++)
    {
        for (long long e = 1, t = prime[k]; t * prime[k] <= x; e++, t = t * prime[k])
        {
            ans = (ans + (long long)(prime[k] ^ e) * query(x / t, k + 1) % M) % M;
            ans = (ans + (prime[k] ^ (e + 1))) % M;
        }
    }
    return ans;
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
    long long ans = (query(n, 1) + 1) % M;
    printf("%lld\n", ans);
    return 0;
}