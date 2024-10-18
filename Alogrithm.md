# ALOGRITHM

## **manacher算法**

```c++
int manacher(string str){
	manacherss(str.toCharArray());
	int max = 0;
	for (int i = 0, c = 0, r = 0, len; i < n; i++) {
		len = r > i ? Math.min(p[2 * c - i], r - i) : 1;
		while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
			len++;
		}
		if (i + len > r) {
			r = i + len;
			c = i;
		}
		max = Math.max(max, len);
		p[i] = len;
	}
	return max - 1;
}

void manacherss(char[] a) {
	n = a.length * 2 + 1;
	for (int i = 0, j = 0; i < n; i++) {
		ss[i] = (i & 1) == 0 ? '#' : a[j++];
	}
}
```

## **前缀树**


```c++
void insert(string word){
	int cur = 1;
	pass[cur]++;
	for (int i = 0, path; i < word.length(); i++) {
		path = word.charAt(i) - 'a';
		if (tree[cur][path] == 0) {
			tree[cur][path] = ++cnt;
		}
		cur = tree[cur][path];
		pass[cur]++;
	}
	end[cur]++;
}

int prefixNumber(String pre) {
	int cur = 1;
	for (int i = 0, path; i < pre.length(); i++) {
		path = pre.charAt(i) - 'a';
		if (tree[cur][path] == 0) {
			return 0;
		}
		cur = tree[cur][path];
	}
	return pass[cur];
}

void delete(String word) {
	if (search(word) > 0) {
		int cur = 1;
		for (int i = 0, path; i < word.length(); i++) {
			path = word.charAt(i) - 'a';
			if (--pass[tree[cur][path]] == 0) {
				tree[cur][path] = 0;
				return;
			}
			cur = tree[cur][path];
		}
		end[cur]--;
	}
}

void clear() {
	for (int i = 1; i <= cnt; i++) {
		Arrays.fill(tree[i], 0);
		end[i] = 0;
		pass[i] = 0;
	}
}
```



## **树状数组**

### 一维数组

#### **单点增加、范围查询**


```c++
int lowbit(int i){
	return i & -i;
}

 void add(int i, int v) {
	while (i <= n) {
		tree[i] += v;
		i += lowbit(i);
	}
}

// 返回1~i范围累加和
 int sum(int i) {
	int ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= lowbit(i);
	}
	return ans;
}

 int range(int l, int r) {
	return sum(r) - sum(l - 1);
}
```

#### 范围增加，单点查询

#####    将tree数组变成原数组的差分数组

#### **范围增加，范围查询**

```c++
// 维护原始数组的差分信息：Di
	public static long[] info1 = new long[MAXN];
// 维护原始数组的差分加工信息：(i-1) * Di
public static long[] info2 = new long[MAXN];

public static int n, m;

public static int lowbit(int i) {
	return i & -i;
}

void add(long[] tree, int i, long v) {
	while (i <= n) {
		tree[i] += v;
		i += lowbit(i);
	}
}

long sum(long[] tree, int i) {
	long ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= lowbit(i);
	}
	return ans;
}

// 原始数组中[l..r]每个数值+v
 void add(int l, int r, long v) {
	add(info1, l, v);
	add(info1, r + 1, -v);
	add(info2, l, (l - 1) * v);
	add(info2, r + 1, -(r * v));
}

// 原始数组中[l..r]范围上的累加和
 long range(int l, int r) {
	return sum(info1, r) * r - sum(info2, r) - sum(info1, l - 1) * (l - 1) + sum(info2, l - 1);
}
```

### 二维数组

#### 单点增加和范围查询

```c++
矩阵要从1，1开始
int lowbit(int i) {
		return i & -i;
	}

void add(int x, int y, int v) {
		for (int i = x; i <= n; i += lowbit(i)) {
			for (int j = y; j <= m; j += lowbit(j)) {
				tree[i][j] += v;
			}
		}
	}

	// 从(1,1)到(x,y)这个部分的累加和
 int sum(int x, int y) {
		int ans = 0;
		for (int i = x; i > 0; i -= lowbit(i)) {
			for (int j = y; j > 0; j -= lowbit(j)) {
				ans += tree[i][j];
			}
		}
		return ans;
	}
```

#### **范围增加和范围查询**

```c++
// 维护信息 : d[i][j]
int[][] info1 = new int[MAXN][MAXM];

// 维护信息 : d[i][j] * i
 int[][] info2 = new int[MAXN][MAXM];

// 维护信息 : d[i][j] * j
int[][] info3 = new int[MAXN][MAXM];

// 维护信息 : d[i][j] * i * j
int[][] info4 = new int[MAXN][MAXM];

public static int n, m;

 int lowbit(int i) {
	return i & -i;
}

 void add(int x, int y, int v) {
	int v1 = v;
	int v2 = x * v;
	int v3 = y * v;
	int v4 = x * y * v;
	for (int i = x; i <= n; i += lowbit(i)) {
		for (int j = y; j <= m; j += lowbit(j)) {
			info1[i][j] += v1;
			info2[i][j] += v2;
			info3[i][j] += v3;
			info4[i][j] += v4;
		}
	}
}

// 以(1,1)左上角，以(x,y)右下角
int sum(int x, int y) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {
			ans += (x + 1) * (y + 1) * info1[i][j] - (y + 1) * info2[i][j] - (x + 1) * info3[i][j] + info4[i][j];
		}
	}
	return ans;
}

 void add(int a, int b, int c, int d, int v) {
	add(a, b, v);
	add(a, d + 1, -v);
	add(c + 1, b, -v);
	add(c + 1, d + 1, v);
}

 int range(int a, int b, int c, int d) {
	return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
}
```

## KMP算法

```C++
#include<bits/stdc++.h>

using namespace std;

*const* int N=1e5+10;

int Next[N];

*//next[i]数组表示,前i-1个字符串的前后缀最大匹配长度*

*//s1是主串,s2是子串*

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

    *return* y==m?x-y:-1;

}



void get_NEXT(string s2){

    int n=s2.length();

    Next[0]=-1;

    Next[1]=0;

    int i=2,cn=0;

    while(i<n){

        if(s2[i-1]==s2[cn]){

            Next[i++]=++cn;//cn表示i-1的next值

        }else if(cn>0){

            cn=Next[cn];

        }else {

            Next[i++]=0;

        }

    }

}

int main(){

   *return* 0;

}
```

## 逆元求法

```C++
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

```



## ST表+倍增

```C++
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
尽可能接近的p 可以取长度的log2
// 区间查询 
i -> j
i -> i + 2的p次方(尽可能接近j)
j - 2的p次方(尽可能接近i) -> j
两个区间查询比较

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> num[i];
    return 0;
}
```



## 树上问题

## 前置知识(链式前向星建图)





### 树上倍增+LCA(最低公共祖先)



### 

```C++
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

```

### targin(最低公共祖先)

```C++
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

```

