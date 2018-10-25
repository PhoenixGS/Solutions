#include <cstdio>
#include <cstring>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const long long INF = (long long)1000000000 * 1000000000;
const int M = 20120427;
const int _len = 22, _cas = 70000;
int T;
long long l, r;
long long K;
int last;
int trans[60][40][30][25];
int k1[100000], k2[100000], k3[100000], k4[100000];
int cnt1, cnt2, cnt3, cnt4, mul[10];
int len;
int v[_len];
int f[_len][100000], s[_len][100000];
int fx[_len][2], sx[_len][2];
int cc1[12], cc2[12], cc3[12], cc4[12];
int mi[_len];

void init()
{
	last = 0;
	for (long long c1 = 0, w1 = 1; w1 <= INF; c1++, w1 *= 2)
	{
		for (long long c2 = 0, w2 = w1; w2 <= INF; c2++, w2 *= 3)
		{
			for (long long c3 = 0, w3 = w2; w3 <= INF; c3++, w3 *= 5)
			{
				for (long long c4 = 0, w4 = w3; w4 <= INF; c4++, w4 *= 7)
				{
					last++;
					trans[c1][c2][c3][c4] = last;
					k1[last] = c1;
					k2[last] = c2;
					k3[last] = c3;
					k4[last] = c4;
				}
			}
		}
	}
}

std::pair<int, int> dfs(int pos, int cas, int limit, int lead)
{
	int c1 = k1[cas], c2 = k2[cas], c3 = k3[cas], c4 = k4[cas];
	if (pos == 0)
	{
		return std::make_pair(c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0, 0);
	}
	if (! limit && ! lead && f[pos][cas] != -1)
	{
		return std::make_pair(f[pos][cas], s[pos][cas]);
	}
	int top = limit ? v[pos] : 9;
	int ans = 0, anss = 0;
	if (lead)
	{
		std::pair<int, int> tmp = dfs(pos - 1, cas, limit && 0 == top, lead);
		ans = (ans + tmp.first) % M;
		anss = (anss + tmp.second) % M;
	}
	for (int i = 1; i <= top; i++)
	{
		if (c1 >= cc1[i] && c2 >= cc2[i] && c3 >= cc3[i] && c4 >= cc4[i])
		{
			std::pair<int, int> tmp = dfs(pos - 1, trans[c1 - cc1[i]][c2 - cc2[i]][c3 - cc3[i]][c4 - cc4[i]], limit && i == top, 0);
			ans = (ans + tmp.first) % M;
			anss = ((anss + tmp.second) % M + (long long)i * mi[pos - 1] % M * tmp.first % M) % M;
		}
	}
	if (! limit && ! lead)
	{
		f[pos][cas] = ans;
		s[pos][cas] = anss;
	}
	return std::make_pair(ans, anss);
}

int solve(long long x)
{
	if (x == 0)
	{
		return 0;
	}
	len = 0;
	while (x)
	{
		len++;
		v[len] = x % 10;
		x /= 10;
	}
	return dfs(len, trans[cnt1][cnt2][cnt3][cnt4], 1, 1).second;
}

std::pair<int, int> dfsx(int pos, int limit, int lead, int has)
{
	if (pos == 0)
	{
		return std::make_pair(has, 0);
	}
	if (! limit && ! lead && fx[pos][has] != -1)
	{
		return std::make_pair(fx[pos][has], sx[pos][has]);
	}
	int top = limit ? v[pos] : 9;
	int ans = 0, anss = 0;
	for (int i = 0; i <= top; i++)
	{
		std::pair<int, int> tmp = dfsx(pos - 1, limit && i == top, lead && i == 0, has | (! lead && i == 0));
		ans = (ans + tmp.first) % M;
		anss = ((anss + tmp.second) % M + (long long)i * mi[pos - 1] % M * tmp.first % M) % M;
	}
	if (! limit && ! lead)
	{
		fx[pos][has] = ans;
		sx[pos][has] = anss;
	}
	return std::make_pair(ans, anss);
}

int solvex(long long x)
{
	if (x == 0)
	{
		return 0;
	}
	len = 0;
	while (x)
	{
		len++;
		v[len] = x % 10;
		x /= 10;
	}
	return dfsx(len, 1, 1, 0).second;
}

int main()
{
	init();
	mi[0] = 1;
	for (int i = 1; i <= 20; i++)
	{
		mi[i] = (long long)mi[i - 1] * 10 % M;
	}
	for (int i = 0; i < 10; i++)
	{
		int tmp = i;
		while (tmp && tmp % 2 == 0)
		{
			cc1[i]++;
			tmp /= 2;
		}
		while (tmp && tmp % 3 == 0)
		{
			cc2[i]++;
			tmp /= 3;
		}
		while (tmp && tmp % 5 == 0)
		{
			cc3[i]++;
			tmp /= 5;
		}
		while (tmp && tmp % 7 == 0)
		{
			cc4[i]++;
			tmp /= 7;
		}
	}
	memset(f, -1, sizeof(f));
	memset(fx, -1, sizeof(fx));
	T = read();
	while (T--)
	{
		l = read();
		r = read();
		K = read();
		if (K == 0)
		{
			printf("%d\n", ((solvex(r) - solvex(l - 1)) % M + M) % M);
			continue;
		}
		cnt1 = cnt2 = cnt3 = cnt4 = 0;
		while (K && K % 2 == 0)
		{
			cnt1++;
			K /= 2;
		}
		while (K && K % 3 == 0)
		{
			cnt2++;
			K /= 3;
		}
		while (K && K % 5 == 0)
		{
			cnt3++;
			K /= 5;
		}
		while (K && K % 7 == 0)
		{
			cnt4++;
			K /= 7;
		}
		if (K != 1)
		{
			puts("0");
			continue;
		}
		printf("%d\n", ((solve(r) - solve(l - 1)) % M + M) % M);
	}
	return 0;
}