#include <cstdio>
#include <vector>
#include <map>
#include <cmath>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

long long ans;
std::vector<int> vec[300000];
int cnt[1000000];
int n, Q;
int x[300000];
bool flag[1000000];
bool fff[300000];
int primenum;
int prime[300000];
std::map<int, int> map;

void solve(int x, int id)
{
	int tmp = x;
	for (int i = 2; i <= sqrt(x); i++)
	{
		if (tmp % i == 0)
		{
			vec[id].push_back(i);
			while (tmp % i == 0)
			{
				tmp /= i;
			}
		}
	}
	if (tmp != 1)
	{
		vec[id].push_back(tmp);
	}
}

void dfs(int id, int now, int cc, int cas, int mul)
{
	if (now == vec[id].size())
	{
		if (cas == -1)
		{
			cnt[mul] += cas;
		}
		ans += ((cc & 1) ? -1 : 1) * cas * cnt[mul];
		if (cas == 1)
		{
			cnt[mul] += cas;
		}
		return;
	}
	dfs(id, now + 1, cc, cas, mul);
	dfs(id, now + 1, cc + 1, cas, mul * vec[id][now]);
}

int main()
{
	for (int i = 2; i <= 100000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			map[i] = primenum;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 100000; j++)
		{
			flag[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
	n = read();
	Q = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
		solve(x[i], i);
	}
	for (int i = 1; i <= Q; i++)
	{
		int kkk = read();
		if (fff[kkk])
		{
			dfs(kkk, 0, 0, -1, 1);
		}
		else
		{
			dfs(kkk, 0, 0, 1, 1);
		}
		fff[kkk] = ! fff[kkk];
		printf("%lld\n", ans);
	}
	return 0;
}
