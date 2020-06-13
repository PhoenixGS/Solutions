#include <cstdio>
#include <cstring>

const int _n = 500000 + 10;
int n;
char s[_n];
int lastans;

struct PAM
{
	int knum, last;
	int to[_n][26], len[_n], pre[_n], cnt[_n];

	PAM()
	{
		len[0] = 0;
		pre[0] = 1;
		len[1] = -1;
		pre[1] = 0;
		last = 0;
		knum = 1;
	}

	void extend(int idx)
	{
		int u = last;
		while (s[idx - len[u] - 1] != s[idx])
		{
			u = pre[u];
		}
		if (! to[u][s[idx] - 'a'])
		{
			knum++;
			len[knum] = len[u] + 2;
			int w = pre[u];
			while (s[idx - len[w] - 1] != s[idx])
			{
				w = pre[w];
			}
			pre[knum] = to[w][s[idx] - 'a'];
			cnt[knum] = cnt[pre[knum]] + 1;
			to[u][s[idx] - 'a'] = knum;
		}
		last = to[u][s[idx] - 'a'];
	}
};

PAM PAM;

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int lastans = 0;
	for (int i = 1; i <= n; i++)
	{
		s[i] = (s[i] - 'a' + lastans) % 26 + 'a';
		PAM.extend(i);
		lastans = PAM.cnt[PAM.last];
		printf("%d ", lastans);
	}
	puts("");
	return 0;
}
