#include <cstdio>
#include <cstring>

char st[20000];
int nextx[20000];
int ans;
int n, k;
char *s;

void getnextx()
{
	nextx[0] = nextx[1] = 0;
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
	}
}

int main()
{
	scanf("%s", st + 1);
	s = st;
	n = strlen(s + 1);
	scanf("%d", &k);
	ans = 0;
	while (n)
	{
		getnextx();
		int j = 0;
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
			while (j && j + 1 + j > i)
			{
				j = nextx[j];
			}
			ans += (j >= k);
		}
		s++;
		n--;
	}
	printf("%d\n", ans);
	return 0;
}
