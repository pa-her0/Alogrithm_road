#include<bits/stdc++.h>
using namespace std;

// 二维单点查询 范围增加
int lowbit(int m){
     return m&-m;
}

/*
  求和的差分信息是
      sum(1,1,n,m)=
      -(m+1)*|(1->m)(1->n) (D[i][j]*i)
      -(n+1)*|(1->m)(1->n) (D[i][j]*j)
      +(1->m)(1->n)(D[i][j]*i*J) 
*/

int main(){
    return 0;
}