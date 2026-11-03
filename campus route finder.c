
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define V 8

// Structure for adjacency list
struct Node {
    int vertex;
    struct Node *next;
};

// Graph structure
struct Node *adj[V];

// Campus location names
char locations[V][30];

// Initialize graph
void initializeGraph() {
    char names[V][30] = {
        "Main Gate",
        "Library",
        "Block 1",
        "Block 2",
        "Cafeteria",
        "Auditorium",
        "Parking",
        "Lab"
    };

    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        strcpy(locations[i], names[i]);
    }
}

// Add an edge between two locations
void addEdge(int u, int v) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Display all campus locations
void displayLocations() {
    printf("\nCampus Locations:\n");

    for (int i = 0; i < V; i++) {
        printf("%d. %s\n", i, locations[i]);
    }
}

// Display graph using adjacency list
void displayGraph() {
    printf("\nCampus Graph (Adjacency List):\n");

    for (int i = 0; i < V; i++) {
        struct Node *temp = adj[i];

        printf("%s -> ", locations[i]);

        while (temp != NULL) {
            printf("%s -> ", locations[temp->vertex]);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// Breadth First Search
void BFS(int start, int destination) {
    int visited[V] = {0};
    int parent[V];
    int queue[V];
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
    }

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        if (current == destination) {
            break;
        }

        struct Node *temp = adj[current];

        while (temp != NULL) {
            int next = temp->vertex;

            if (!visited[next]) {
                visited[next] = 1;
                parent[next] = current;
                queue[rear++] = next;
            }

            temp = temp->next;
        }
    }

    if (!visited[destination]) {
        printf("\nNo route exists between these locations!\n");
        return;
    }

    // Reconstruct shortest path
    int path[V];
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    printf("\nShortest Route using BFS:\n");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", locations[path[i]]);

        if (i != 0) {
            printf(" -> ");
        }
    }

    printf("\nMinimum number of edges: %d\n", count - 1);
}

// Depth First Search
void DFS(int start, int visited[]) {
    visited[start] = 1;

    printf("%s -> ", locations[start]);

    struct Node *temp = adj[start];

    while (temp != NULL) {
        int next = temp->vertex;

        if (!visited[next]) {
            DFS(next, visited);
        }

        temp = temp->next;
    }
}

// Display reachable and disconnected locations
void checkConnectivity(int start) {
    int visited[V] = {0};

    printf("\nLocations reachable from %s:\n",
           locations[start]);

    DFS(start, visited);

    printf("END\n");

    printf("\nDisconnected Locations:\n");

    int found = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            printf("%s\n", locations[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No disconnected locations.\n");
    }
}

// Free allocated memory
void freeGraph() {
    for (int i = 0; i < V; i++) {
        struct Node *temp = adj[i];

        while (temp != NULL) {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }

        adj[i] = NULL;
    }
}

// Main function
int main() {
    int choice, start, destination;

    initializeGraph();

    // Create campus connections
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(4, 6);
    addEdge(5, 7);
    addEdge(6, 7);

    do {
        printf("\n====================================\n");
        printf("       CAMPUS ROUTE FINDER\n");
        printf("====================================\n");

        printf("1. Display Campus Locations\n");
        printf("2. Display Graph\n");
        printf("3. Find Shortest Route using BFS\n");
        printf("4. Explore Locations using DFS\n");
        printf("5. Check Disconnected Locations\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {

            case 1:
                displayLocations();
                break;

            case 2:
                displayGraph();
                break;

            case 3:
                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                printf("Enter destination location number: ");
                scanf("%d", &destination);

                if (start < 0 || start >= V ||
                    destination < 0 || destination >= V) {
                    printf("Invalid location number!\n");
                }
                else {
                    BFS(start, destination);
                }
                break;

            case 4: {
                int visited[V] = {0};

                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                if (start < 0 || start >= V) {
                    printf("Invalid location number!\n");
                }
                else {
                    printf("\nDFS Traversal:\n");
                    DFS(start, visited);
                    printf("END\n");
                }
                break;
            }

            case 5:
                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                if (start < 0 || start >= V) {
                    printf("Invalid location number!\n");
                }
                else {
                    checkConnectivity(start);
                }
                break;

            case 6:
                printf("\nExiting Campus Route Finder...\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 6);

    freeGraph();

    return 0;
}
