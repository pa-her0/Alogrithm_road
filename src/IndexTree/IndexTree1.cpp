 #include<bits/stdc++.h>
using namespace std;
// 范围查询 单点增加
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

void add(int i,int v){
    while(i<=n){
        tree[i] += v;
        i +=lowbit(i);
    }
}

//这个sum 是从 1-i 范围的
int sum(int i){
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
    for(int i=1; i<=n; i++){
        cin >> a[i];
        add(i,a[i]);
    }
    
    for(int i=0; i<m; i++){
        int falg,x,y;
        cin >>falg >>x >>y;
        if(falg == 1){
            add(x, y); 
        }else{
            cout<<sum(y)-sum(x-1)<<endl;
        }
    }
    return 0;
}