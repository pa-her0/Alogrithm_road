#include<bits/stdc++.h>
using namespace std;

const int N=1e4+10;//节点个数

const int M=256;//最长路径的二进制的长度

int ST[N][M];//j号节点 走2的m次方

int num[N];//原始的数据表

//最接近m的二进制值的长度
int log2(int m){
    int ans=0;
    while((1<<ans)<=(m>>1)){
        ans++;
    }
    return ans;
}


void build(int n){
     //初始化ST表
     int power=log2(n);

     //初始化了走2的0次方

     for(int i=0;i<n;i++){
        ST[i][0]=num[i];
     }

    //ST[i][j]=ST[ST[i][j-1]][j-1];
     for(int j=1;j<power;j++){
        for(int i=0;i<n;i++){
            ST[i][j]=ST[ST[i][j-1]][j-1];
        }
     }
}
int main(){
    int n;
    cin>>n;
    
    for(int i=0;i<n;i++) cin>>num[i];
    return 0;
}