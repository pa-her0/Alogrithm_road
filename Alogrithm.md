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

// 预处理
void manacherss(char[] a) {
	n = a.length * 2 + 1;
	for (int i = 0, j = 0; i < n; i++) {
		ss[i] = (i & 1) == 0 ? '#' : a[j++];
	}
}
```

## **前缀树**


```c++
int cnt=1; // 层次编号
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

next数组: 快速匹配数组，没匹配上则跳到前一个next值来进行匹配，用于匹配问题 (前后缀的匹配程度)

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

## 逆元求法(除法同余)

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

## 



## 矩阵快速幂

```c++
// * 重点： 关系矩阵
/*
递推式子中有n个表达式 就是 n*n的关系矩阵
第 0 列是递推表达式的关系系数
【m -> m+n】*关系矩阵(n*n) =[m+1 -> m+n+1] 
*/
vector<vector<int>> multipy(vector<vector<int>> &a,vector<vector<int>> &b){
    int n = a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));

    for (int i = 0; i<n;i++){
        for(int j=0;j<m;j++){
            for(int c=0;c<k;c++){
                ans[i][j]+=a[i][c]*b[c][j];
            }
        }
    }
    return ans;
}

vector<vector<int>> pow(vector<vector<int>> &m,int p){
    int n = m.size();
    vector<vector<int>> ans(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        ans[i][i]=1;
    }
    for(;p!=0;p>>=1){
        if((p&1)!=0){
            ans =multipy(ans,m);
        }
        m=multipy(m,m);
    }
    return ans;
}
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

### 前置知识(链式前向星建图)

```C++
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
```



### 树上倍增+LCA(最低公共祖先)

------



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

## 

### 树的直径

```c++
using namespace std;
// 直径：树上距离最远的两个点

/*
  1，两次 dfs (仅适用非负边权)  *可以得到这条直径的相关节点信息
   （1) 随便选一个点 找最远的点
    (2) 从最远的点 dfs
  2， 树型dp (使用于所有树)  *只能得到树的直径长度

  树上边权都为正的结论：
  1，如果有多条直径 直径一定有共同的中间部分 (点或者路径)
  2，树上任意一点的最远点的集合，直径的端点至少有一个在集合中
*/

//|||||||||||||||||||||||||||||
// 方法1

// 链式前向星建图
// 链式前向星建图
const int N = 1e6 + 10;
int cnt = 0;
int head[N];
struct
{
    int to, next, w;
} edge[N];

void init()
{
    for (int i = 0; i < N; i++)
        head[i] = 0;
    for (int i = 0; i < N; i++)
        edge[i].next = 0;
    cnt = 1;
}
void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}


// 直径的开始点
int start;

// 直径的结束点
int End;

// 直径的长度
int diameter;

// 从头结点出发，到 i 的距离
int dist[N];

// i节点的上一个节点
int last[N];

int n; // n 个点
void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int e=head[u];e!=0;e=edge[e].next){
        if(edge[e].to!=f){
            dfs(edge[e].to,u,edge[e].w);
        }
    }
}

void longest_road(){
    dfs(1,0,0);
    start = 1;
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[start]) start=i;
    }
    dfs(start,0,0);
    End=1;
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[End]) End=i;
    }
    diameter = dist[End];
}

// 方法2
// Dist[u] 从u节点往下走 能走出的最大距离
int Dist[N];

// ans[u] 路径包括u的最大路径和
int ans[N];

void dp(int u,int f){
    for(int e=head[u],v;e>0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dp(v,u);
       }
       }
       for(int e=head[u],v;e>0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            diameter=max(diameter,Dist[u]+Dist[v]+edge[e].w);
            Dist[u]=max(Dist[u],Dist[v]+edge[e].w);
        }
       }

}
int main(){
    cin >>n;
    init();diameter=INT_MIN;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    //longest_road();
    dp(1,0);
    cout<<diameter<<endl;
    return 0;
}
```



### 树的重心

#### 不带点权

```C++
/*
  重心的定义：
     1，最大子树的节点数最少
     2，每颗子树的节点数不超过总结点的一半
     3，以重心为根时，所有节点走向该节点的总边数最少
  重心的性质：
     1，树上有重心，两个重心一定相邻
     2，树上增加或者删除叶子节点，转移的重心最多移动一条边
     3，两棵树连起来，新树的重心一定在原来两棵树的重心的路径上
     4，如果是正边权，所有节点走向重心的总距离和最小
*/
#include<bits/stdc++.h>
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

// 定义1 最大子树的节点个数最少
int Size[N];// i节点的子树大小
int best=INT_MAX,center;
int n;

void dfs(int u,int f){
    Size[u]=1;
    int maxSub=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            dfs(v,u);
            Size[u]+=Size[v];
            maxSub=max(maxSub,Size[v]); //取子树的maxsub
        }
    }
    maxSub=max(maxSub,n-Size[u]); // 取自己的maxsub
    if(maxSub<best||(maxSub==best&&u<center)){
        best=maxSub;
        center=u;
    }
}

// 定义2
int MaxSub[N];
int SIZE[N];
void dfs(int u,int f){
    SIZE[u]=1;
    MaxSub[u]=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dfs(v,u);
        SIZE[u]+=SIZE[v];
        MaxSub[u]=max(MaxSub[u],SIZE[v]);
       }
    }
    MaxSub[u]=max(MaxSub[u],n-SIZE[u]);
}
int main(){
    return 0;
}
```



#### 带点权

```c++
#include<bits/stdc++.h>
using namespace std;
// 带点权求重心


// 链式前向星建图
const int N = 1e6 + 10;
int cnt = 0;
int head[N];
struct
{
    int to, next, w;
} edge[N];

void init()
{
    for (int i = 0; i < N; i++)
        head[i] = 0;
    for (int i = 0; i < N; i++)
        edge[i].next = 0;
    cnt = 1;
}
void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int best=INT_MAX,center;
int Size[N];
int path[N];

int n;
int cow[N];
int cowSum=0;


void dfs(int u,int f){
    Size[u]=cow[u];
    int maxSub=0;
    for(int e=head[u],v;e!=0;e=edge[e].next){
       v=edge[e].to;
       if(v!=f){
        dfs(v,u);
        Size[u]+=Size[v];
        maxSub=max(maxSub,Size[v]);
       }
    }
    maxSub=max(maxSub,cowSum-Size[u]);
    if(maxSub<best){
        best=maxSub;
        center=u;
    }
}

void dfs_road(int u,int f){
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            path[v]=path[u]+edge[e].w;
            dfs_road(v,u);
        }
    }
}
int main(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
       cin>>cow[i];
       cowSum+=cow[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    path[center]=0;
    dfs_road(center,0);
    long long sum=0;
    // for(int i=1;i<=n;i++){
    //     cout<<path[i]<<" "<<cow[i]<<endl;
    // }
    for(int i=1;i<=n;i++){
        sum+=path[i]*cow[i];
    }
    cout<<sum<<endl;
    return 0;
}
```



### 树上差分

```C++
#include<bits/stdc++.h>
using namespace std;
/*
  树上点差分
  a -> b 路径上增加 v
  a+v b+v lca(最低公共祖先)-v lca的父亲节点-v
  a的权重 = a的权重 + a的所有节点的权重
  
  树上边差分
  a -> b
  a+v b+v lca-2*v
*/

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
        head[i] = 0;
    for (int i = 0; i < N; i++)
        edge[i].next = 0;
    cnt = 1;
}
void addedge(int u, int v)
{
    edge[cnt].to = v;
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
long long ans[N];
void dfs2(int u,int f){
    for(int e=head[u],v;e!=0;e=edge[e].next){
        v=edge[e].to;
        if(v!=f){
            dfs2(v,u);
            ans[u]+=ans[v];
        }
    }
}
int n,K;
int main(){
    cin>>n>>K;
    build(n);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    
    dfs(1,0);
    for(int i=0;i<K;i++){
        int a,b,Lca,father;
        cin>>a>>b;
        Lca=lca(a,b);
        father=STjump[Lca][0];
        ans[a]++;ans[b]++;ans[Lca]--;ans[father]--;
    }
    long long Max=0;
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        Max=max(Max,ans[i]);
    }
    cout<<Max<<endl;
    return 0;
}
```







## 线性基

###  普通线性基

```c++
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

  
```



### 标准线性基

```c++
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

```



### 空间向量线性基

```

```



## 高斯消元

高斯消元 加法和异或同理

```C++
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
```



## 01 分数规划

```

```



## DP问题

### 区间dp

```

```

### 树形dp

```

```



### 状压dp

```

```



### 数位dp

```

```



### 轮廓线dp

```

```



### 三进制状压dp

```

```



## 图论

### 离散化(模板)

```C++
int old[N];
int New[N];
int n;
    for(int i=1;i<=n;i++) {
        cin>>old[i];
        New[i]=old[i];
        }
        sort(old,old+n);
    int cnt=n;
    cnt=unique(old+1,old+1+n)-(old+1);
    for(int i=1;i<=cnt;i++){
        New[i]=lower_bound(old+1,old+1+n,New[i])-old;
    }

    for(int i=1;i<=cnt;i++) cout<<New[i]<<" ";//每个值在原始位置的大小
```



### 并查集

```C++
const int N = 1e5 + 10;
int father[N];
// 初始化并查集
void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
}
// 查找元素的根，并进行路径压缩
int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}
// 判断两个元素是否属于同一个集合
bool isSameSet(int x, int y) {
    return find(x) == find(y);
}
// 合并两个集合
void unite(int x, int y) {
    father[find(x)] = find(y);
}

```



### 最小生成树

##### kruksal算法

```C++
#include <bits/stdc++.h>
using namespace std;

// 并查集模板

const int N = 1e5 + 10;
int father[N];

// 初始化并查集
void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
}

// 查找元素的根，并进行路径压缩
int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 判断两个元素是否属于同一个集合
bool isSameSet(int x, int y) {
    return find(x) == find(y);
}

// 合并两个集合
void unite(int x, int y) {
    father[find(x)] = find(y);
}

// 最小生成树 (Kruskal 算法)
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const { // 通过这个改变sort的排序顺序
        return weight < other.weight;
    }
};

vector<Edge> edges;

int kruskal(int n, int m) {
    // n: 顶点数, m: 边数
    build(n); // 初始化并查集
    sort(edges.begin(), edges.end()); // 按照权重排序边

    int mst_weight = 0;
    int edges_used = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (!isSameSet(u, v)) {
            unite(u, v);
            mst_weight += weight;
            edges_used++;
            if (edges_used == n - 1) {
                break;
            }
        }
    }
    return mst_weight;
}

```



### DIjkstra算法

```C++
/ 最短路径 (Dijkstra 算法)
const int INF = 1e9;
vector<pair<int, int>> adj[N]; // 邻接节点和权重

vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, INF);
    dist[start] = 0;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // 默认用pair的first来比较，相等则用second来比较
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

```



### 分层图最短路

```

```



### Floyd算法

```C++
for(int k=1;k<=n;k++){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
        }
    }
}
```



### SPFA

```C++
// 最短路径 (SPFA 算法)
vector<int> spfa(int start, int n) {
    vector<int> dist(n, INF);
    vector<bool> in_queue(n, false);
    queue<int> q;

    dist[start] = 0;
    q.push(start);
    in_queue[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dist;
}

```



### 拓扑排序

------

通过 节点的入度大小来构建优先队列来实现