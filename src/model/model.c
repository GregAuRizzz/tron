#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "model.h"

int ** creationDuJeu(Moto * moto1,Moto * moto2,Model * model) {
    int colonnes = model->colonnes;
    int lignes = model->lignes;

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
    moto1->x = colonnes-(colonnes/3);
    moto1->y = lignes/2;
    moto2->x = (colonnes/3);
    moto2->y = lignes/2;

    return plateau;
}


typedef enum GAGNANT {JOUEUR1,JOUEUR2,CONTINUER} Gagnant;
Gagnant verif_collision(int **plateau, Moto moto1,Moto moto2) {
    int CoMoto1[2] = {moto1.x,moto1.y};
    int CoMoto2[2] = {moto2.x,moto2.y};
    // je teste si la moto est rentré dans l'autre moto :
    if ( (plateau[CoMoto1[1]][CoMoto1[0]] == (plateau[CoMoto2[1]][CoMoto2[0]] == 0)) || (plateau[CoMoto1[1]][CoMoto1[0]] == moto2.valeur && plateau[CoMoto2[1]][CoMoto2[0]] == moto1.valeur)) {
        return JOUEUR2;
    }
    // je teste si la moto 1 a rencontré un mur ou l'autre moto
    else if ((plateau[CoMoto1[1]][CoMoto1[0]] == 0) || (plateau[CoMoto1[1]][CoMoto1[0]] == moto2.valeur)) {
        return JOUEUR2;
    }
    // pareil qu'avant
    else if ((plateau[CoMoto2[1]][CoMoto2[0]] == 0) || (plateau[CoMoto2[1]][CoMoto2[0]] == moto1.valeur)) {
        return JOUEUR1;
    }
    else {
        return CONTINUER;
    }
}

void free_jeu(int **plateau, Model model) {
    for (int i = 0; i < model.lignes; i++) {
        free(plateau[i]);
    }
    free(plateau);
}
