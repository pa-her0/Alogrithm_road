#include<bits/stdc++.h>
using namespace std;
int c[1010][1010]={0};
void add(int x1,int y1,int x2,int y2){
     c[x1][y1]++;
     c[x1][y2+1]--;
     c[x2+1][y2+1]++;
     c[x2+1][y1]--;
}
void slove(){
    int n,m,k;
    string s;
    memset(c,0,sizeof c);
    cin >> n >> m >> k >> s;
    vector<vector<bool>> visit(1010,vector<bool>(1010,false));
    // for(int i=1; i<=n; i++){
    //     for(int j=1; j<=m; j++){
    //         cout<<"* ";
    //     }cout<<endl; 
    // }

    int U = 1,D = n,L = 1,R = m;
    int u = 1,d = n,l = 1,r = m;
    for (int i = 0; i < s.size(); i++){
        if (s[i]=='L') r++,l++;
        else if (s[i]=='R') r--,l--;
        else if (s[i]=='U') u++,d++;
        else u--,d--;
        U = max(u,U); D=min(d,D); L=max(L,l); R=min(r,R);
    }
    if(L>R||U>D){
        if(k) cout<<0<<endl;
        else cout<<m*n<<endl;
        return;
    }
    // for(int i=U; i<=D; i++){
    //     for(int j=L; j<=R; j++){
    //         cout<<"&"<<" ";
    //     }cout<<endl;
    // }
    // cout<< U <<" "<< D <<" "<< R <<" "<< L <<endl;
    int dalt = (D-U+1)*(R-L+1)-k;

    if(dalt<0){
        cout<<0<<endl;
        return ;
    }
    
    add(U,L,D,R);
    visit[U][L]=true;

    for (int i=0; i<s.size(); i++)
    {
        if(s[i]=='L') L--,R--;
        else if(s[i]=='R') L++,R++;
        else if(s[i]=='U') U--,D--;
        else U++,D++;
        if(visit[U][L] ) continue;
        visit[U][L]=true;
        add(U,L,D,R);
    }

    for(int i=1;i<=n;i++){
       for(int j=1;j<=m;j++){
        c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
       }
    }
   int ans=0;
   for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(c[i][j]==dalt) ans++;
    }
   }
   cout<<ans<<endl;
}

int main(){
    int t;
    cin >> t;
    while(t--) slove();

    return 0;
}