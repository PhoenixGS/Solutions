#include <cstdio>
#include <cstring>
#include <algorithm>

int T, n;
char s[200000];
int nextx[200000];
int ans1, ans2, ans3;
int cas;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s);
		n = strlen(s);
		nextx[0] = n;
		int pos = -1, last = -1;
		for (int i = 1; i < n; i++)
		{
			int k = (pos == -1 || i > last) ? 0 : std::min(nextx[i - pos], last - i + 1);
			while (k < n && s[k] == s[(i + k) % n])
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
		ans1 = ans2 = ans3 = 0;
		for (int i = 0; i < n; i++)
		{
			if (nextx[i] == n)
			{
				ans2++;
			}
			else
			{
				if (s[(i + nextx[i]) % n] > s[nextx[i]])
				{
					ans3++;
				}
				else
				{
					ans1++;
				}
			}
		}
		cas++;
		printf("Case %d: %d %d %d\n", cas, ans1 / ans2, ans2 / ans2, ans3 / ans2);
	}
	return 0;
}
