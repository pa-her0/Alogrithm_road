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

public static int prefixNumber(String pre) {
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

public static void delete(String word) {
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

public static void clear() {
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

*//next[i]数组表示，前i-1个字符串的前后缀最大匹配长度*

*//s1是主串，s2是子串*

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

            Next[i++]=++cn;

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

