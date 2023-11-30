#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


// création d'un nouveau sommet
p_s creationsommet(int numero) {
    p_s sommet = (p_s)malloc(sizeof(struct sommets));
    sommet->valeur = numero;
    sommet->arc = NULL;
    sommet->station = 0;
    return sommet;
}

//ajout d'un arc au graphe
void nouvelArc(p_s sommet, int suivant, int poids) {
    parc nouvelArc = (parc)malloc(sizeof(struct arcs));
    nouvelArc->sommet = suivant;
    nouvelArc->poids = poids;
    nouvelArc->arcSuivant = sommet->arc;
    sommet->arc = nouvelArc;
}

//création du graphe
graph* creationG(int ordre) {
    graph* graphe = (graph*)malloc(sizeof(graph));
    graphe->taille = 0;
    graphe->ordre = ordre;
    graphe->sommets = (p_s*)malloc(ordre * sizeof(p_s));
    for (int i = 0; i < ordre; i++) {
        graphe->sommets[i] = creationsommet(i+1);
    }
    return graphe;
}

//lecture du fichier
void lectureF(graph* graphe, char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    int source, destination;
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    while (fscanf(fichier, "%d %d", &source, &destination) != EOF) {
        nouvelArc(graphe->sommets[source-1], destination, 0);
        graphe->taille++;
    }
    fclose(fichier);
}

/*void printGraph(graph* graphe) {
    printf("Graph :\n");
    for (int j=0; j<graphe->ordre; j++) {
        parc curent = graphe->sommets[j]->arc;
        printf("sommets %d:", graphe->sommets[j]->valeur);
        while (curent != NULL) {
            printf(" %d", curent->sommet);
            curent = curent->arcSuivant;
        }
        printf("\n");
    }
}*/

//déterminer l'ordre_g
int ordre_g(char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    int ordre = 0;
    int source, destination;
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
    while (fscanf(fichier, "%d %d", &source, &destination) != EOF) {
        if (source > ordre){
            ordre = source;
        }
        if (destination > ordre) {
            ordre = destination;
        }
    }
    fclose(fichier);
    return ordre;
}


// initialiser la précédence
void initprecedence(pred tab[], int ordre) {
    for (int i = 0; i < ordre; i++) {
        tab[i].n_pred = 0;
    }
}

// recherche des taches precedentes
void rechercheprec(graph* graphe, pred tab[]) {
    for (int i = 0; i < graphe->ordre; i++) {
        parc arc = graphe->sommets[i]->arc;
        while (arc != NULL) {
            int ipred = arc->sommet - 1;
            tab[ipred].pred[tab[ipred].n_pred++] = i;
            arc = arc->arcSuivant;
        }
    }
}

//trouver des sommets isolés
void S_isoles(graph* graphe, bool s_isoles[graphe->ordre]) {
    for (int i = 0; i < graphe->ordre; i++) {
        s_isoles[i] = true;
    }
    for (int i = 0; i < graphe->ordre; i++) {
        parc arc = graphe->sommets[i]->arc;
        while (arc != NULL) {
            s_isoles[i] = false;
            s_isoles[arc->sommet-1] = false;
            arc = arc->arcSuivant;
        }
    }
}


//classer les tâches dans des stations
void classer_op(graph* graphe, pred tab[], bool s_isoles[graphe->ordre]) {
    int curent = 1;
    bool tache[graphe->ordre];
    for (int i = 0; i < graphe->ordre; i++) {
        tache[i] = s_isoles[i];
    }
    for (int i = 0; i < graphe->ordre; i++) {
        if (!tache[i] && tab[i].n_pred == 0) {
            graphe->sommets[i]->station = curent;
            tache[i] = true;
        }
    }
    while (curent < graphe->ordre) {
        bool c =false;
        curent++;
        for (int i = 0; i < graphe->ordre; i++) {
            if (!tache[i]) {
                bool t_pred = true;
                for (int j = 0; j < tab[i].n_pred; j++) {
                    int pred = tab[i].pred[j];
                    if (graphe->sommets[pred]->station == 0 || graphe->sommets[pred]->station >= curent) {
                        t_pred = false;
                        break;
                    }
                }
                if (t_pred) {
                    graphe->sommets[i]->station = curent;
                    tache[i] = true;
                    c = true;
                }
            }
        }
        if (!c) {
            break;
        }
    }
}

//affichage
void print_stations(graph* graphe) {
    printf("Affichage des Sommets :\n");
    for (int station = 1; station <= graphe->ordre; station++) {
        bool vide = true;
        for (int i = 0; i < graphe->ordre; i++) {
            if (graphe->sommets[i]->station == station) {
                vide = false;
                break;
            }
        }
        if (!vide) {
            printf(" ", station);
            for (int i = 0; i < graphe->ordre; i++) {
                if (graphe->sommets[i]->station == station) {
                    printf("%d ", graphe->sommets[i]->valeur);
                }
            }
            printf("\n");
        }
    }
}


int main() {
    char nomFichier[100];
    printf("nom du fichier: ");
    scanf("%s", nomFichier);

    int ordre = ordre_g(nomFichier);
    if (ordre == -1) return 1;

    graph* graphe = creationG(ordre);
    printf("Ordre: %d\n", graphe->ordre);
    lectureF(graphe, nomFichier);
    //printGraph(graphe);

    pred Precedent[graphe->ordre];
    initprecedence(Precedent, graphe->ordre);
    rechercheprec(graphe, Precedent);
    bool s_isoles[graphe->ordre];
    S_isoles(graphe, s_isoles);
    classer_op(graphe, Precedent, s_isoles);

    print_stations(graphe);


    return 0;
}