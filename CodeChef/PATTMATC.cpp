#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

int T;
char S[200000], t[200000];
int n, m;
int len[600];
std::string s[600];
std::vector<int> fail[600];
std::vector<int> v[600];
int last;
int ans[200000];
int now[600];

void getfail(std::string s, std::vector<int> &fail, int n)
{
	fail.resize(n + 5);
	int j = 0;
	fail[0] = fail[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		fail[i] = j;
	}
}

void calc(std::string s, std::vector<int> &v, std::vector<int> fail, int n, int m)
{
	v.clear();
	int j = 0;
	for (int i = 1; i <= m; i++)
	{
		while (j && s[j + 1] != t[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == t[i])
		{
			j++;
		}
		if (j == n)
		{
			v.push_back(i);
//			t[0]++;
//			t[t[0]] = i;
			j = fail[j];
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(len, 0, sizeof(len));
		scanf("%s", S + 1);
		n = strlen(S + 1);
		scanf("%s", t + 1);
		m = strlen(t + 1);
		for (int i = 1; i <= n / 2; i++)
		{
			std::swap(S[i], S[n - i + 1]);
		}
		for (int i = 1; i <= m / 2; i++)
		{
			std::swap(t[i], t[m - i + 1]);
		}
		last = 1;
		s[last] = " ";
		for (int i = 1; i <= n; i++)
		{
			if (S[i] == '*')
			{
//				if (len[last])
				if (s[last].length() != 1)
				{
					last++;
					s[last] = " ";
				}
			}
			else
			{
//				len[last]++;
//				s[last][len[last]] = S[i];
				s[last] += S[i];
			}
		}
		if (s[last].length() == 1)
		{
			last--;
		}
		if (last == 0)
		{
			for (int i = 1; i <= m; i++)
			{
				printf("%d ", i);
			}
			puts("");
			continue;
		}
		for (int i = 1; i <= last; i++)
		{
			len[i] = s[i].length() - 1;
		}
		for (int i = 1; i <= last; i++)
		{
			getfail(s[i], fail[i], len[i]);
			calc(s[i], v[i], fail[i], len[i], m);
		}
		for (int i = 1; i <= last; i++)
		{
			now[i] = -1;
		}
		for (int i = 1; i <= m; i++)
		{
			int nx = last;
			int pre = i;
			while (nx > 0)
			{
				bool flag = false;
				while (now[nx] != (int)v[nx].size() - 1 && v[nx][now[nx] + 1] <= pre)
				{
					now[nx]++;
					flag = true;
				}
				pre = v[nx][now[nx]] - len[nx];
				nx--;
				if (! flag)
				{
					break;
				}
			}
			ans[m - i + 1] = now[1] == -1 ? -1 : (m - (v[1][now[1]] - len[1] + 1) + 1);
		}
		for (int i = 1; i <= m; i++)
		{
			printf("%d ", ans[i]);
		}
		puts("");
	}
	return 0;
}
