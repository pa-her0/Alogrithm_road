#include<bits/stdc++.h>
using namespace std;
void slove(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> op(m+1);
    vector<vector<int>> G(n+1);
    vector<int> in(n+1);
    for(int i=1;i<=n;i++){
         int temp;cin >> temp;
        for(int j=0;j<temp;j++){
            int t;cin >> t;
            op[t].push_back(i);// t节点的操作
        }
    }
    
    // 构建依赖图
    for(int i=1;i<=m;i++){
        int s=op[i].size();
        for(int j=0;j<s-1;j++){
           G[op[i][j]].push_back(op[i][s-1]); // t节点的操作永远由最后一个操作决定
           in[op[i][s-1]]++;
        }
    }
    priority_queue<int> Q;
    for(int i=1;i<=n;i++){
        if(in[i]==0) Q.push(i);
    }
    vector<int>ans(n+1);
    int flag=1;
    while(!Q.empty()){
        int x=Q.top();Q.pop();
        ans[flag++]=x;
        for(int v:G[x]){
            in[v]--;
            if(in[v]==0) Q.push(v);
        }
    }
    bool ok=false;
    for(int i=1;i<=n;i++) {
        if(ans[i]!= i) ok=true;
    }
    if(ok){
        cout << "Yes"<<endl;
        for(int i=1;i<=n;i++) cout<<ans[i]<<(n==i?'\n':' ');
    }else cout << "No" <<endl;
}

int main(){
    int t;
    cin >> t;
    while(t--) slove();
    return 0;
}