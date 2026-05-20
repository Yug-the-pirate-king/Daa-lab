#include <stdio.h>
#define INF 999

int dist[20][20], n, e;
int cost[20], path[20], h[20]; // Shared helpers for Multistage & Johnson

void floydWarshall()
{
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void multistageGraph()
{
    int i, j;
    cost[n - 1] = 0;
    for (i = n - 2; i >= 0; i--)
    {
        cost[i] = INF;
        for (j = i + 1; j < n; j++)
        {
            if (dist[i][j] != INF && dist[i][j] + cost[j] < cost[i])
                cost[i] = dist[i][j] + cost[j];
        }
    }
}

void dijkstra(int src, int outputRow[])
{
    int vis[20] = {0}, i, j, u;
    for (i = 0; i < n; i++)
        outputRow[i] = INF;
    outputRow[src] = 0;

    for (i = 0; i < n - 1; i++)
    {
        int min = INF;
        for (j = 0; j < n; j++)
        {
            if (!vis[j] && outputRow[j] < min)
            {
                min = outputRow[j];
                u = j;
            }
        }
        vis[u] = 1;
        for (j = 0; j < n; j++)
        {
            if (!vis[j] && dist[u][j] != INF)
            {
                int weight = dist[u][j] + h[u] - h[j];
                if (outputRow[u] + weight < outputRow[j])
                    outputRow[j] = outputRow[u] + weight;
            }
        }
    }
}

void johnsonsAlgorithm()
{
    int i, j, result[20][20];
    for (i = 0; i < n; i++)
        h[i] = 0;
    for (i = 0; i < n; i++)
        dijkstra(i, result[i]);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = (result[i][j] == INF) ? INF : (result[i][j] - h[i] + h[j]);
}

int main()
{
    printf("1. Floyd-Warshall\n2. Johnson\n3. Multistage Graph\n");
    int choice, u, v, w, i, j;

    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &e);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : INF;
    }

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = w;
    }

    if (choice == 1)
    {
        floydWarshall();
    }
    else if (choice == 2)
    {
        johnsonsAlgorithm();
    }
    else if (choice == 3)
    {
        multistageGraph();
        printf("\nShortest path cost: %d\n", cost[0]);
        return 0; // Multistage usually prints a single scalar result
    }

    printf("\nAll pairs shortest paths:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Enter vertices and edges: 4 5
// Enter edges (u v w):
// 0 1 4
// 0 2 1
// 2 1 2
// 1 3 1
// 2 3 5