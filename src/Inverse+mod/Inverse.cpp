#include <bits/stdc++.h>
using namespace std;

const int N = 3e6 + 10;

int mod;

vector<long long> Inverse1(N, 0);

vector<long long> Inverse2(N, 0);
// 连续数字的逆元

// 从左向右推
void inverse1(int n)
{
    Inverse1[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        Inverse1[i] = (mod - Inverse1[mod % i] * (mod / i) % mod);
    }
}

// 连续数字的阶乘的逆元

// 从右往左推
void inverse2(int n)
{
    for (int i = n - 1; i >= 1; i--)
    {
        Inverse2[i] = (Inverse2[i + 1] * (i + 1)) % mod;
    }
}

// 费马小定理求逆元
int Power(int base, int exp, int mod)
{
    int result = 1;
    base = base % mod;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int mod_inverse(int a, int m)
{
    return Power(a, m - 2, m);
}

// 扩展欧几里得算法求逆元



