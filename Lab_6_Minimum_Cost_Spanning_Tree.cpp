#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

const int INF = INT_MAX / 4;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    std::vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank[a] < rank[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        parent[b] = a;
        if (rank[a] == rank[b]) ++rank[a];
    }
};

void kruskalsMST(const std::vector<Edge>& edgeList, int n) {
    std::vector<Edge> edges = edgeList;
    std::stable_sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long minCost = 0;
    int edgesCount = 0;

    printf("\nEdges in the MST (Kruskal's):\n");
    for (const auto& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            printf("%d - %d: %d\n", e.u, e.v, e.w);
            minCost += e.w;
            dsu.unite(e.u, e.v);
            ++edgesCount;
            if (edgesCount == n - 1) break;
        }
    }

    if (edgesCount != n - 1) {
        printf("Graph is disconnected. No spanning tree exists.\n");
    } else {
        printf("Minimum Cost of Spanning Tree: %lld\n", minCost);
    }
}

void primsMST(const std::vector<std::vector<int>>& cost, int n) {
    std::vector<int> vis(n, 0);
    long long minCost = 0;
    int edgesCount = 0;

    vis[0] = 1;

    printf("\nEdges in the MST (Prim's):\n");
    while (edgesCount < n - 1) {
        int min = INF;
        int u = -1, v = -1;

        for (int i = 0; i < n; ++i) {
            if (vis[i]) {
                for (int j = 0; j < n; ++j) {
                    if (!vis[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1 || v == -1) {
            printf("Graph is disconnected. No spanning tree exists.\n");
            return;
        }

        printf("%d - %d: %d\n", u, v, min);
        minCost += min;
        vis[v] = 1;
        ++edgesCount;
    }

    printf("Minimum Cost of Spanning Tree: %lld\n", minCost);
}

int main() {
    int choice;
    printf("1. Prim's Algorithm\n2. Kruskal's Algorithm\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int n, e;
    printf("Enter vertices and edges: ");
    if (scanf("%d %d", &n, &e) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n <= 0 || e < 0) {
        printf("Invalid number of vertices or edges.\n");
        return 1;
    }

    long long maxEdges = 1LL * n * (n - 1) / 2;
    if (e > maxEdges) {
        printf("Too many edges for %d vertices.\n", n);
        return 1;
    }

    std::vector<std::vector<int>> cost(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i) cost[i][i] = 0;

    std::vector<Edge> edges;
    edges.reserve(e);

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            printf("Invalid edge input.\n");
            return 1;
        }
        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Vertex index out of range.\n");
            return 1;
        }

        if (u != v && w < cost[u][v]) {
            cost[u][v] = w;
            cost[v][u] = w;
        }
        edges.push_back({u, v, w});
    }

    if (choice == 1) primsMST(cost, n);
    else if (choice == 2) kruskalsMST(edges, n);
    else printf("Invalid choice!\n");

    return 0;
}

// 1. Prim's Algorithm Test Run
// Enter choice: 1
// Enter vertices and edges: 4 5
// Enter edges (u v w):
// 0 1 10
// 0 2 6
// 0 3 5
// 1 3 15
// 2 3 4
//
// Edges in the MST:
// 0 - 3 	 5
// 3 - 2 	 4
// 0 - 1 	 10
// Minimum Cost of Spanning Tree: 19

// 2. Kruskal's Algorithm Test Run
// Enter choice: 2
// Enter vertices and edges: 4 5
// Enter edges (u v w):
// 0 1 10
// 0 2 6
// 0 3 5
// 1 3 15
// 2 3 4
//
// Edges in the MST:
// 2 - 3 	 4
// 0 - 3 	 5
// 0 - 1 	 10
// Minimum Cost of Spanning Tree: 19