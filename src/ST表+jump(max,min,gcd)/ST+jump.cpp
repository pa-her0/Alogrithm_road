#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10; // 节点个数

const int M = 256; // 最长路径的二进制的长度

int ST[N][M]; // j号节点 走2的m次方

int num[N]; // 原始的数据表

// 最接近m的二进制值的长度
int log2(int m)
{
    int ans = 0;
    while ((1 << ans) <= (m >> 1))
    {
        ans++;
    }
    return ans;
}

void build_st(int n)
{
    // 初始化ST表
    int power = log2(n);
    // 初始化了走2的0次方
    for (int i = 0; i < n; i++)
    {
        ST[i][0] = num[i];
    }
    // ST[i][j]=ST[ST[i][j-1]][j-1];
    for (int j = 1; j < power; j++)
    {
        for (int i = 0; i < n; i++)
        {
            ST[i][j] = ST[ST[i][j - 1]][j - 1];
        }
    }
}

// 最小值就是将 max 改成 min
// gcd就是将 max 改成 gcd
void bulid_st_max_min(int n)
{
    for (int i = 0; i < n; i++)
    {
        ST[i][0] = num[i]; // 从i节点开始的2的0次方的距离的最值
    }

    for (int i = 1; i <= log2(n); i++)
    {
        for (int j = 0; j + (1 << i) - 1 < n; j++)
        {
            // question 为什么是 i+(1<<p)-1 而不是 i+(1<<p-1)
            // 因为我们要扩展的是 p的位置(2的p次方)
            ST[j][i] = max(ST[j][i - 1], ST[j + (1 << i - 1)][i - 1]);
        }
    }
}
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> num[i];
    return 0;
}