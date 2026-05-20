#include <stdio.h>
#define INF 999

int dist[20][20], n, e;

void dijkstra(int src)
{
    int output[20], vis[20] = {0};
    int i, j, u;

    for (i = 0; i < n; i++)
    {
        output[i] = INF;
    }
    output[src] = 0;

    for (i = 0; i < n - 1; i++)
    {
        int min = INF;

        for (j = 0; j < n; j++)
        {
            if (!vis[j] && output[j] < min)
            {
                min = output[j];
                u = j;
            }
        }

        vis[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (!vis[j] && dist[u][j] != INF && output[u] + dist[u][j] < output[j])
            {
                output[j] = output[u] + dist[u][j];
            }
        }
    }

    printf("\nShortest paths from Source Node %d:\n", src);
    printf("Vertex\tDistance\n");
    for (i = 0; i < n; i++)
    {
        if (output[i] == INF)
            printf("%d \t INF\n", i);
        else
            printf("%d \t %d\n", i, output[i]);
    }
}

int main()
{
    int u, v, w, i, j, src;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &e);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = w;
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(src);

    return 0;
}

// Enter vertices and edges: 4 5  
// Enter edges (u v w): 
// 0 1 4                                                                      
// 0 2 1                     
// 2 1 2                                                                      
// 1 3 1                     
// 2 3 5
// Enter source vertex: 0

// Shortest paths from Source Node 0:
// Vertex  Distance
// 0        0
// 1        3
// 2        1
// 3        4