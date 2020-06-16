#include <cstdio>
#include <unordered_map>

long long read()
{
    char last = '+', ch = getchar();
    while (ch < '0' || ch > '9') last = ch, ch = getchar();
    long long tmp = 0;
    while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
    if (last == '-') tmp = -tmp;
    return tmp;
}

const int lim = 5000000, _l = lim + 10;
int T;
int flag[_l], phi[_l], mu[_l];
long long sphi[_l], smu[_l];
int primenum;
int prime[_l];
std::unordered_map<int, long long> mphi, mmu;

inline long long Sphi(int n)
{
	if (n <= lim)
	{
		return sphi[n];
	}
	if (mphi[n])
	{
		return mphi[n];
	}
	long long ans = (long long)n * (n + 1) / 2;
	for (int l = 2, r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		ans -= (r - l + 1) * Sphi(n / l);
	}
	return mphi[n] = ans;
}

inline long long Smu(int n)
{
	if (n <= lim)
	{
		return smu[n];
	}
	if (mmu[n])
	{
		return mmu[n];
	}
	long long ans = 1;
	for (int l = 2, r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		ans -= (r - l + 1) * Smu(n / l);
	}
	return mmu[n] = ans;
}

int main()
{
	//init
	mu[1] = 1;
	phi[1] = 1;
	for (int i = 2; i <= lim; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= lim; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				phi[i * prime[j]] = phi[i] * prime[j];
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= lim; i++)
	{
		smu[i] = smu[i - 1] + mu[i];
		sphi[i] = sphi[i - 1] + phi[i];
	}

	int T = read();
	while (T--)
	{
		int n = read();
		printf("%lld %lld\n", Sphi(n), Smu(n));
	}
	return 0;
}
