#include <cstdio>
#include <cstring>

const int _n = 1000000 + 10;
int n, m;
char s[_n], t[_n];
int f[_n];
int ans;

void getf()
{
	int now = 0;
	f[1] = 0;
	for (int i = 2; i <= m; i++)
	{
		while (now && t[now + 1] != t[i])
		{
			now = f[now];
		}
		if (t[now + 1] == t[i])
		{
			now++;
		}
		f[i] = now;
	}
}

void calc()
{
	int now = 0;
	for (int i = 1; i <= n; i++)
	{
		while (now && t[now + 1] != s[i])
		{
			now = f[now];
		}
		if (t[now + 1] == s[i])
		{
			now++;
			if (now == m)
			{
				ans++;
				now = f[now];
			}
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	scanf("%s", t + 1);
	m = strlen(t + 1);
	getf();
	calc();
	printf("%d\n", ans);
	return 0;
}
