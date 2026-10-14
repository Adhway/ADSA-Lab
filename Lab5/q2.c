// Find the shortest paths between all pairs of vertices in a weighted directed graph using the 
// Floyd–Warshall algorithm,which uses dynamic programming and matrix multiplication concepts.

#include <stdio.h>

#define INF 99999

void floydWarshall(int graph[][100], int V) {
    int dist[100][100];

    // Step 1: Copy graph into distance matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Step 2: Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Step 3: Print shortest path matrix
    printf("\nAll-Pairs Shortest Path Matrix:\n\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    // Step 4: Check for negative cycle
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("\nGraph contains a negative-weight cycle.\n");
            return;
        }
    }
}

int main() {
    int V;
    int graph[100][100];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("\nEnter the adjacency matrix:\n");
    printf("(Use %d for INF/no edge)\n\n", INF);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, V);

    return 0;
}