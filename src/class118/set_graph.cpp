#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;

int cnt=0;// 边的编号
int head[N];// head[i] 表示 i号节点所指向的第一条边

struct{
    int from,to,next; // edge[i].to 存储的邻居节点(去往的点)  edge[i].next 表示指向的下一条边的边号
    int w;
}edge[N];

void init(){
    for(int i=0;i<N;i++) head[i]=-1;
    for(int i=0;i<N;i++) edge[i].next=-1;
    cnt=0;
}

void addedge(int u,int v,int w){
    edge[cnt].from=u;
    edge[cnt].to=v; // 这条边去往的点
    edge[cnt].w=w;
    edge[cnt].next=head[u];// 这条边的下一条边是一开始的这个点的头号边
    head[u]=cnt++; // 这个点的头号边改为新进来的那条边
}

int main(){
    init();
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }

    for(int i=0;i<n;i++){
        printf("h[%d]=%d  ",i,head[i]);
    }cout<<endl;

    for(int i=0;i<m;i++) {
        printf("e[%d].to=%d  ",i,edge[i].to);
    }cout<<endl;

    for(int i=0;i<m;i++){
        printf("e[%d].next=%d  ",i,edge[i].next);
    }cout<<endl;

    for(int i=head[2];i>=0;i=edge[i].next){// i是边号
        cout<<edge[i].to<<" ";
    }cout<<endl;
    
    return 0;
}