#include<bits/stdc++.h>
using namespace std;

// 二维单点查询 范围增加

/*
  求和的差分信息是
      Tree1 D[i][j]
      sum(1,1,n,m)=(n+1)*(m+1)*D[i][j] Tree1
      -(m+1)*|(1->m)(1->n) (D[i][j]*i) Tree2
      -(n+1)*|(1->m)(1->n) (D[i][j]*j) Tree3
      +(1->m)(1->n)(D[i][j]*i*J)       Tree4
*/
const int N=2e3+50;
// D[i][j]
int Tree1[N][N];
// D[i][j]*i
int Tree2[N][N];
// D[i][j]*j
int Tree3[N][N];
// D[i][j]*i*j
int Tree4[N][N];

int n,m;
int lowbit(int m){
     return m&-m;
}

void add(int x,int y,int v){
    int v1=v;
    int v2=v*x;
    int v3=v*y;
    int v4=v*x*y;
    for(int i=x; i<=n; i +=lowbit(i)){
        for(int j=y; j<=m; j+=lowbit(j)){
            Tree1[i][j] += v1;
            Tree2[i][j] += v2;
            Tree3[i][j] += v3;
            Tree4[i][j] += v4;
        }
    }
}

// 1 1 -> x y
int sum(int x,int y){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans +=(x+1)*(y+1)*Tree1[i][j]-(y+1)*Tree2[i][j]-(x+1)*Tree3[i][j]+Tree4[i][j];
        }
    }
    return ans;
}

void add(int a,int b,int c,int d,int v){
    add(a,b,v);
    add(a,d+1,-v);
    add(c+1,b,-v);
    add(c+1,d+1,v);
}

int range_sum(int a,int b,int c,int d){
    return sum(c,d)-sum(a-1,d)-sum(c,b-1)+sum(a-1,b-1);
}
int main(){
    char X;
    cin>>X>>n>>m;
    char temp;
    while(cin>>temp){
        if(temp=='L'){
            int a,b,c,d,v;
            cin>>a>>b>>c>>d>>v;
            add(a,b,c,d,v);
        }else {
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            cout<<range_sum(a,b,c,d)<<endl;
        }
    }
    return 0;
}