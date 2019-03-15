#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int T;
long long n, k;
<<<<<<< HEAD
long long f[100000];
long long fac[100000];
long long inv[100000];
long long invk[100000];
long long up;
long long ans;
const long long M = 1e9 + 7;

long long pow_mod(long long x, long long p, long long M)
{
	long long tmp = x % M;
	long long ans = 1;
=======
int f[100000];
int fac[100000];
int inv[100000];
int invk[100000];
int pre[100000];
int nextx[100000];
int up;
int ans;
const int M = 1e9 + 7;

int pow_mod(int x, int p)
{
	int tmp = x % M;
	int ans = 1;
>>>>>>> 984c9bc947b1ca2134dfae21c5962d44c66cb9c6
	while (p)
	{
		if (p & 1)
		{
<<<<<<< HEAD
			ans = ans * tmp % M;
		}
		tmp = tmp * tmp % M;
=======
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
>>>>>>> 984c9bc947b1ca2134dfae21c5962d44c66cb9c6
		p >>= 1;
	}
	return ans;
}

int main()
{
	T = read();
	fac[0] = 1;
<<<<<<< HEAD
	for (int i = 1; i <= 50000 + 1; i++)
	{
		fac[i] = (fac[i - 1] * i) % M;
	}
	inv[0] = 1;
	inv[1] = 1;
	for (int i = 2; i <= 50000 + 1; i++)
	{
		inv[i] = (-inv[M % i] * ((M / i) % M) % M + M) % M;
	}
	invk[0] = 1;
	for (int i = 1; i <= 50000 + 1; i++)
	{
		invk[i] = invk[i - 1] * inv[i] % M;
	}
	while (T--)
	{
		printf("X");
		n = read();
		k = read();
		printf("X");
		for (int i = 1; i <= k + 1; i++)
		{
			f[i] = (f[i - 1] + pow_mod(i * 1ll, k, M)) % M;
		}
		if (n <= k + 1)
		{
			printf("%lld\n", f[n]);
			return 0;
		}
		printf("X");
		up = 1;
		ans = 0;
		for (int i = 0; i <= k + 1; i++)
		{
			up = (up * ((n - i) % M)) % M;
		}
		for (int i = 0; i <= k + 1; i++)
		{
			long long inv1 = inv[(n - i) % M];
			long long inv2 = invk[i] * invk[k - i + 1] % M;
			long long sign = ((k - i + 1) & 1) ? -1 : 1;
			(ans += sign * inv1 * inv2 % M * f[i] % M * up % M) %= M;
		}
		ans = (ans + M) % M;
		printf("%lld\n", ans);
=======
	for (int i = 1; i <= 50000 + 2; i++)
	{
		fac[i] = ((long long)fac[i - 1] * i) % M;
	}
	inv[0] = 1;
	inv[1] = 1;
	for (int i = 2; i <= 50000 + 2; i++)
	{
		inv[i] = (-(long long)inv[M % i] * (M / i) % M + M) % M;
	}
	invk[0] = 1;
	for (int i = 1; i <= 50000 + 2; i++)
	{
		invk[i] = (long long)invk[i - 1] * inv[i] % M;
	}
	while (T--)
	{
		n = read();
		n = n % M;
		k = read();
		for (int i = 1; i <= k + 2; i++)
		{
			f[i] = f[i - 1] + pow_mod(i, k);
			f[i] -= f[i] >= M ? M : 0;
		}
		if (n <= k + 2)
		{
			printf("%d\n", f[n]);
			continue;
		}
		up = 1;
		ans = 0;
		for (int i = 0; i <= k + 2; i++)
		{
			up = ((long long)up * ((n - i) % M)) % M;
		}
		pre[0] = 1;
		for (int i = 1; i <= k + 2; i++)
		{
			pre[i] = (long long)pre[i - 1] * (n - i) % M;
		}
		nextx[k + 3] = 1;
		for (int i = k + 2; i >= 0; i--)
		{
			nextx[i] = (long long)nextx[i + 1] * (n - i) % M;
		}
		for (int i = 1; i <= k + 2; i++)
		{
			int inv = (long long)invk[i - 1] * invk[k - i + 2] % M;
			int sign = ((k - i + 2) & 1) ? -1 : 1;
			ans += (long long)sign * inv % M * f[i] % M * pre[i - 1] % M * nextx[i + 1] % M;
			ans -= ans >= M ? M : 0;
			ans += ans <= -M ? M : 0;
		}
		ans = (ans + M) % M;
		printf("%d\n", ans);
>>>>>>> 984c9bc947b1ca2134dfae21c5962d44c66cb9c6
	}
	return 0;
}

<<<<<<< HEAD
=======

>>>>>>> 984c9bc947b1ca2134dfae21c5962d44c66cb9c6
