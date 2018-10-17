#include <cstdio>

int n;
char s[2000000];
int nextx[2000000], minx[2000000];
long long ans;

int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	ans = 0;
	minx[0] = minx[1] = 0;
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
		minx[i] = minx[j] == 0 ? j : minx[j];
		ans += (minx[i] != 0) * (2 * (i - minx[i]) >= i) * (i - minx[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
