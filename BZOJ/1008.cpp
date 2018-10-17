#include <cstdio>
 
typedef long long ll;
 
const ll M = 100003;
 
ll read()
{
    char last = '+', ch = getchar();
    while (ch < '0' || ch > '9') last = ch, ch = getchar();
    ll tmp = 0;
    while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
    if (last == '-') tmp = -tmp;
    return tmp;
}
 
ll pow_mod(ll x, ll p)
{
    ll ans = 1;
    ll tmp = x % M;
    while (p)
    {
        if (p & 1)
        {
            ans = ans * tmp % M;
        }
        tmp = tmp * tmp % M;
        p >>= 1;
    }
    return ans;
}
 
int main()
{
    ll m, n;
    m = read();
    n = read();
    printf("%lld\n", ((pow_mod(m, n) - m % M * pow_mod(m - 1, n - 1) % M) % M + M) % M);
    return 0;
}
