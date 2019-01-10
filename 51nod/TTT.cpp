#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;

const int N=50005;
const int MOD=1000000007;

int k,a[N],ny[N],pow[N],p[N],q[N];
LL n;

int ksm(int x,int y)
{
    int ans=1;
    while (y)
    {
        if (y&1) ans=(LL)ans*x%MOD;
        x=(LL)x*x%MOD;y>>=1;
    }
    return ans;
}

int solve(LL x)
{
    if (x<=k+2) return a[x];
    x%=MOD;
    int w=ksm(pow[k+2],MOD-2);LL ans=0;
    p[0]=q[k+3]=1;
    for (int i=1;i<=k+2;i++) p[i]=(LL)p[i-1]*(x-i)%MOD;
    for (int i=k+2;i>=1;i--) q[i]=(LL)q[i+1]*(x-i)%MOD;
    for (int i=1;i<=k+2;i++)
    {
        (ans+=(LL)a[i]*w%MOD*p[i-1]%MOD*q[i+1])%=MOD;
        w=(LL)w*(i-k-2)%MOD*ny[i]%MOD;
    }
    ans+=ans<0?MOD:0;
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for (int i=1;i<=50002;i++) ny[i]=ksm(i,MOD-2);
    pow[1]=1;
    for (int i=2;i<=50002;i++) pow[i]=(LL)pow[i-1]*(1-i)%MOD;
    while (T--)
    {
        scanf("%lld%d",&n,&k);
        for (int i=1;i<=k+2;i++) a[i]=a[i-1]+ksm(i,k),a[i]-=a[i]>=MOD?MOD:0;
        printf("%d\n",solve(n));
    }
    return 0;
}
