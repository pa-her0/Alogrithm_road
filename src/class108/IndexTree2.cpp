#include<bits/stdc++.h>
using namespace std;
// 单点查询 范围增加
// 原始数组变成差分数组 -> 用差分数组来构建Tree数组

const int N=5e5+10;

//*树状数组-> 下标从1开始 */
int tree[N]; // 树状数组
/*
树状数组所管束的范围是 [去掉二进制的lowbit+1,自己] 
*/
//lowbit   i最右侧的1的状态

int n;// 原数组长度

int lowbit(int n){
    return n & -n;
}

// l-r 范围增加 v 
void add(int l,int r,int v){
    while(l <= n){
        tree[l] += v;
        l +=lowbit(l);
    }
    
    int x = r+1;
    while(x <= n){
        tree[x] -= v;
        x +=lowbit(x);
    }
}

//这个sum 是从 1-i 范围的 用差分来构建 前i个就是原数组 i 的值
int find(int i){
    int ans = 0;
    while(i > 0){
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int main(){
    int m;
    cin >> n >> m;
    vector <int> a(n+1,0);
    //vector <int> chafen(n+1,0);
    for(int i=1; i<=n; i++){
        cin >> a[i];
        add(i,i,a[i]);
    }
    
    for(int i=0; i<m; i++){
        int x;
        cin >> x;
        if(x == 1){
            int l,r,v;
            cin>> l >> r >> v;
            add(l,r,v); 
        }else{
            int l;
            cin >> l;
            cout<< find(l) <<"\n";
        }
    }
    return 0;
}