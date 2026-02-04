#include <stdio.h>
#include <stdlib.h>

#define N1 8   // Taille du graphe non pondéré (BFS / DFS)
#define N2 7   // Taille du graphe pondéré (Dijkstra)
#define INF 1000000




typedef struct {
    int data[100];
    int front, rear;
} Queue;

void initQueue(Queue *q){
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q){
    return q->front == q->rear;
}

void enqueue(Queue *q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue *q){
    return q->data[q->front++];
}



   

void BFS(int graph[N1][N1], int start) {
    int visited[N1] = {0};
    Queue q;
    initQueue(&q);

    visited[start] = 1;
    enqueue(&q, start);

    printf("BFS à partir de %c : ", start + 'A');

    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        printf("%c ", u + 'A');

        for (int v = 0; v < N1; v++) {
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = 1;
                enqueue(&q, v);
            }
        }
    }
    printf("\n");
}



/*        DFS        */

void DFS(int graph[N1][N1], int visited[], int start)
{
    visited[start] = 1;
    printf("%c ", start + 'A');

    for (int v = 0; v < N1; v++) {
        if (graph[start][v] == 1 && !visited[v]) {
            DFS(graph, visited, v);
        }
    }
}



/*     DIJKSTRA      */

int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < N2; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[N2][N2], int source) {
    int dist[N2], visited[N2];

    for (int i = 0; i < N2; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < N2 - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < N2; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nDistances depuis A (Dijkstra) :\n");
    char nodes[N2] = {'A','B','C','D','E','F','G'};

    for (int i = 0; i < N2; i++) {
        printf("%c : %d\n", nodes[i], dist[i]);
    }
}



/*       MAIN        */

int main()
{
    // Graphe utilisé pour BFS / DFS
    int graph1[N1][N1] = {0};
    int edges[][2] = {
        {0,1},{0,2},{1,4},{2,4},{2,3},
        {4,5},{3,5},{3,6},{5,6},{5,7},{6,7}
    };
    int nbEdges = sizeof(edges)/sizeof(edges[0]);

    for (int i = 0; i < nbEdges; i++) {
        int a = edges[i][0], b = edges[i][1];
        graph1[a][b] = 1;
        graph1[b][a] = 1;
    }

    // Graphe pondéré pour Dijkstra
    int graph2[N2][N2] = {
        {0,1,2,0,0,0,0},
        {1,0,0,2,0,3,0},
        {2,0,0,3,4,0,0},
        {0,2,3,0,2,3,3},
        {0,0,4,2,0,0,5},
        {0,3,0,3,0,0,4},
        {0,0,0,3,5,4,0}
    };


    /******** MENU ********/
    int choix;
    do {
        printf("\n===== MENU GRAPHE =====\n");
        printf("1 - Parcours BFS\n");
        printf("2 - Parcours DFS\n");
        printf("3 - Algorithme de Dijkstra\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                BFS(graph1, 0); // depuis A
                break;

            case 2: {
                int visited[N1] = {0};
                printf("DFS à partir de A : ");
                DFS(graph1, visited, 0);
                printf("\n");
                break;
            }

            case 3:
                dijkstra(graph2, 0);
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
