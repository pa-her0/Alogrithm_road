#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int old[N];
int New[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>old[i];
        New[i]=old[i];
        }
        sort(old,old+n);
    int cnt=n;
    cnt=unique(old+1,old+1+n)-(old+1);
    for(int i=1;i<=cnt;i++){
        New[i]=lower_bound(old+1,old+1+n,New[i])-old;
    }

    for(int i=1;i<=cnt;i++) cout<<New[i]<<" ";//每个值在原始位置的大小

    return 0;
}