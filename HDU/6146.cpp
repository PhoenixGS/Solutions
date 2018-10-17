#include <cstdio>

long long f[20000];
int T;
const long long M = 1e9 + 7;

long long pow_mod(long long x, long long p, long long M)
{
	long long ans = 1;
	long long tmp = x % M;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * tmp % M;
		}
		tmp = tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int main()
{
	f[0] = 1;
	f[1] = 1;
	for (int i = 3; i <= 10000; i++)
	{
		f[i] = (2 * f[i - 1] + 4 * f[i - 2] + 2 * pow_mod(2, i - 2, M)) % M;
	}
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
	}
	return 0;
}
