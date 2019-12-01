// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <queue>

typedef long long LL;

inline char fgc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
    register LL res = 0, neg = 1;
    register char c = fgc();
    while(c < '0' || c > '9') {
        if(c == '-') neg = -1;
        c = fgc();
    }
    while(c >= '0' && c <= '9') {
        res = res * 10 + c - '0';
        c = fgc();
    }
    return res * neg;
}

inline bool isop(char c) {
    return c == 'A' || c == 'C';
}

inline char readop() {
    char c;
    while(!isop(c = fgc()));
    return c;
}

const int MAXN = 200005, INF = 2e9;

int n, q, col[MAXN], ans;

struct Edge {
    int to, w, nxt;
} gra[MAXN << 1], grao[MAXN << 1];
int head[MAXN], heado[MAXN], ecnt, ecnto;

inline void addedge(int u, int v, int w) {
    gra[ecnt] = Edge {v, w, head[u]}; head[u] = ecnt++;
}

inline void addedgeo(int u, int v, int w) {
    grao[ecnto] = Edge {v, w, heado[u]}; heado[u] = ecnto++;
}

inline void rebuild(int u, int fa) {
    int ff = 0;
    for(int i = heado[u]; ~i; i = grao[i].nxt) {
        int v = grao[i].to, w = grao[i].w;
        if(v == fa) continue;
        if(!ff) {
            addedge(u, v, w);
            addedge(v, u, w);
            ff = u;
        } else {
            int k = ++n;
            col[k] = 1;
            addedge(ff, k, 0);
            addedge(k, ff, 0);
            addedge(k, v, w);
            addedge(v, k, w);
            ff = k;
        }
        rebuild(v, u);
    }
}

bool del[MAXN << 1];
int ct, ctsiz, sum;
int siz[MAXN], msz[MAXN];

inline void calsiz(int u, int fa) {
    siz[u] = 1;
    for(int i = head[u]; ~i; i = gra[i].nxt) {
        int v = gra[i].to;
        if(del[i >> 1] || v == fa) continue;
        calsiz(v, u);
        siz[u] += siz[v];
    }
}

inline void findct(int u, int fa) {
    for(int i = head[u]; ~i; i = gra[i].nxt) {
        int v = gra[i].to;
        if(del[i >> 1] || v == fa) continue;
        findct(v, u);
        int vsiz = std::max(siz[v], sum - siz[v]);
        if(vsiz < ctsiz) {
            ct = i;
            ctsiz = vsiz;
        }
    }
}

struct DisData {
    int u, d;
    inline bool operator<(const DisData &rhs) const {
        return d < rhs.d;
    }
};

std::priority_queue<DisData> s[MAXN][2];
int cnt;

struct NodeData {
    int bel, side, dis;
};
std::vector<NodeData> ndata[MAXN];

inline void caldis(int u, int fa, int d, int t, int l) {
    if(!col[u]) {
        s[t][l].push(DisData {u, d}); ndata[u].push_back(NodeData {t, l, d});
    }
    for(int i = head[u]; ~i; i = gra[i].nxt) {
        int v = gra[i].to, w = gra[i].w;
        if(del[i >> 1] || v == fa) continue;
        caldis(v, u, d + w, t, l);
    }
}

int mx[MAXN], lch[MAXN], rch[MAXN], ctw[MAXN];

inline void update(int p) {
    while(!s[p][0].empty() && col[s[p][0].top().u]) s[p][0].pop();
    while(!s[p][1].empty() && col[s[p][1].top().u]) s[p][1].pop();
    if(s[p][0].empty() || s[p][1].empty()) mx[p] = 0;
    else mx[p] = s[p][0].top().d + ctw[p] + s[p][1].top().d;
    if(lch[p]) mx[p] = std::max(mx[p], mx[lch[p]]);
    if(rch[p]) mx[p] = std::max(mx[p], mx[rch[p]]);
}

inline int divide(int u) {
    calsiz(u, 0);
    ct = -1; ctsiz = INF; sum = siz[u]; findct(u, 0);
    if(ct == -1) return 0;
    int x = gra[ct].to, y = gra[ct ^ 1].to;
    del[ct >> 1] = true;
    int t = ++cnt;
    ctw[t] = gra[ct].w;
    caldis(x, 0, 0, t, 0); caldis(y, 0, 0, t, 1);
    lch[t] = divide(x); rch[t] = divide(y); 
    update(t);
    return t;
}

inline void setwhite(int u) {
    for(int i = ndata[u].size() - 1; i >= 0; i--) {
        NodeData d = ndata[u][i];
        s[d.bel][d.side].push(DisData {u, d.dis});
        update(d.bel);
    }
}

inline void setblack(int u) {
    for(int i = ndata[u].size() - 1; i >= 0; i--) {
        NodeData d = ndata[u][i];
        update(d.bel);
    }
}

int ut, vt, wt;
char op;

int main() {
    memset(head, -1, sizeof(head));
    memset(heado, -1, sizeof(heado));
    n = readint();
    int white = n;
    for(int i = 1; i < n; i++) {
        ut = readint(); vt = readint(); wt = readint();
        addedgeo(ut, vt, wt);
        addedgeo(vt, ut, wt);
    }
    rebuild(1, 0);
    divide(1);
    q = readint();
    while(q--) {
        op = readop();
        if(op == 'A') {
            if(!white) {
                puts("They have disappeared.");
            } else if(white == 1) {
                puts("0");
            } else {
                printf("%d\n", mx[1]);
            }
        } else {
            ut = readint(); 
            col[ut] ^= 1;
            if(col[ut]) {
                setblack(ut);
                white--;
            } else {
                setwhite(ut);
                white++;
            }
        }
    }
    return 0;
}
