#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "model.h"

int **creationDuJeu() {
    int colonnes = 1000;  
    int lignes = 500;

    int **plateau = malloc(lignes * sizeof(int*));
    assert(plateau);

    for (int i = 0; i < lignes; i++) {
        plateau[i] = malloc(colonnes * sizeof(int));
        assert(plateau[i]);
    }

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            plateau[i][j] = 0; 
        }
    }

    return plateau;
}

void free_jeu(int **plateau, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(plateau[i]);
    }
    free(plateau);
}
