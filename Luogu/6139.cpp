#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int _s = 1000000 + 10;
int n;
char s[_s];

namespace Trie
{
	int knum;
	int ch[_s][26], pos[_s];

	void init()
	{
		knum = 1;
	}

	void insert(char * s)
	{
		int len = strlen(s + 1);
		int u = 1;
		for (int i = 1; i <= len; i++)
		{
			if (! ch[u][s[i] - 'a'])
			{
				knum++;
				ch[u][s[i] - 'a'] = knum;
			}
			u = ch[u][s[i] - 'a'];
		}
	}
}

namespace SAM
{
	int knum;
	int to[2 * _s][26], pre[2 * _s], len[2 * _s];
	std::queue<int> que;

	void init()
	{
		knum = 1;
	}

	int extend(int c, int last)
	{
		knum++;
		int u = last;
		int v = knum;
		last = knum;
		len[v] = len[u] + 1;
		for (; u && ! to[u][c]; u = pre[u])
		{
			to[u][c] = v;
		}
		if (! u)
		{
			pre[v] = 1;
			return last;
		}
		int w = to[u][c];
		if (len[u] + 1 == len[w])
		{
			pre[v] = w;
			return last;
		}
		knum++;
		int neww = knum;
		pre[neww] = pre[w];
		len[neww] = len[u] + 1;
		for (int i = 0; i < 26; i++)
		{
			to[neww][i] = to[w][i];
		}
		pre[w] = pre[v] = neww;
		for (; u && to[u][c] == w; u = pre[u])
		{
			to[u][c] = neww;
		}
		return last;
	}

	void build()
	{
		Trie::pos[1] = 1;
		que.push(1);
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			for (int i = 0; i < 26; i++)
			{
				int v = Trie::ch[u][i];
				if (v != 0)
				{
					Trie::pos[v] = extend(i, Trie::pos[u]);
					que.push(v);
				}
			}
		}
	}

	long long calc()
	{
		long long ans = 0;
		for (int i = 1; i <= knum; i++)
		{
			ans += len[i] - len[pre[i]];
		}
		return ans;
	}
}

int main()
{
	Trie::init();
	SAM::init();

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		Trie::insert(s);
	}
	SAM::build();
	printf("%lld\n", SAM::calc());
	return 0;
}
