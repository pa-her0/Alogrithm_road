#include <bits/stdc++.h>
using namespace std;
/*
  线性基是对于二进制中的每一位的选取
  一: 普通线性基
  */
const int bit = 52;

long long Xor[64];

bool insert(long long m)
{
    for (int i = bit - 1; i >= 0; i--)
    {
        if (m >> i == 1)
        {
            if (Xor[i] == 0)
            {
                Xor[i] = m;
                return true;
            }
            m = m ^ Xor[i];
        }
    }
    return false;
}

// 所有异或可能值
void cout_Vordata()
{
    vector<long long> b;
    b.push_back(0);

    for (int i = bit; i >= 0; i--)
    {
        if (Xor[i])
        {
            int n = b.size();
            for (int j = 0; j < n; j++)
            {
                b.push_back(Xor[i] ^ b[j]);
            }
        }
    }
    for (int i = 0; i < b.size(); i++)
    {
        cout << b[i] << " ";
    }
}
// 线性基的二进制形式
void cout_binary(){
    for (int i = 0; i < 32; i++)
    {
        if (Xor[i])
        {
            bitset<32> binary(Xor[i]);
            cout << binary << endl;
        }
    }
}


    // 异或最大值
long long Xor_max(){
    long long Max = 0;
    for (int i = bit - 1; i >= 0; i--)
    {
        Max = max(Max, Max ^ Xor[i]);
    }
    return Max;
    }

  