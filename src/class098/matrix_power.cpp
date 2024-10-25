#include<bits/stdc++.h>
using namespace std;

// * 重点： 关系矩阵
/*
递推式子中有n个表达式 就是 n*n的关系矩阵
第 0 列是递推表达式的关系系数
【m -> m+n】*关系矩阵(n*n) =[m+1 -> m+n+1] 
*/
vector<vector<int>> multipy(vector<vector<int>> &a,vector<vector<int>> &b){
    int n = a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));

    for (int i = 0; i<n;i++){
        for(int j=0;j<m;j++){
            for(int c=0;c<k;c++){
                ans[i][j]+=a[i][c]*b[c][j];
            }
        }
    }
    return ans;
}

vector<vector<int>> pow(vector<vector<int>> &m,int p){
    int n = m.size();
    vector<vector<int>> ans(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        ans[i][i]=1;
    }
    for(;p!=0;p>>=1){
        if((p&1)!=0){
            ans =multipy(ans,m);
        }
        m=multipy(m,m);
    }
    return ans;
}
int main(){
    vector<vector<int>> a(2,vector<int>(2));
    a[0][0]=1;a[0][1]=2;a[1][0]=3,a[1][1]=4;
    vector<vector<int>>t=pow(a,5);
     for(int i=0;i<t.size();i++){
        for(int j=0;j<t[0].size();j++){
            cout<<t[i][j]<<" ";
        }cout<<endl;
     }
    return 0;
}