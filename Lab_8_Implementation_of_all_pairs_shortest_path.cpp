#include <stdio.h>

const int MAX_VERTICES = 20;
const int INF = 999;

int numVertices, numEdges;
int distance[MAX_VERTICES][MAX_VERTICES];
int stageCost[MAX_VERTICES];
int nodePotential[MAX_VERTICES];

void initializeDistanceMatrix() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            distance[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void readGraphEdges() {
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < numEdges; i++) {
        int sourceVertex, destVertex, edgeWeight;
        scanf("%d %d %d", &sourceVertex, &destVertex, &edgeWeight);
        distance[sourceVertex][destVertex] = edgeWeight;
    }
}

void printDistanceMatrix() {
    printf("\nAll pairs shortest paths:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (distance[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", distance[i][j]);
            }
        }
        printf("\n");
    }
}

void computeFloydWarshall() {
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

void computeMultistageGraphCost() {
    stageCost[numVertices - 1] = 0;
    for (int i = numVertices - 2; i >= 0; i--) {
        stageCost[i] = INF;
        for (int j = i + 1; j < numVertices; j++) {
            if (distance[i][j] != INF && distance[i][j] + stageCost[j] < stageCost[i]) {
                stageCost[i] = distance[i][j] + stageCost[j];
            }
        }
    }
}

void runDijkstra(int sourceVertex, int outputRow[]) {
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < numVertices; i++) {
        outputRow[i] = INF;
    }
    outputRow[sourceVertex] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int minDistance = INF;
        int currentVertex = 0;
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && outputRow[j] < minDistance) {
                minDistance = outputRow[j];
                currentVertex = j;
            }
        }
        visited[currentVertex] = 1;
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && distance[currentVertex][j] != INF) {
                int adjustedWeight = distance[currentVertex][j] + nodePotential[currentVertex] - nodePotential[j];
                if (outputRow[currentVertex] + adjustedWeight < outputRow[j]) {
                    outputRow[j] = outputRow[currentVertex] + adjustedWeight;
                }
            }
        }
    }
}

void computeJohnsonsAllPairsShortestPaths() {
    int result[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        nodePotential[i] = 0;
    }

    for (int i = 0; i < numVertices; i++) {
        runDijkstra(i, result[i]);
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            distance[i][j] = (result[i][j] == INF) ? INF : (result[i][j] - nodePotential[i] + nodePotential[j]);
        }
    }
}

int main() {
    printf("1. Floyd-Warshall\n2. Johnson\n3. Multistage Graph\n");

    printf("Enter choice: ");
    int choice;
    scanf("%d", &choice);

    printf("Enter vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    initializeDistanceMatrix();
    readGraphEdges();

    if (choice == 1) {
        computeFloydWarshall();
    } else if (choice == 2) {
        computeJohnsonsAllPairsShortestPaths();
    } else if (choice == 3) {
        computeMultistageGraphCost();
        printf("\nShortest path cost: %d\n", stageCost[0]);
        return 0;
    }

    printDistanceMatrix();
    return 0;
}