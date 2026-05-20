// lab 10 Program for Tree traversal techniques.
#include <stdio.h>
int graph[20][20], visited[20], n;

void BFS(int start)
{
    int queue[20], front = 0, rear = 0, i;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    queue[rear++] = start;
    visited[start] = 1;
    printf("BFS Traversal: ");
    while (front < rear)
    {
        int node = queue[front++];
        printf("%d ", node);
        for (i = 0; i < n; i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS(int node)
{
    printf("%d ", node);
    visited[node] = 1;
    for (int i = 0; i < n; i++)
    {
        if (graph[node][i] == 1 && !visited[i])
            DFS(i);
    }
}

int main()
{
    int choice, start, i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix (0 or 1):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("\n1. BFS\n2. DFS\nEnter choice: ");
    scanf("%d", &choice);
    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    for (i = 0; i < n; i++)
        visited[i] = 0;

    if (choice == 1)
    {
        BFS(start);
    }
    else if (choice == 2)
    {
        printf("DFS Traversal: ");
        DFS(start);
        printf("\n");
    }
    else
    {
        printf("Invalid choice\n");
    }
    return 0;
}
Enter number of vertices and edges: 4 4
Enter edges (u v):
0 1
0 2
1 3
2 3
Enter starting vertex for BFS: 0

BFS Traversal starting from node 0:
0 1 2 3