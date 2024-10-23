#include <bits/stdc++.h>
using namespace std;

// 高斯消元 求 标准线性基

const int MAXN = 1e5 + 10;
const int bit = 64;
int a[MAXN];

void swap(int p1, int p2)
{
    int temp = a[p1];
    a[p1] = a[p2];
    a[p2] = temp;
}

int n;
int len;  // len是前几行是以及找到了线性基的
int zero; // 是否可以异或出0

void gaosi_create()
{
    len = 1;
    for (int i = bit; i >= 0; i--)
    {
        for (int j = len; j <= n; j++)
        {
            if ((a[j] & (1 << i)) != 0)
            {
                swap(j, len);
                break;
            }
        }
        if ((a[len] & (1 << i)) != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != len && (a[j] & (1 << i)) != 0)
                {
                    a[j] ^= a[len];
                }
            }
            len++;
        }
    }
    len--;
    zero = (len != n);
}

int K_th(int k)
{
    if (zero && k == 1)
    {
        return 0;
    }
    if (zero)
    {
        k--;
    }
    if (k >= (1 << len))
    {
        // k的位数大于线性基的位数
        return -1;
    }
    int ans = 0;
    for (int i = len, j = 0; i >= 1; i--, j++)
    {
        if ((k & (1 << j)) != 0)
        {
            ans ^= a[i];
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    gaosi_create();

    int k;
    cin >> k;
    int result = K_th(k);

    return 0;
}
