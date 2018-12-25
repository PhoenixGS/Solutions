#include<cstdio>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
typedef pair<ll,int>P;
const int N=100010,M=7000000;
int n,m,i,x,tot,T[N],l[M],r[M];ll tag[M];P v[M];map<int,int>pre;
struct E{
  ll v;int x,l,r,m;
  E(){}
  E(ll _v,int _x,int _l,int _r,int _m){v=_v,x=_x,l=_l,r=_r,m=_m;}
  inline bool operator<(const E&b)const{return v<b.v;}
}tmp;
priority_queue<E>Q;
inline void read(int&a){
  char c;bool f=0;a=0;
  while(!((((c=getchar())>='0')&&(c<='9'))||(c=='-')));
  if(c!='-')a=c-'0';else f=1;
  while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';
  if(f)a=-a;
}
int build(int a,int b){
  int x=++tot;
  v[x]=P(0,a);
  if(a==b)return x;
  int mid=(a+b)>>1;
  l[x]=build(a,mid),r[x]=build(mid+1,b);
  return x;
}
inline int add(int x,ll p){
  int y=++tot;
  l[y]=l[x],r[y]=r[x],v[y]=v[x],tag[y]=tag[x]+p;
  v[y].first+=p;
  return y;
}
inline void pb(int x){
  if(!tag[x])return;
  l[x]=add(l[x],tag[x]);
  r[x]=add(r[x],tag[x]);
  tag[x]=0;
}
int change(int x,int a,int b,int c,int d,int p){
  if(c<=a&&b<=d)return add(x,p);
  pb(x);
  int y=++tot;
  l[y]=l[x],r[y]=r[x],v[y]=v[x];
  int mid=(a+b)>>1;
  if(c<=mid)l[y]=change(l[x],a,mid,c,d,p);
  if(d>mid)r[y]=change(r[x],mid+1,b,c,d,p);
  v[y]=max(v[l[y]],v[r[y]]);
  return y;
}
P ask(int x,int a,int b,int c,int d){
  if(c<=a&&b<=d)return v[x];
  pb(x);
  int mid=(a+b)>>1;
  if(d<=mid)return ask(l[x],a,mid,c,d);
  if(c>mid)return ask(r[x],mid+1,b,c,d);
  return max(ask(l[x],a,mid,c,d),ask(r[x],mid+1,b,c,d));
}
inline void ext(int x,int l,int r){
  if(l>r)return;
  P t=ask(x,1,n,l,r);
  Q.push(E(t.first,x,l,r,t.second));
}
int main(){
  read(n),read(m);
  for(T[0]=build(1,n),i=1;i<=n;i++){
    read(x);
    T[i]=change(T[i-1],1,n,pre[x]+1,i,x);
    pre[x]=i;
    ext(T[i],1,i);
  }
  while(m--){
    tmp=Q.top();Q.pop();
	printf("%lld\n", tmp.v);
    ext(tmp.x,tmp.l,tmp.m-1);
    ext(tmp.x,tmp.m+1,tmp.r);
  }
  return printf("%lld",tmp.v),0;
}

