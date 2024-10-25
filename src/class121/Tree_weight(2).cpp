#include<bits/stdc++.h>
using namespace std;
// 带点权求重心


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

int best=INT_MAX,center;
int Size[N];
int path[N];

int n;
int cow[N];
int cowSum=0;


void dfs(int u,int f){
    Size[u]=cow[u];
    int maxSub=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dfs(v,u);
        Size[u]+=Size[v];
        maxSub=max(maxSub,Size[v]);
       }
    }
    maxSub=max(maxSub,cowSum-Size[u]);
    if(maxSub<best){
        best=maxSub;
        center=u;
    }
}

void dfs_road(int u,int f){
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            path[v]=path[u]+edge[e].w;
            dfs_road(v,u);
        }
    }
}
int main(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
       cin>>cow[i];
       cowSum+=cow[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    path[center]=0;
    dfs_road(center,0);
    long long sum=0;
    // for(int i=1;i<=n;i++){
    //     cout<<path[i]<<" "<<cow[i]<<endl;
    // }
    for(int i=1;i<=n;i++){
        sum+=path[i]*cow[i];
    }
    cout<<sum<<endl;
    return 0;
}