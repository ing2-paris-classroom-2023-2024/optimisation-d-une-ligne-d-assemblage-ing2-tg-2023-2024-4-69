//
// Created by rapha on 20/11/2023.
//

#ifndef ECELECARTEST_HEADER_H
#define ECELECARTEST_HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100 // Modifier la taille maximum d'opérations si nécessaire
#define MAX_COLORS 100 // Nombre maximal de couleurs

// Structure pour représenter une arête dans le graphe
typedef struct Arc {
    int src;
    int dest;
    struct Arc *next;
} Arc;

// Structure pour représenter le graphe
typedef struct {
    Arc *Arcs;
} Graphe;

void ajouterArete(Graphe *graphe, int src, int dest);
int colorierStations(Graphe *graphe, int nbOperations);
void fichier_exclusions();


#endif //ECELECARTEST_HEADER_H
