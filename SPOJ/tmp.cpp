//minamoto
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char obuf[1<<24],*o=obuf;
inline void print(int x){
    if(x>9) print(x/10);
    *o++=x%10+48;
}
const int N=100005;
int ver[N<<1],head[N],Next[N<<1];
int rev[N],fa[N],ch[N][2],w[N],col[N],lmn[N],rmn[N],len[N],val[N];
multiset<int> s[N];
int n,q,white=0,tot;
#define ls ch[x][0]
#define rs ch[x][1]
inline int fir(multiset<int> &s){return s.size()?*s.begin():inf;}
inline int min(int x,int y,int z){return min(x,min(y,z));}
inline bool add(int u,int v){ver[++tot]=v,Next[tot]=head[u],head[u]=tot;}
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
inline void init(){for(int i=0;i<=n;++i) lmn[i]=rmn[i]=w[i]=inf;}
inline void pushr(int x){
    rev[x]^=1,swap(ls,rs),swap(lmn[x],rmn[x]);
}
inline void pushup(int x){
    if(!x) return;
    len[x]=len[ls]+len[rs]+val[x];
    lmn[x]=min(lmn[ls],len[ls]+val[x]+min(w[x],fir(s[x]),lmn[rs]));
    rmn[x]=min(rmn[rs],len[rs]+min(w[x],fir(s[x]),rmn[ls]+val[x]));
}
inline void pushdown(int x){
    if(x&&rev[x]){
        pushr(ls),pushr(rs),rev[x]=0;
    }
}
void rotate(int x){
    int y=fa[x],z=fa[y],d=ch[y][1]==x;
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z,fa[y]=x,fa[ch[x][d^1]]=y,ch[y][d]=ch[x][d^1],ch[x][d^1]=y,pushup(y);
}
void down(int x){
    if(!isroot(x)) down(fa[x]);
    pushdown(x);
}
void splay(int x){
    down(x);
    for(int y=fa[x],z=fa[y];!isroot(x);y=fa[x],z=fa[y]){
        if(!isroot(y))
        ((ch[z][1]==y)^(ch[y][1]==x))?rotate(x):rotate(y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x);
        if(rs) s[x].insert(lmn[rs]);
        if(y) s[x].erase(s[x].find(lmn[y]));
        rs=y,pushup(x);
    }
}
void modify(int x){
    access(x),splay(x);
    col[x]^=1,w[x]=col[x]?0:inf;
    col[x]?(++white):(--white);
    pushup(x);
}
int query(int x){
    access(x),splay(x);
    return rmn[x];
}
void dfs(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==fa[u]) continue;
        fa[v]=u,val[v]=1,dfs(v);
        s[u].insert(lmn[v]);
    }
    pushup(u);
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read();init();
    for(int i=1;i<n;++i){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1);q=read();
    while(q--){
        int op=read(),x=read();
        if(op){
            if(!white) *o++='-',*o++='1';
            else if(col[x]) *o++='0';
            else print(query(x));
            *o++='\n';
        }
        
        else modify(x);
    }
    fwrite(obuf,o-obuf,1,stdout);
    return 0;
}
