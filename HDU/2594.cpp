#include <cstdio>
#include <cstring>
#include <algorithm>

char s[100000], t[100000];
int n, m;
int nextx[100000], extend[100000];
int ans;

void getnextx()
{
	int pos = -1, last = -1;
	for (int i = 2; i <= m; i++)
	{
		int k = (pos == -1 || i > last) ? 0 : std::min(nextx[i - pos + 1], last - i + 1);
		while (k + 1 <= n && t[i + k] == t[k + 1])
		{
			k++;
		}
		nextx[i] = k;
		if (i + nextx[i] - 1 > last)
		{
			pos = i;
			last = i + nextx[i] - 1;
		}
	}
}

int main()
{
	while (scanf("%s%s", s + 1, t + 1) == 2)
	{
		n = strlen(s + 1);
		m = strlen(t + 1);
		getnextx();
		int pos = -1, last = -1;
		for (int i = 1; i <= m; i++)
		{
			int k = (pos == -1 || i > last) ? 0 : std::min(nextx[i - pos + 1], last - i + 1);
			while (k + 1 <= n && i + k <= m && t[i + k] == s[k + 1])
			{
				k++;
			}
			extend[i] = k;
			if (i + extend[i] - 1 > last)
			{
				pos = i;
				last = i + extend[i] - 1;
			}
		}
		ans = 0;
		for (int i = 1; i <= m; i++)
		{
			if (i + extend[i] - 1 == m)
			{
				ans = extend[i];
				break;
			}
		}
		if (ans)
		{
			for (int i = 1; i <= ans; i++)
			{
				printf("%c", s[i]);
			}
			printf(" ");
		}
		printf("%d\n", ans);
	}
	return 0;
}
