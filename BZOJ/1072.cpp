#include <cstdio>
#include <cstring>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _cas = 1024 + 10, _d = 1000 + 10;
int T;
int len;
char s[100];
int d;
long long f[_cas][_d];
int cnt[12], mul[12];

long long dfs(int cas, int mod)
{
	if (cas == 0)
	{
		return mod == 0;
	}
	if (f[cas][mod] != -1)
	{
		return f[cas][mod];
	}
	long long ans = 0;
	for (int i = 0; i < 10; i++)
	{
		int least = cas / (i == 0 ? 1 : mul[i - 1]) % (cnt[i] + 1);
		if (least)
		{
			ans += dfs(cas - (i == 0 ? 1 : mul[i - 1]), (mod * 10 + i) % d);
		}
	}
	return f[cas][mod] = ans;
}

int main()
{
	T = read();
	while (T--)
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		d = read();
		for (int i = 0; i < 10; i++)
		{
			cnt[i] = 0;
		}
		for (int i = 1; i <= len; i++)
		{
			cnt[s[i] - '0']++;
		}
		mul[0] = (cnt[0] + 1);
		for (int i = 1; i < 10; i++)
		{
			mul[i] = mul[i - 1] * (cnt[i] + 1);
		}
		for (int i = 0; i < mul[9]; i++)
		{
			for (int j = 0; j < d; j++)
			{
				f[i][j] = -1;
			}
		}
		printf("%lld\n", dfs(mul[9] - 1, 0));
	}
	return 0;
}