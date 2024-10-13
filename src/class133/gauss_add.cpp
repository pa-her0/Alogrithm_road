#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const double sml = 1e-7;
vector<vector<double>> gauss(N, vector<double>(N));
int n; // 变量个数、

void swap(int i, int j)
{
    double temp;
    for (int t = 0; t <= n; t++)
    {
        temp = gauss[i][t];
        gauss[i][t] = gauss[j][t];
        gauss[j][t] = temp;
    }
}

int guass_add()
{
    for (int i = 0; i < n; i++)
    {
        int maxl = i;
        for (int j = 0; j < n; j++)
        {
            if (j < i && abs(gauss[j][j]) >= sml)
            {
                continue;
            }
            if (abs(gauss[j][i]) > abs(gauss[maxl][i]))
            {
                maxl = j;
            }
        }
        swap(i, maxl);
        // 如果它为0,如何检测他的解的个数

        // if (abs(temp) < sml)
        //     return 0;
        if (abs(gauss[i][i]) >= sml)
        {
            double temp = gauss[i][i];
            for (int k = i; k <= n; k++)
            {
                gauss[i][k] /= temp;
            }

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    double rate = gauss[j][i] / gauss[i][i];
                    for (int k = i; k <= n; k++)
                    {
                        gauss[j][k] -= gauss[i][k] * rate;
                    }
                }
            }
        }
    }

    int sign = 1;
    for (int i = 0; i < n; i++)
    {
        if (abs(gauss[i][i]) < sml && abs(gauss[i][n]) >= sml)
        {
            sign = -1;
            break;
        }
        if (abs(gauss[i][i]) < sml)
        {
            sign = 0;
        }
    }
    if (sign == 1)
    {
        for (int i = 0; i < n; i++)
        {
            printf("x%d=%.2lf\n", i + 1, gauss[i][n]);
        }
    }
    else
    {
        cout << sign << endl;
    }
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<=n; j++){
    //         cout<<gauss[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return 0;
}
int main()
{
    // int k = guass_add();
    // if (k == 0)
    // {
    //     cout << "No Solution" << endl;
    // }
    // else
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         printf("%.2f\n", gauss[i][n]);
    //     }
    // }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cin >> gauss[i][j];
        }
    }

    guass_add();
    return 0;
}