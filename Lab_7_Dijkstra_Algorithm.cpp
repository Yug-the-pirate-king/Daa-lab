#include <cstdio>
#define INF 999
#define MAX 20

int dist[MAX][MAX];
int n, e;

void dijkstra(int src)
{
    int output[MAX];
    int vis[MAX] = {0};

    for (int i = 0; i < n; i++)
    {
        output[i] = INF;
    }
    output[src] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int min = INF;
        int u = -1;

        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && output[j] < min)
            {
                min = output[j];
                u = j;
            }
        }

        if (u == -1)
        {
            break;
        }

        vis[u] = 1;

        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && dist[u][j] != INF && output[u] + dist[u][j] < output[j])
            {
                output[j] = output[u] + dist[u][j];
            }
        }
    }

    printf("\nShortest paths from Source Node %d:\n", src);
    printf("Vertex\tDistance\n");
    for (int i = 0; i < n; i++)
    {
        if (output[i] == INF)
            printf("%d \t INF\n", i);
        else
            printf("%d \t %d\n", i, output[i]);
    }
}

int main()
{
    int u, v, w, src;

    printf("Enter vertices and edges: ");
    if (scanf("%d %d", &n, &e) != 2 || n <= 0 || n > MAX || e < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
    {
        if (scanf("%d %d %d", &u, &v, &w) != 3 || u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge.\n");
            return 1;
        }
        dist[u][v] = w;
    }

    printf("Enter source vertex: ");
    if (scanf("%d", &src) != 1 || src < 0 || src >= n)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(src);

    return 0;
}