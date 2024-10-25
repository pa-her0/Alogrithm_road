#include<bits/stdc++.h>
using namespace std;
/*
  树上点差分
  a -> b 路径上增加 v
  a+v b+v lca(最低公共祖先)-v lca的父亲节点-v
  a的权重 = a的权重 + a的所有节点的权重
  
  树上边差分
  a -> b
  a+v b+v lca-2*v
*/

// 链式前向星建图
const int N = 1e5 + 10;
int cnt = 0;
int head[N];
struct
{
    int to, next, w;
} edge[N];

void init()
{
    for (int i = 0; i < N; i++)
        head[i] = 0;
    for (int i = 0; i < N; i++)
        edge[i].next = 0;
    cnt = 1;
}
void addedge(int u, int v)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

// ST处理

const int limit = 64; // 二进制的位数
int deep[N];

int STjump[N][limit];

int power; // 最长的距离的二进制表示
int log2(int m)
{
    int ans = 0;
    while ((1 << ans) <= (m >> 1))
        ans++;
    return ans;
}

void build(int n)
{
    power = log2(n);
}

// 首先先dfs预处理ST表

void dfs(int u, int f)
{
    deep[u] = deep[f] + 1;
    STjump[u][0] = f;
    for (int p = 1; p <= power; p++)
    {
        STjump[u][p] = STjump[STjump[u][p - 1]][p - 1];
    }
    for (int i = head[u]; i > 0; i = edge[i].next)
    {
        if (edge[i].to != f)
        {
            dfs(edge[i].to, u);
        }
    }
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }

    for (int p = power; p >= 0; p--)
    {
        if (deep[STjump[a][p]] >= deep[b])
        {
            a = STjump[a][p];
        }
    }
    if (a == b)
        return a;

    for (int p = power; p >= 0; p--)
    {
        if (STjump[a][p] != STjump[b][p])
        {
            a = STjump[a][p];
            b = STjump[b][p];
        }
    }
    return STjump[a][0];
}
long long ans[N];
void dfs2(int u,int f){
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            dfs2(v,u);
            ans[u]+=ans[v];
        }
    }
}
int n,K;
int main(){
    cin>>n>>K;
    build(n);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    
    dfs(1,0);
    for(int i=0;i<K;i++){
        int a,b,Lca,father;
        cin>>a>>b;
        Lca=lca(a,b);
        father=STjump[Lca][0];
        ans[a]++;ans[b]++;ans[Lca]--;ans[father]--;
    }
    long long Max=0;
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        Max=max(Max,ans[i]);
    }
    cout<<Max<<endl;
    return 0;
}