#include<bits/stdc++.h>
using namespace std;

vector<int> get_third(long long m){
            vector<int>third;
            if(m==0){
                third.push_back(0);
            }
            while(m>0){
                third.push_back(m%3);
                m/=3;
            }
            reverse(third.begin(),third.end());
            return third;
}
void dfs(vector<int>&l,vector<int>&r,int falg,int sum,int limit,int &result){
     if(limit==1){
        int ans=(r.size()-falg)*2+sum;
        result=max(result,ans);
        return;
     }
     if(falg==r.size()){
        int ans=sum+r.size();
        result=max(ans,result);
        return ;
     }
     int temp=r[falg];
     if(temp>=l[falg]+1){
        dfs(l,r,falg+1,sum+temp-1,1,result);
     }
}

void slove(){
    long long l,r;
    cin>>l>>r;
    int result=0;
    vector<int> L=get_third(l);
    vector<int> R=get_third(r);
    if(L.size()<R.size()){
        result=(R.size()-1)*2+(R.size()-1);
        vector<int> backup(R.size(),0);
        backup[0]=1;
        dfs(backup,R,0,0,0,result);
    }else{
        dfs(L,R,0,0,0,result);
    }
    cout<<result<<endl;
}
int main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--) slove();
}