//It is made by ljh2000
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100011;
const int MAXM = 200011;
int n,m,ecnt,first[MAXN],to[MAXM],nextx[MAXM],w[MAXM];
int son_num[MAXN],w_fa[MAXN],havfa[MAXN];
double down[MAXN],up[MAXN],ans;
 
inline int getint(){
    int w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}
 
namespace Tree{
    inline void dfs1(int x,int fa){
        for(int i=first[x];i;i=nextx[i]) {
            int v=to[i]; if(v==fa) continue; havfa[v]=1;
            son_num[x]++; w_fa[v]=w[i]; dfs1(v,x);
            down[x]+=down[v]+w[i];
        }
        if(son_num[x]>0) down[x]/=(double)son_num[x];
    }
 
    inline void dfs2(int x,int fa){
        if(fa!=0) {
            up[x]=down[fa]*son_num[fa]-down[x]-w_fa[x]+up[fa];//从当前节点走上父亲再走下所有儿子节点，再考虑从父亲往上走的情况
            up[x]/=(double)(son_num[fa]+havfa[fa]-1); up[x]+=w_fa[x];//必须要判断父亲有没有父亲！否则不能往上走！
        }
        for(int i=first[x];i;i=nextx[i]) {
            int v=to[i]; if(v==fa) continue;
            dfs2(v,x);
        }
    }
 
    inline void work(){
        dfs1(1,0);
        dfs2(1,0);
    }
}
 
namespace Circle_and_tree{
    bool iscircle[MAXN],vis[MAXN];
    int pre[MAXN],father[MAXN],dui[45],cir_cnt,W[45][45];
    inline void dfs_circle(int x,int fa){//找环
        vis[x]=1;
        for(int i=first[x];i;i=nextx[i]) {
            int v=to[i]; if(v==fa) continue;
            if(vis[v]) {
                if(iscircle[v]) continue;
                int u=x;
                while(1) {
					printf("%d\n", u);
                    iscircle[u]=true; dui[++cir_cnt]=u;
                    pre[u]=father[u];
                    if(cir_cnt>1) W[cir_cnt][cir_cnt-1]=W[cir_cnt-1][cir_cnt]=w_fa[dui[cir_cnt-1]];
                    if(u==v) break;
                    u=father[u];
                }
                W[cir_cnt][1]=W[1][cir_cnt]=w[i];
                continue;
            }
            father[v]=x; w_fa[v]=w[i];
            dfs_circle(v,x);
        }
    }
 
    inline void dfs1(int x,int fa){//得到环上每个点向树中走的down值
		if (x == 97)printf("XX%d\n", iscircle[x]);
        for(int i=first[x];i;i=nextx[i]) {
            int v=to[i]; if(iscircle[v] || v==fa) continue;
            dfs1(v,x);
            son_num[x]++; father[v]=x; w_fa[v]=w[i]; havfa[v]=1;
            down[x]+=down[v]+w[i];
        }
        if(son_num[x]) down[x]/=(double)son_num[x];
    }
 
    inline void dfs2(int x,int fa){//得到环上每个点向树中走的up值
        if(fa!=0) {//环上的点不用再算up值了
            up[x]=down[fa]*son_num[fa]-down[x]-w_fa[x]+up[fa]*havfa[fa];
            //同时考虑父亲节点可能是根节点，可以往环上两边走
            //从当前节点走上父亲再走下所有儿子节点，再考虑从父亲往上走的情况
            up[x]/=(double)(son_num[fa]+havfa[fa]-1); up[x]+=w_fa[x];//必须要判断父亲有没有父亲！否则不能往上走！
        }
        for(int i=first[x];i;i=nextx[i]) {
            int v=to[i]; if(v==fa || iscircle[v]) continue;
            dfs2(v,x);
        }
    }
 
    inline void work(){
        dfs_circle(1,0); int u,now,last,nex; double nowp;
        memset(father,0,sizeof(father));
        memset(w_fa,0,sizeof(w_fa));
        for(int i=1;i<=cir_cnt;i++) dfs1(dui[i],0);
        for(int i=1;i<=cir_cnt;i++) havfa[dui[i]]=2; //两个方向     
        for(int i=1;i<=cir_cnt;i++) {
            nowp=1.0; u=i+1; last=i; if(u>cir_cnt) u=1;
            while(u!=i) {//向编号变大方向
                now=dui[u];//从i走到环上的当前点
                //不要漏掉了环上点之间的长度!!!
                if((u%cir_cnt+1)==i) up[dui[i]]+=(double)nowp*(down[now]+W[last][u]);//特判最后一条环边不能走！
                else up[dui[i]]+=(double)nowp*(son_num[now]*down[now]/(son_num[now]+1)+W[last][u]);
                nowp/=(double)(son_num[now]+1); last=u;
                u++; if(u>cir_cnt) u=1;
            }
 
            nowp=1.0; u=i-1; last=i; if(u==0) u=cir_cnt;
            while(u!=i) {//向编号变小方向
                now=dui[u];//从i走到环上的当前点
                nex=u; nex--; if(nex==0) nex=cir_cnt;
                if(nex==i) up[dui[i]]+=(double)nowp*(down[now]+W[last][u]);//特判最后一条环边不能走！
                else up[dui[i]]+=(double)nowp*(son_num[now]*down[now]/(son_num[now]+1)+W[last][u]);
                nowp/=(double)(son_num[now]+1); last=u;
                u=nex;
            }
            up[dui[i]]/=2.0;//取平均值
        }
        for(int i=1;i<=cir_cnt;i++) dfs2(dui[i],0);
    }
}
 
inline void work(){
    n=getint(); m=getint(); int x,y,z;
    for(int i=1;i<=m;i++) {
        x=getint(); y=getint(); z=getint();
        nextx[++ecnt]=first[x]; first[x]=ecnt; to[ecnt]=y; w[ecnt]=z;
        nextx[++ecnt]=first[y]; first[y]=ecnt; to[ecnt]=x; w[ecnt]=z;
    }
    if(m==n-1) Tree::work();
    else Circle_and_tree::work();
 
    for(int i=1;i<=n;i++)
	{
		printf("%.5f %.5f %d %d\n", down[i], up[i], son_num[i], havfa[i]);
        ans+=(double)(down[i]*son_num[i]+up[i]*havfa[i])/(son_num[i]+havfa[i]);
	}
    ans/=(double)n;//平均值
    printf("%.5lf",ans);
}
 
int main()
{
    work();
    return 0;
}
