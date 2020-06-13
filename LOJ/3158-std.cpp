#include <cstdio>
#include <algorithm>
#include <queue>
#include <cctype>

#define fi first
#define se second
#define mp std::make_pair
typedef long long LL;
typedef std::pair<int, int> pii;
typedef std::priority_queue<pii> PQ;
const int MN = 200005;

inline void read(int &x) {
	x = 0; static char ch;
	while (!isdigit(ch = getchar())) ;
	while (x = x * 10 + (ch & 15), isdigit(ch = getchar()));
}
inline void write(LL x) {
	static char st[15];
	static char *t = st;
	while (x) *t++ = (x % 10) | 48, x /= 10;
	while (t != st) putchar(*--t);
	putchar('\n');
}

int N, K, L;
int A[MN], B[MN];
bool vA[MN], vB[MN];
PQ A0, B0, A1, B1, C;
LL Ans;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Ans = 0;
		while (!A0.empty()) A0.pop();
		while (!B0.empty()) B0.pop();
		while (!A1.empty()) A1.pop();
		while (!B1.empty()) B1.pop();
		while (!C.empty()) C.pop();
		read(N), read(K), read(L);
		for (int i = 1; i <= N; ++i) read(A[i]);
		for (int i = 1; i <= N; ++i) read(B[i]);
		for (int i = 1; i <= N; ++i) {
			vA[i] = vB[i] = 0;
			A0.push(mp(A[i], i));
			B0.push(mp(B[i], i));
			C.push(mp(A[i] + B[i], i));
		}
		int left = K - L;
		for (int cnt = 1; cnt <= K; ++cnt) {
			while (vA[A0.top().se]) A0.pop();
			while (vB[B0.top().se]) B0.pop();
			if (left) {
				pii a = A0.top(), b = B0.top();
				A0.pop(), B0.pop();
				Ans += a.fi + b.fi;
				int ap = a.se, bp = b.se;
				vA[ap] = vB[bp] = 1;
				if (ap == bp) C.pop();
				else {
					--left;
					if (vB[ap]) ++left, A1.pop();
					else B1.push(mp(B[ap], ap));
					if (vA[bp]) ++left, B1.pop();
					else A1.push(mp(A[bp], bp));
				}
			}
			else {
				pii c0 = C.empty() ? mp(0, 0) : C.top();
				while (vA[c0.se] || vB[c0.se])
					C.pop(), c0 = C.empty() ? mp(0, 0) : C.top();
				pii a0 = A0.top(), b0 = B0.top();
				pii a1 = A1.empty() ? mp(-b0.fi, 0) : A1.top();
				pii b1 = B1.empty() ? mp(-a0.fi, 0) : B1.top();
				int a = a1.fi + b0.fi;
				int b = b1.fi + a0.fi;
				if (c0.fi >= a && c0.fi >= b)
					Ans += c0.fi, vA[c0.se] = vB[c0.se] = 1;
				else if (a >= b) {
					Ans += a;
					A1.pop(), B0.pop(), vA[a1.se] = vB[b0.se] = 1;
					if (b1.se == b0.se) B1.pop(), ++left;
					else A1.push(mp(A[b0.se], b0.se));
				}
				else {
					Ans += b;
					B1.pop(), A0.pop(), vB[b1.se] = vA[a0.se] = 1;
					if (a1.se == a0.se) A1.pop(), ++left;
					else B1.push(mp(B[a0.se], a0.se));
				}
			}
		} 
		for (int i = 1; i <= N; i++)
		{
			printf("%d %d\n", vA[i], vB[i]);
		}
		write(Ans);
	}
	return 0;
}
