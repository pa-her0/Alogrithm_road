#include<bits/stdc++.h>
using namespace std;

int log2(int m){
    int ans =0;
    while((1<<ans)<=(m>>1)){
        ans++;
    }
    return ans;
}

int Log2[1000005];
int main(){
    int n;
    cin>>n;
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
       Log2[i]=Log2[i>>1]+1;
    }
    for(int i=1;i<=n;i++){
        if(log2(i)!=Log2[i]){
            cout<<"No"<<endl;
        }
        // cout<<log2(i)<<" ";
    }cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<Log2[i]<<" ";
    // }
    return 0;
}