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
