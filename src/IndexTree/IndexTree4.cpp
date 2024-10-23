#include<bits/stdc++.h>
using namespace std;

// 二维范围查询 单点增加
const int N=1e4+10;
int n,m; // n行 m列 下标要从 1 1 开始

int Tree[N][N];
int lowbit(int m){
    return m&-m;
}

int sum(int x,int y,int v){
    int ans=0;
    for (int i=x;i>0;i-=lowbit(i)){
        for (int j=y;j>0;j-=lowbit(j)){
            ans+=Tree[i][j];
        }
    }
    return ans;
}

int add(int x,int y,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        for (int j=y;j<=m;j+=lowbit(j)){
            Tree[i][j]+=v;
        }
    }
}


int main(){
    return 0;
}