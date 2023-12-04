#include "header.h"

// Fonction pour ajouter une arête au graphe
void ajouterArete(Graphe *graphe, int src, int dest) {
    Arc *newArc = (Arc *)malloc(sizeof(Arc));
    newArc->src = src;
    newArc->dest = dest;
    newArc->next = graphe->Arcs;
    graphe->Arcs = newArc;
}

int colorierStations(Graphe *graphe, int nbOperations) {
    int degre[MAX_OPERATIONS]; // Tableau pour stocker les degrés des sommets
    int couleurs[MAX_OPERATIONS]; // Tableau pour stocker les couleurs des opérations

    for (int i = 0; i < nbOperations; ++i) {
        degre[i] = 0;
        couleurs[i] = -1; // Initialisation des couleurs à -1 (non attribuées)
    }

    // Calcul des degrés de chaque sommet
    for (Arc *Arc = graphe->Arcs; Arc != NULL; Arc = Arc->next) {
        degre[Arc->src]++;
        degre[Arc->dest]++;
    }

    // Ordonner les sommets selon leur degré décroissant (tri par sélection)
    for (int i = 0; i < nbOperations - 1; ++i) {
        int maxdegre = -1;
        int maxdegreS = -1;

        for (int j = 0; j < nbOperations; ++j) {
            if (degre[j] > maxdegre) {
                maxdegre = degre[j];
                maxdegreS = j;
            }
        }

        // Mettre à jour le degré du sommet sélectionné pour ne pas le réutiliser
        degre[maxdegreS] = -1;

        // Coloration du sommet sélectionné
        int cr = 0;
        int couleursDispo[MAX_COLORS] = {0}; // Tableau pour marquer les couleurs disponibles

        for (Arc *Arc = graphe->Arcs; Arc != NULL; Arc = Arc->next) {
            if (Arc->src == maxdegreS || Arc->dest == maxdegreS) {
                if (couleurs[Arc->src] != -1) {
                    couleursDispo[couleurs[Arc->src]] = 1;
                }
                if (couleurs[Arc->dest] != -1) {
                    couleursDispo[couleurs[Arc->dest]] = 1;
                }
            }
        }

        while (couleursDispo[cr] == 1) {
            cr++;
        }

        couleurs[maxdegreS] = cr; // Attribution de la couleur disponible au sommet

        // Mettre à jour les couleurs disponibles pour les voisins
        for (Arc *Arc = graphe->Arcs; Arc != NULL; Arc = Arc->next) {
            if (Arc->src == maxdegreS || Arc->dest == maxdegreS) {
                if (couleurs[Arc->src] != -1) {
                    couleursDispo[couleurs[Arc->src]] = 0;
                }
                if (couleurs[Arc->dest] != -1) {
                    couleursDispo[couleurs[Arc->dest]] = 0;
                }
            }
        }
    }

    // Trouver le nombre de couleurs utilisées (stations formées)
    int nbStations = 0;
    for (int i = 0; i < nbOperations; ++i) {
        if (couleurs[i] > nbStations) {
            nbStations = couleurs[i];
        }
    }

    // Affichage des stations formées
    printf("Stations formees :\n");
    for (int i = 0; i <= nbStations; ++i) {
        printf("Station %d : ", i + 1);
        for (int j = 1; j < nbOperations; ++j) {
            if (couleurs[j] == i) {
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

    Graphe graphe;
    graphe.Arcs = NULL;

    int src, dest;
    int maxOperation = -1;

    while (fscanf(fichier, "%d %d", &src, &dest) == 2) {
        if (src > maxOperation) maxOperation = src;
        if (dest > maxOperation) maxOperation = dest;
        ajouterArete(&graphe, src, dest);
    }
    int nbOperations = maxOperation + 1;

    fclose(fichier);

    int nbStations = colorierStations(&graphe, nbOperations);
    printf("Nombre de stations : %d\n", nbStations);

    // Libérer la mémoire
    Arc *tempArc = graphe.Arcs;
    while (tempArc != NULL) {
        Arc *nextArc = tempArc->next;
        free(tempArc);
        tempArc = nextArc;
    }
}

int main() {
    fichier_exclusions();
    return 0;
}
