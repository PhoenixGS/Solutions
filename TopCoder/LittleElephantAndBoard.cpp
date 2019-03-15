#include <algorithm>

const int M = 1000000007;
const int _m = 2000000 + 10;
int up[_m], down[_m];

class LittleElephantAndBoard
{
	public:
	
	void init()
	{
		up[0] = 1;
		for (int i = 1; i <= 2000000; i++)
		{
			up[i] = (long long)up[i - 1] * i % M;
		}
		down[0] = down[1] = 1;
		for (int i = 2; i <= 2000000; i++)
		{
			down[i] = (long long)(M - M / i) * down[M % i] % M;
		}
		for (int i = 2; i <= 2000000; i++)
		{
			down[i] = (long long)down[i - 1] * down[i] % M;
		}
	}

	int pow_mod(int x, int p, int M)
	{
		int ans = 1;
		int tmp = x;
		while (p)
		{
			if (p & 1)
			{
				ans = (long long)ans * tmp % M;
			}
			tmp = (long long)tmp * tmp % M;
			p >>= 1;
		}
		return ans;
	}

	int calc(int k, int y, int z)
	{
		if (k < 1)
		{
			return 0;
		}
		int ans = 0;
		for (int t = 0; t <= std::min(y, z); t++)
		{
			int a = k - z + t;
			int b = k - y + t;
			int c = y + z - k - 2 * t;
			if (a >= 0 && b >= 0 && c >= 0)
			{
				(ans += (long long)up[k] * down[a] % M * down[b] % M * down[c] % M * pow_mod(2, c, M) % M * up[t + k - 1] % M * down[k - 1] % M * down[t] % M) %= M;
			}
		}
		return ans;
	}

	int getNumber(int m, int R, int G, int B)
	{
		init();

		R = m - R;
		G = m - G;
		B = m - B;
		int ans = 0;
		ans = (ans + calc(R - 1, G, B)) % M;
		ans = (ans + calc(R, G, B)) % M;
		ans = (ans + calc(R, G, B)) % M;
		ans = (ans + calc(R + 1, G, B)) % M;
		return (ans + ans) % M;
	}
};

#ifdef debug
int main()
{
	int m, R, G, B;
	scanf("%d%d%d%d", &m, &R, &G, &B);
	LittleElephantAndBoard Test;
	printf("%d\n", Test.getNumber(m, R, G, B));
	return 0;
}
#endif
