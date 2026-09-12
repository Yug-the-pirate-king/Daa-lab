#include <stdio.h>
#include <stdlib.h>

const int MAX_VERTICES = 20;
const int INF = 999;

// Global adjacency / distance matrix and graph dimensions.
int adjacency[MAX_VERTICES][MAX_VERTICES];
int numVertices = 0;
int numEdges = 0;

// Helper arrays shared by Johnson's reweighting and the multistage graph routine.
int vertexPotential[MAX_VERTICES];   // Johnson's h-values (kept at zero in this implementation)
int minCostToTarget[MAX_VERTICES];   // Minimum cost from vertex i to the sink
int nextVertexOnPath[MAX_VERTICES];  // Best successor of vertex i (multistage graph)

// Print the available algorithm choices.
void printMenu()
{
    printf("1. Floyd-Warshall\n2. Johnson\n3. Multistage Graph\n");
}

// Read a single integer with basic validation.
int readInteger(const char *prompt)
{
    int value;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1)
    {
        fprintf(stderr, "Error: expected an integer value.\n");
        exit(EXIT_FAILURE);
    }
    return value;
}

// Initialise the distance matrix: 0 on the diagonal, INF elsewhere.
void initializeDistanceMatrix()
{
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            adjacency[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// Read the edges and store them in the global adjacency matrix.
// Vertex indices are validated; weights must be valid for the chosen algorithm.
void readEdges(int algorithmChoice)
{
    printf("Enter edges (u v w):\n");

    for (int i = 0; i < numEdges; ++i)
    {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3)
        {
            fprintf(stderr, "Error: expected three integers for edge %d.\n", i + 1);
            exit(EXIT_FAILURE);
        }

        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        {
            fprintf(stderr, "Error: edge %d has a vertex outside range [0, %d].\n", i + 1, numVertices - 1);
            exit(EXIT_FAILURE);
        }

        if (w >= INF)
        {
            fprintf(stderr, "Error: edge weight must be less than %d.\n", INF);
            exit(EXIT_FAILURE);
        }

        if (algorithmChoice == 2 && w < 0)
        {
            fprintf(stderr, "Error: Johnson's algorithm requires non-negative edge weights.\n");
            exit(EXIT_FAILURE);
        }

        adjacency[u][v] = w;
    }
}

// Floyd-Warshall dynamic programming algorithm.
// Tries every vertex as an intermediate point and updates shortest paths.
void runFloydWarshall()
{
    for (int intermediate = 0; intermediate < numVertices; ++intermediate)
    {
        for (int source = 0; source < numVertices; ++source)
        {
            for (int destination = 0; destination < numVertices; ++destination)
            {
                int viaIntermediate = adjacency[source][intermediate] + adjacency[intermediate][destination];

                if (viaIntermediate < adjacency[source][destination])
                {
                    adjacency[source][destination] = viaIntermediate;
                }
            }
        }
    }
}

// Multistage graph dynamic programming.
// Assumes vertices are topologically ordered by stage; edges go from lower to higher indices.
void runMultistageGraph()
{
    // The sink vertex has zero cost by definition.
    minCostToTarget[numVertices - 1] = 0;

    // Process vertices in reverse order, accumulating the cheapest cost to the sink.
    for (int i = numVertices - 2; i >= 0; --i)
    {
        minCostToTarget[i] = INF;
        nextVertexOnPath[i] = -1;

        for (int j = i + 1; j < numVertices; ++j)
        {
            if (adjacency[i][j] != INF)
            {
                int candidate = adjacency[i][j] + minCostToTarget[j];

                if (candidate < minCostToTarget[i])
                {
                    minCostToTarget[i] = candidate;
                    nextVertexOnPath[i] = j;
                }
            }
        }
    }
}

// Dijkstra's single-source shortest path using the current reweighted edges.
// Stores the result for the given source in shortestDistances[].
void runDijkstra(int sourceVertex, int shortestDistances[])
{
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < numVertices; ++i)
    {
        shortestDistances[i] = INF;
    }
    shortestDistances[sourceVertex] = 0;

    for (int iteration = 0; iteration < numVertices - 1; ++iteration)
    {
        int minDistance = INF;
        int closestUnvisited = -1;

        // Select the unvisited vertex with the smallest tentative distance.
        for (int v = 0; v < numVertices; ++v)
        {
            if (!visited[v] && shortestDistances[v] < minDistance)
            {
                minDistance = shortestDistances[v];
                closestUnvisited = v;
            }
        }

        // No reachable unvisited vertex remains.
        if (closestUnvisited == -1)
        {
            break;
        }

        visited[closestUnvisited] = 1;

        // Relax all outgoing edges using the reweighted cost.
        for (int v = 0; v < numVertices; ++v)
        {
            if (!visited[v] && adjacency[closestUnvisited][v] != INF)
            {
                int reweightedEdge = adjacency[closestUnvisited][v]
                                     + vertexPotential[closestUnvisited]
                                     - vertexPotential[v];

                int candidate = shortestDistances[closestUnvisited] + reweightedEdge;

                if (candidate < shortestDistances[v])
                {
                    shortestDistances[v] = candidate;
                }
            }
        }
    }
}

// Johnson's all-pairs shortest path algorithm (simplified).
// Runs Dijkstra from every vertex and converts the reweighted distances back.
void runJohnsonsAlgorithm()
{
    int result[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < numVertices; ++i)
    {
        vertexPotential[i] = 0;
    }

    for (int i = 0; i < numVertices; ++i)
    {
        runDijkstra(i, result[i]);
    }

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (result[i][j] == INF)
            {
                adjacency[i][j] = INF;
            }
            else
            {
                adjacency[i][j] = result[i][j] - vertexPotential[i] + vertexPotential[j];
            }
        }
    }
}

// Print the all-pairs shortest-path matrix.
void printAllPairsShortestPaths()
{
    printf("\nAll pairs shortest paths:\n");

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (adjacency[i][j] == INF)
            {
                printf("INF ");
            }
            else
            {
                printf("%d ", adjacency[i][j]);
            }
        }

        printf("\n");
    }
}

int main()
{
    printMenu();

    int choice = readInteger("Enter choice: ");
    if (choice < 1 || choice > 3)
    {
        fprintf(stderr, "Error: choice must be 1, 2 or 3.\n");
        return EXIT_FAILURE;
    }

    printf("Enter vertices and edges: ");
    if (scanf("%d %d", &numVertices, &numEdges) != 2)
    {
        fprintf(stderr, "Error: expected two integers for vertices and edges.\n");
        return EXIT_FAILURE;
    }

    if (numVertices <= 0 || numVertices > MAX_VERTICES)
    {
        fprintf(stderr, "Error: number of vertices must be between 1 and %d.\n", MAX_VERTICES);
        return EXIT_FAILURE;
    }

    if (numEdges < 0 || numEdges > numVertices * numVertices)
    {
        fprintf(stderr, "Error: number of edges must be between 0 and %d.\n", numVertices * numVertices);
        return EXIT_FAILURE;
    }

    initializeDistanceMatrix();
    readEdges(choice);

    if (choice == 1)
    {
        runFloydWarshall();
    }
    else if (choice == 2)
    {
        runJohnsonsAlgorithm();
    }
    else if (choice == 3)
    {
        runMultistageGraph();
        printf("\nShortest path cost: %d\n", minCostToTarget[0]);
        return 0;
    }

    printAllPairsShortestPaths();
    return 0;
}