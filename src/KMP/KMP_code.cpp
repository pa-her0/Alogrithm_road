#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int Next[N];
//next[i]数组表示，前i-1个字符串的前后缀最大匹配长度
//s1是主串，s2是子串
int kmp(string s1,string s2){
    int n=s1.length(),m=s2.length(),x=0,y=0;
    get_NEXT(s2);
    while(x<n&&y<m){
        if(s1[x]==s2[y]){
            x++;y++;
        }else if(y==0){
            x++;
        }else {
            y=Next[y];
        }
    }
    return y==m?x-y:-1;
}
//时间复杂度O(n)
void get_NEXT(string s2){
    int n=s2.length();
    Next[0]=-1;
    Next[1]=0;
    int i=2,cn=0;
    while(i<n){
        if(s2[i-1]==s2[cn]){
            Next[i++]=++cn;
        }else if(cn>0){
            cn=Next[cn];//cn往前跳，是因为cn保留着i-1的next
        }else {
            Next[i++]=0;
        }
    }
}
int main(){
    return 0;
}