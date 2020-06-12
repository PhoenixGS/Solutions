#include <cstdio>
#include <algorithm>
using namespace std;
#define N 300005
#define oo 1e12
#define ll long long
#define pli pair<ll,int>
#define fi first
#define se second
#define mx(k) max(f[k][0],max(f[k][1],f[k][2]))
int E,n,m,k,x,y,z,head[N];
pli o,f[N][3];
struct ji{
    int nex,to,len;
}edge[N<<1];
pli add(pli x,pli y){
    return make_pair(x.fi+y.fi,x.se+y.se);
}
void add(int x,int y,int z){
    edge[E].nex=head[x];
    edge[E].to=y;
    edge[E].len=z;
    head[x]=E++;
}
void dfs(int k,int fa,ll v){
    f[k][0]=make_pair(0,0);
    f[k][1]=f[k][2]=make_pair(-v,1);
    for(int i=head[k];i!=-1;i=edge[i].nex)
        if (edge[i].to!=fa){
            int u=edge[i].to;
            dfs(u,k,v);
            memcpy(f[0],f[k],sizeof(f[0]));
            for(int j=0;j<3;j++)f[k][j]=add(f[k][j],mx(u));
            f[k][1]=max(f[k][1],add(add(f[0][0],f[u][1]),make_pair(edge[i].len,0)));
            f[k][2]=max(f[k][2],add(add(f[0][1],f[u][1]),make_pair(edge[i].len+v,-1)));
        }
}
pli pd(ll k){
    dfs(1,0,k);
    return mx(1);
}
int main(){
    scanf("%d%d",&n,&m);
    m++;
    memset(head,-1,sizeof(head));
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    ll l=-oo,r=oo;
    while (l<r){
        ll mid=(l+r+1>>1);
        if (pd(mid).se>=m)l=mid;
        else r=mid-1;
    }
	printf("..%lld\n", l);
    o=pd(l-1);
    printf("%lld",o.fi+o.se*(l-1)+l*(m-o.se));
}
