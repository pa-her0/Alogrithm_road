#include<bits/stdc++.h>
using namespace std;
void slove(){
    int n,m;
   
    cin >> n >> m;
    vector<int> flag(n);
    vector<vector<int>> num(n,vector<int>(m));
    int q,temp;
    for(int i=1;i<=n;i++){
        cin >> flag[i];
       for(int j=0;j<q;j++){
        cin >> num[i][j];

       }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<num[i].size();j++) cout<<num[i][j]<<" ";
    //     cout<<endl;
    // }
    int j;
    bool ans=false;
    for(int i=2;i<=n;i++){
        map <int,int>mp;
       for( j=0;j<flag[i-1];j++){
          mp[num[i-1][j]]++;
       }
       for( j=0;j<flag[i];j++){
        if(!mp[num[i][j]]){
            ans=true;
            break;
        }
       }
       cout << j <<endl;
    for(int k=1;k<=j-1;k++) cout << k << " ";
    cout << j+1 << " " << j <<" ";
    for(int k=j+2;k<=n;k++) cout << k << " ";
    }
}

int main(){
    int t;
    cin >> t;
    while(t--) slove();
    return 0;
}