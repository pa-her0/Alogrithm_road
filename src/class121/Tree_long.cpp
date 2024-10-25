#include<bits/stdc++.h>
using namespace std;
// 直径：树上距离最远的两个点

/*
  1，两次 dfs (仅适用非负边权)  *可以得到这条直径的相关节点信息
   （1) 随便选一个点 找最远的点
    (2) 从最远的点 dfs
  2， 树型dp (使用于所有树)  *只能得到树的直径长度

  树上边权都为正的结论：
  1，如果有多条直径 直径一定有共同的中间部分 (点或者路径)
  2，树上任意一点的最远点的集合，直径的端点至少有一个在集合中
*/

//|||||||||||||||||||||||||||||
// 方法1

// 链式前向星建图
// 链式前向星建图
const int N = 1e6 + 10;
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
void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}


// 直径的开始点
int start;

// 直径的结束点
int End;

// 直径的长度
int diameter;

// 从头结点出发，到 i 的距离
int dist[N];

// i节点的上一个节点
int last[N];

int n; // n 个点
void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int e=head[u];e!=0;e=edge[e].next){
        if(edge[e].to!=f){
            dfs(edge[e].to,u,edge[e].w);
        }
    }
}

void longest_road(){
    dfs(1,0,0);
    start = 1;
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[start]) start=i;
    }
    dfs(start,0,0);
    End=1;
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[End]) End=i;
    }
    diameter = dist[End];
}

// 方法2
// Dist[u] 从u节点往下走 能走出的最大距离
int Dist[N];

// ans[u] 路径包括u的最大路径和
int ans[N];

void dp(int u,int f){
    for(int e=head[u],v;e>0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dp(v,u);
       }
       }
       for(int e=head[u],v;e>0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            diameter=max(diameter,Dist[u]+Dist[v]+edge[e].w);
            Dist[u]=max(Dist[u],Dist[v]+edge[e].w);
        }
       }

}
int main(){
    cin >>n;
    init();diameter=INT_MIN;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    //longest_road();
    dp(1,0);
    cout<<diameter<<endl;
    return 0;
}