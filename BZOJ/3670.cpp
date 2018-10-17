#include <cstdio>
#include <cstring>
#include <algorithm>

const int M = 1000000007;
int T;
int ans;
char s[2000000];
int n;
int nextx[2000000];
int k[2000000];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		k[0] = 0;
		k[1] = 1;
		int j = 0;
		for (int i = 2; i <= n; i++)
		{
			while (j && s[j + 1] != s[i])
			{
				j = nextx[j];
			}
			if (s[j + 1] == s[i])
			{
				j++;
			}
			nextx[i] = j;
			k[i] = k[j] + 1;
		}
		j = 0;
		ans = 1;
		for (int i = 1; i <= n; i++)
		{
			while (j && s[j + 1] != s[i])
			{
				j = nextx[j];
			}
			if (s[j + 1] == s[i])
			{
				j++;
			}
			while (j > i / 2)
			{
				j = nextx[j];
			}
			ans = (long long)ans * (k[j] + 1) % M;
		}
		printf("%d\n", ans);
	}
	return 0;
}
