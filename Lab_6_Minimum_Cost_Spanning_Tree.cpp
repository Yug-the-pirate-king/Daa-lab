#include <stdio.h>
#define INF 999

int cost[20][20], n, e;

// Structure to represent an edge for Kruskal's algorithm
struct Edge {
    int u, v, w;
} edges[40];

// --- KRUSKAL'S ALGORITHM HELPERS (Disjoint Set Union) ---
int parent[20];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void kruskalsMST() {
    int i, j, minCost = 0, edgesCount = 0;

    // Initialize DSU parent array
    for (i = 0; i < n; i++) parent[i] = i;

    // Simple Bubble Sort to sort edges by weight
    for (i = 0; i < e - 1; i++) {
        for (j = 0; j < e - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    printf("\nEdges in the MST (Kruskal's):\n");
    for (i = 0; i < e; i++) {
        // If roots are different, it doesn't form a cycle
        if (find(edges[i].u) != find(edges[i].v)) {
            printf("%d - %d: %d\n", edges[i].u, edges[i].v, edges[i].w);
            minCost += edges[i].w;
            unionSets(edges[i].u, edges[i].v);
            edgesCount++;
            if (edgesCount == n - 1) break;
        }
    }
    printf("Minimum Cost of Spanning Tree: %d\n", minCost);
}

// --- PRIM'S ALGORITHM ---
void primsMST() {
    int vis[20] = {0};
    int i, j, k, minCost = 0, edgesCount = 0;

    // Start with the first vertex (vertex 0)
    vis[0] = 1; 

    printf("\nEdges in the MST (Prim's):\n");
    while (edgesCount < n - 1) {
        int min = INF;
        int u = -1, v = -1;

        // Find the absolute minimum weight edge connecting visited to unvisited vertices
        for (i = 0; i < n; i++) {
            if (vis[i]) {
                for (j = 0; j < n; j++) {
                    if (!vis[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1) {
            printf("%d - %d: %d\n", u, v, min);
            minCost += min;
            vis[v] = 1;
            edgesCount++;
        }
    }
    printf("Minimum Cost of Spanning Tree: %d\n", minCost);
}

int main() {
    int choice, u, v, w, i, j;

    printf("1. Prim's Algorithm\n2. Kruskal's Algorithm\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &e);

    // Initialize cost matrix for Prim's
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INF;
        }
    }

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        
        // Since MST applies to Undirected Graphs, map it both ways
        cost[u][v] = w;
        cost[v][u] = w;

        // Save to edge array for Kruskal's
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    if (choice == 1) primsMST();
    else if (choice == 2) kruskalsMST();
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