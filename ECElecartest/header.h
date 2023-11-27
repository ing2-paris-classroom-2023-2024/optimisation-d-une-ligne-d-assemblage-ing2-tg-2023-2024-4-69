//
// Created by rapha on 20/11/2023.
//

#ifndef ECELECARTEST_HEADER_H
#define ECELECARTEST_HEADER_H

// Structures de données pour stocker les informations lues
typedef struct {
    int exclusions[100][2];
    int exclusionCount;
} Exclusions;

typedef struct {
    int precedences[100][2];
    int arcCount;
} Precedences;

typedef struct {
    int operationNum[100];
    float operationTemp[100];
    int operationCount;
} Operations;

void fichier_exclusions();
void fichier_precedences();
void fichier_operations();
void fichier_temps_cycle();
void optimizeAssemblyLine();

#endif //ECELECARTEST_HEADER_H
