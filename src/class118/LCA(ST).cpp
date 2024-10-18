#include <bits/stdc++.h>
using namespace std;

// 链式前向星建图
const int N = 1e5 + 10;
int cnt = 0;
int head[N];
struct
{
    int to, next, w;
} edge[N];

void init()
{
    for (int i = 0; i < N; i++)
        head[i] = -1;
    for (int i = 0; i < N; i++)
        edge[i].next = -1;
    cnt = 1;
}
void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

// ST处理

const int limit = 64; // 二进制的位数
int deep[N];

int STjump[N][limit];

int power; // 最长的距离的二进制表示
int log2(int m)
{
    int ans = 0;
    while ((1 << ans) <= (m >> 1))
        ans++;
    return ans;
}

void build(int n)
{
    power = log2(n);
    cnt = 1;
}

// 首先先dfs预处理ST表

void dfs(int u, int f)
{
    deep[u] = deep[f] + 1;
    STjump[u][0] = f;
    for (int p = 1; p <= power; p++)
    {
        STjump[u][p] = STjump[STjump[u][p - 1]][p - 1];
    }
    for (int i = head[u]; i > 0; i = edge[i].next)
    {
        if (edge[i].to != f)
        {
            dfs(edge[i].to, u);
        }
    }
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }

    for (int p = power; p >= 0; p--)
    {
        if (deep[STjump[a][p]] >= deep[b])
        {
            a = STjump[a][p];
        }
    }
    if (a == b)
        return a;

    for (int p = power; p >= 0; p--)
    {
        if (STjump[a][p] != STjump[b][p])
        {
            a = STjump[a][p];
            b = STjump[b][p];
        }
    }
    return STjump[a][0];
}
int main()
{
    return 0;
}