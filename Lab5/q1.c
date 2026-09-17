#include <stdio.h>

#define INF 99999

struct Edge {
    int src;
    int dest;
    int weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int source) {
    int dist[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }

    dist[source] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Step 3: Check for negative-weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("\nGraph contains a negative-weight cycle.\n");
            return;
        }
    }

    // Step 4: Print shortest distances
    printf("\nShortest distances from source vertex %d:\n", source);

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("Vertex %d : INF\n", i);
        else
            printf("Vertex %d : %d\n", i, dist[i]);
    }
}

int main() {
    int V, E, source;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    struct Edge edges[E];

    printf("\nEnter edges (source destination weight):\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    printf("\nEnter source vertex: ");
    scanf("%d", &source);

    bellmanFord(edges, V, E, source);

    return 0;
}