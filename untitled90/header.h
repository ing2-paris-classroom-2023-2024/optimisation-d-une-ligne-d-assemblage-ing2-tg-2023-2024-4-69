//
// Created by maxim on 29/11/2023.
//

#ifndef UNTITLED90_HEADER_H
#define UNTITLED90_HEADER_H
#include <stdbool.h>

struct arcs {
    int sommet;
    int poids;
    struct arcs* arcSuivant;
};

typedef struct arcs* parc;

typedef struct sommets {
    parc arc;
    int valeur;
    int station;
} *p_s;

typedef struct graph {
    int taille;
    int ordre;
    p_s* sommets;
} graph;

typedef struct pred{
    int n_pred;
    int pred[100];
} pred;

p_s creationsommet(int numero);
void nouvelArc(p_s sommet, int suivant, int poids);
graph* creationG(int ordre);
void printGraph(graph* graphe);
int ordre_g(char* nomFichier);


void lectureF(graph* graphe, char* nomFichier);


void initprecedence(pred tab[], int ordre);
void rechercheprec(graph* graphe, pred tab[]);
void S_isoles(graph* graphe, bool s_isoles[graphe->ordre]);
void classer_op(graph* graphe, pred tab[], bool s_isoles[graphe->ordre]);


void print_stations(graph* graphe);
void print_op(graph* graphe);

#endif //UNTITLED90_HEADER_H
