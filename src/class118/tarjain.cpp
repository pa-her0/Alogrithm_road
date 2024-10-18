#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
// 批量处理的两个节点的最低公共祖先(LAC)
// 并查集
int father[N];

// 链式前向星建图

int head[N];
struct
{
    int to, next;
} edge[N << 1];
int cnt;
// 查询链表(链式前向星)

int check_head[N];
struct
{
    int to, next, flag;
} check_edge[N << 1];
int c_cnt;

// targin

bool visited[N];

int ans[N];
// 并查集查询头节点

int find(int i)
{ // 查找节点并且扁平化
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}
// 建图
void bulid(int n)
{
    cnt = c_cnt = 1;
    for (int i = 1; i <= n + 1; i++)
        head[i] = 0;
    for (int i = 1; i <= n + 1; i++)
        check_head[i] = 0;
    for (int i = 1; i <= n + 1; i++)
        visited[i] = false;
    for (int i = 1; i <= n; i++)
        father[i] = i;
}

void add_edge(int u, int v)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void add_check_edge(int u, int v, int i)
{ // i表示问题编号
    check_edge[c_cnt].to = v;
    check_edge[c_cnt].next = check_head[u];
    check_edge[c_cnt].flag = i;
    check_head[u] = c_cnt++;
}
// targin算法
void targin(int u, int f)
{
    visited[u] = true;
    for (int e = head[u], v; e != 0; e = edge[e].next)
    {
        v = edge[e].to;
        if (v != f)
        {
            targin(v, u);
            father[v] = u;
        }
    }
    for (int e = check_head[u], v; e != 0; e = check_edge[e].next)
    {
        v = check_edge[e].to;
        if (visited[v])
        {
            // cout<<check_edge[e].flag<<" "<<find(v)<<endl;
            ans[check_edge[e].flag] = find(v); // v的代表节点
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    bulid(n);
    // cout<<c_cnt<<cnt<<endl;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        add_check_edge(u, v, i);
        add_check_edge(v, u, i);
    }
    targin(s, 0);
    for (int i = 0; i < m; i++)
        cout << ans[i] << endl;

    return 0;
}