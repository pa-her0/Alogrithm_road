#include <bits/stdc++.h>
using namespace std;

// 范围增加 范围查询( l - r 的范围累加和)

/* Di 是差分
Tree1 -> Di
Tree2 -> (i-1)*Di 几号位置加就是 (i-1)*v

1-r 的累加和 k*(Di) - ((i-1)*Di)

*/
const int N = 1e5 + 10;
long long  Tree1[N];
long long Tree2[N];
int n,m; // 数组长度

int lowbit(int m)
{
    return m & -m;
}

void add(long long a[], int i, long long v)
{
    while (i <= n)
    {
        a[i] += v;
        i += lowbit(i);
    }
}

long long sum(long long a[], int i)
{
    long long ans = 0;
    while (i > 0)
    {
        ans += a[i];
        i -= lowbit(i);
    }
    return ans;
}

void add(int l, int r, long long v)
{
    add(Tree1, l, v);
    add(Tree1, r + 1, -v);
    add(Tree2, l, (l - 1) * v);
    add(Tree2, r + 1, -r*v);
}

long long sum_rage(int l, int r)
{
    return sum(Tree1, r) * r - sum(Tree2, r) - sum(Tree1, l - 1) * (l - 1) + sum(Tree2, l - 1);
}
int main()
{
    cin >> n >> m;
    vector<long long> origin(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> origin[i];
        add(i,i,origin[i]);
    }
    int temp;
    for (int i = 0; i < m; i++)
    {
    
        cin >> temp;
        if (temp == 1)
        {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            add(l, r, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << sum_rage(l, r) << endl;
        }
        // for(int i=1;i<=n;i++) cout<<Tree1[i]<<" ";
        // for(int i=1;i<=n;i++) cout<<Tree2[i]<<" ";
        // cout<<endl;
    }
    return 0;
}