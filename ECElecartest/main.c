#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Modifier la taille maximum d'opérations si nécessaire
#define MAX_COLORS 100 // Nombre maximal de couleurs

// Structure pour représenter une arête dans le graphe
typedef struct Edge {
    int src;
    int dest;
    struct Edge *next;
} Edge;

// Structure pour représenter le graphe
typedef struct {
    Edge *edges;
} Graph;

// Structure pour représenter une opération avec sa couleur
typedef struct {
    int operation;
    int couleur;
} Operation;

// Fonction pour ajouter une arête au graphe
void ajouterArete(Graph *graph, int src, int dest) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->src = src;
    newEdge->dest = dest;
    newEdge->next = graph->edges;
    graph->edges = newEdge;
}

// Fonction pour colorier les opérations et former les stations
int colorierStations(Graph *graph, int nbOperations) {
    int colors[MAX_OPERATIONS]; // Tableau pour stocker les couleurs des opérations
    int availableColors[MAX_COLORS]; // Tableau pour marquer les couleurs disponibles

    for (int i = 0; i < nbOperations; ++i) {
        colors[i] = -1; // Initialisation des couleurs à -1 (non attribuées)
    }

    colors[0] = 0; // On attribue la couleur 0 à la première opération

    for (int i = 1; i < nbOperations; ++i) {
        for (Edge *edge = graph->edges; edge != NULL; edge = edge->next) {
            int src = edge->src;
            int dest = edge->dest;

            if (src == i) {
                if (colors[dest] != -1) {
                    availableColors[colors[dest]] = 1;
                }
            } else if (dest == i) {
                if (colors[src] != -1) {
                    availableColors[colors[src]] = 1;
                }
            }
        }

        int cr;
        for (cr = 0; cr < nbOperations; ++cr) {
            if (availableColors[cr] != 1) {
                break;
            }
        }

        colors[i] = cr; // Attribution de la couleur disponible à l'opération actuelle

        for (Edge *edge = graph->edges; edge != NULL; edge = edge->next) {
            int src = edge->src;
            int dest = edge->dest;

            if (src == i || dest == i) {
                if (colors[src] != -1) {
                    availableColors[colors[src]] = 0;
                }
                if (colors[dest] != -1) {
                    availableColors[colors[dest]] = 0;
                }
            }
        }
    }

    // Trouver le nombre de couleurs utilisées (stations formées)
    int nbStations = 0;
    for (int i = 1; i < nbOperations; ++i) {
        if (colors[i] > nbStations) {
            nbStations = colors[i];
        }
    }

    // Affichage des stations formées
    printf("Stations formees :\n");
    for (int i = 0; i <= nbStations; ++i) {
        printf("Station %d : ", i + 1);
        for (int j = 1; j < nbOperations; ++j) {
            if (colors[j] == i) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }

    return nbStations + 1; // Retourne le nombre de stations formées
}

void fichier_exclusions() {
    FILE *fichier = fopen("exclusions.txt", "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    Graph graph;
    graph.edges = NULL;

    int src, dest;
    int maxOperation = -1;

    while (fscanf(fichier, "%d %d", &src, &dest) == 2) {
        if (src > maxOperation) maxOperation = src;
        if (dest > maxOperation) maxOperation = dest;
        ajouterArete(&graph, src, dest);
    }
    int nbOperations = maxOperation + 1;

    fclose(fichier);

    int nbStations = colorierStations(&graph, nbOperations);
    printf("Nombre de stations : %d\n", nbStations);

    // Libérer la mémoire
    Edge *currentEdge = graph.edges;
    while (currentEdge != NULL) {
        Edge *nextEdge = currentEdge->next;
        free(currentEdge);
        currentEdge = nextEdge;
    }
}

int main() {
    fichier_exclusions();
    return 0;
}
