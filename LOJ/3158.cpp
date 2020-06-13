#include <cstdio>
#include <algorithm>
#include <queue>
#include <cassert>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 200000 + 10;
int T, n, K, L;
int x[_n], y[_n];
int fx[_n], fy[_n];
int rest, cnt;
std::priority_queue<std::pair<int, int> > A, B, RA, RB, M;
long long ans;

int main()
{
#ifdef ONLINE_JUDGE
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &n, &K, &L);

		//init
		while (! A.empty()) A.pop();
		while (! B.empty()) B.pop();
		while (! RA.empty()) RA.pop();
		while (! RB.empty()) RB.pop();
		while (! M.empty()) M.pop();
		for (int i = 1; i <= n; i++)
		{
			fx[i] = fy[i] = 0;
		}

		for (int i = 1; i <= n; i++)
		{
			x[i] = read();
		}
		for (int i = 1; i <= n; i++)
		{
			y[i] = read();
		}

		for (int i = 1; i <= n; i++)
		{
			A.push(std::make_pair(x[i], i));
			B.push(std::make_pair(y[i], i));
			M.push(std::make_pair(x[i] + y[i], i));
		}

		ans = 0;
		rest = K - L;
		cnt = K;

		while (cnt)
		{
			while (! M.empty() && (fx[M.top().second] || fy[M.top().second])) M.pop();
//			while (! A.empty() && (fx[A.top().second] || fy[A.top().second])) A.pop();
//			while (! B.empty() && (fx[B.top().second] || fy[B.top().second])) B.pop();
			while (! A.empty() && fx[A.top().second]) A.pop();
			while (! B.empty() && fy[B.top().second]) B.pop();
			while (! RA.empty() && fx[RA.top().second]) RA.pop();
			while (! RB.empty() && fy[RB.top().second]) RB.pop();

			if (rest)
			{
				int left = A.top().second;
				A.pop();
				int right = B.top().second;
				B.pop();
				cnt--;
				if (left == right)
				{
					fx[left] = fy[right] = 1;
					ans = ans + x[left] + y[right];
				}
				else
				{
					fx[left] = 1;
					fy[right] = 1;
					if (fy[left] == 1)
					{
						rest++;
					}
					if (fx[right] == 1)
					{
						rest++;
					}
					if (fy[left] == 0)
					{
						RB.push(std::make_pair(y[left], left));
					}
					if (fx[right] == 0)
					{
						RA.push(std::make_pair(x[right], right));
					}
					ans = ans + x[left] + y[right];
					rest--;
				}
			}
			else
			{
				long long mL = M.empty() ? -INF : M.top().first;
				long long mA = (A.empty() ? -INF : A.top().first) + (RB.empty() ? -INF : RB.top().first);
				long long mB = (RA.empty() ? -INF : RA.top().first) + (B.empty() ? -INF : B.top().first);
				long long mR = (RA.empty() ? -INF : RA.top().first) + (RB.empty() ? -INF : RB.top().first);
				long long mx = std::max(std::max(mR, mL), std::max(mA, mB));
				cnt--;
				if (mR == mx)
				{
					int left = RA.top().second;
					RA.pop();
					int right = RB.top().second;
					RB.pop();
					fx[left] = 1;
					fy[right] = 1;
					ans = ans + x[left] + y[right];
					rest++;
				}
				else
				{
					if (mL == mx)
					{
						int idx = M.top().second;
						M.pop();
						fx[idx] = fy[idx] = 1;
						ans = ans + x[idx] + y[idx];
					}
					else
					{
						if (mA == mx)
						{
							int left = A.top().second;
							A.pop();
							int right = RB.top().second;
							RB.pop();
							fx[left] = 1;
							fy[right] = 1;
							assert(fy[left] == 0);
							if (fy[left] == 0)
							{
								RB.push(std::make_pair(y[left], left));
							}
							ans = ans + x[left] + y[right];
						}
						else
						{
							int left = RA.top().second;
							RA.pop();
							int right = B.top().second;
							B.pop();
							fx[left] = 1;
							fy[right] = 1;
							assert(fx[right] == 0);
							if (fx[right] == 0)
							{
								RA.push(std::make_pair(x[right], right));
							}
							ans = ans + x[left] + y[right];
						}
					}
				}
			}
/*			puts("#");
			for (int i = 1; i <= n; i++)
			{
				printf("..%d %d\n", fx[i], fy[i]);
			}*/
		}


		printf("%lld\n", ans);
	}
	return 0;
}
