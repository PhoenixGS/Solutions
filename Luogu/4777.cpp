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

int n;

long long mul(long long x, long long y, long long M)
{
	return (x * y - (long long)((long double)x / M * y) * M + M) % M;
}

long long extend_gcd(long long a, long long &x, long long b, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long d = extend_gcd(b, x, a % b, y);
	long long t = y;
	y = x - a / b * y;
	x = t;
	return d;
}

int main()
{
	scanf("%d", &n);
	long long n1 = read();
	long long a1 = read();
	long long k1, k2;
	for (int i = 2; i <= n; i++)
	{
		long long n2 = read();
		long long a2 = read();
		long long d = extend_gcd(n1, k1, n2, k2);
		long long nn = n1 / d * n2;
		k1 = mul((a2 - a1) / d, k1, nn);
		k2 = mul((a2 - a1) / d, k2, nn);
		a1 = (a1 + mul(k1, n1, nn)) % nn;
		n1 = nn;
	}
	printf("%lld\n", (a1 % n1 + n1) % n1);
	return 0;
}
