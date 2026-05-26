#include <stdio.h>

#define MAX 10

int graph[MAX][MAX];
int degree[MAX];
int color[MAX];
int visited[MAX];

int main() {
    int n, i, j, edges;

    printf("===== Railway Platform Allocation =====\n");
    printf("Using Welsh Powell Algorithm\n\n");

    printf("Enter number of trains: ");
    scanf("%d", &n);

    // Initialize graph
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("\nEnter number of conflicts between trains: ");
    scanf("%d", &edges);

    printf("\nEnter conflicting train pairs:\n");
    printf("(Example: 1 2 means Train 1 conflicts with Train 2)\n\n");

    // Input edges
    for(i = 0; i < edges; i++) {
        int u, v;

        printf("Conflict %d: ", i + 1);
        scanf("%d %d", &u, &v);

        graph[u-1][v-1] = 1;
        graph[v-1][u-1] = 1;
    }

    // Calculate degree of each train
    for(i = 0; i < n; i++) {
        degree[i] = 0;

        for(j = 0; j < n; j++) {
            if(graph[i][j] == 1) {
                degree[i]++;
            }
        }
    }

    // Initialize colors
    for(i = 0; i < n; i++) {
        color[i] = 0;
        visited[i] = 0;
    }

    int currentColor = 1;

    // Welsh Powell Coloring
    while(1) {

        int maxDegree = -1;
        int vertex = -1;

        // Find unvisited train with highest degree
        for(i = 0; i < n; i++) {
            if(!visited[i] && degree[i] > maxDegree) {
                maxDegree = degree[i];
                vertex = i;
            }
        }

        // All trains colored
        if(vertex == -1)
            break;

        color[vertex] = currentColor;
        visited[vertex] = 1;

        // Assign same color to non-conflicting trains
        for(i = 0; i < n; i++) {

            if(!visited[i]) {

                int canColor = 1;

                for(j = 0; j < n; j++) {

                    if(color[j] == currentColor && graph[i][j] == 1) {
                        canColor = 0;
                        break;
                    }
                }

                if(canColor) {
                    color[i] = currentColor;
                    visited[i] = 1;
                }
            }
        }

        currentColor++;
    }

    // Output
    printf("\n===== Platform Allocation =====\n\n");

    for(i = 0; i < n; i++) {
        printf("Train %d ---> Platform %d\n", i + 1, color[i]);
    }

    printf("\nTotal Platforms Required = %d\n", currentColor - 1);

    return 0;
}