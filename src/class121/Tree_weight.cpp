/*
  重心的定义：
     1，最大子树的节点数最少
     2，每颗子树的节点数不超过总结点的一半
     3，以重心为根时，所有节点走向该节点的总边数最少
  重心的性质：
     1，树上有重心，两个重心一定相邻
     2，树上增加或者删除叶子节点，转移的重心最多移动一条边
     3，两棵树连起来，新树的重心一定在原来两棵树的重心的路径上
     4，如果是正边权，所有节点走向重心的总距离和最小
*/
#include<bits/stdc++.h>
using namespace std;

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
        head[i] = -1;
    for (int i = 0; i < N; i++)
        edge[i].next = -1;
    cnt = 1;
}
void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

// 定义1 最大子树的节点个数最少
int Size[N];// i节点的子树大小
int best=INT_MAX,center;
int n;

void dfs(int u,int f){
    Size[u]=1;
    int maxSub=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            dfs(v,u);
            Size[u]+=Size[v];
            maxSub=max(maxSub,Size[v]); //取子树的maxsub
        }
    }
    maxSub=max(maxSub,n-Size[u]); // 取自己的maxsub
    if(maxSub<best||(maxSub==best&&u<center)){
        best=maxSub;
        center=u;
    }
}

// 定义2
int MaxSub[N];
int SIZE[N];
void dfs(int u,int f){
    SIZE[u]=1;
    MaxSub[u]=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dfs(v,u);
        SIZE[u]+=SIZE[v];
        MaxSub[u]=max(MaxSub[u],SIZE[v]);
       }
    }
    MaxSub[u]=max(MaxSub[u],n-SIZE[u]);
}
int main(){
    return 0;
}