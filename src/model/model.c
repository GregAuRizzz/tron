#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "model.h"
#include <unistd.h>
#include "view/sdlInterface.h"


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
    moto1->x = colonnes/5;
    moto1->y = lignes/2;
    moto1->valeur = 1;
    moto1->directions = HAUT;

    moto2->x = (colonnes/5)*4;
    moto2->y = lignes/2;
    moto2->valeur = 2;
    moto2->directions = BAS;

    plateau[moto1->y][moto1->x] = moto1->valeur;
    plateau[moto2->y][moto2->x] = moto2->valeur;

    printf("%d, %d\n",moto1->x,moto1->y);
    printf("%d, %d\n",moto2->x,moto2->y);
    return plateau;
}

void start_jeu(int **plateau, Moto * moto1,Moto * moto2,Model * model) {
    while (avancer(plateau,moto1,moto2, model) == CONTINUER) {
        PrintPlateau(model,plateau);
<<<<<<< HEAD
        usleep(400000);
    }; 
=======
        avancer(plateau,&moto1,&moto2);
        sleep(3);
    };
>>>>>>> 68f8036fcaed78f6d044559e10333ca20d3efe3a
}

Gagnant avancer(int **plateau, Moto *moto1, Moto *moto2,Model * model) {

    if (moto1->directions == HAUT && moto1->y > 0 && plateau[moto1->y-1][moto1->x] == 0) {
        moto1->y -= 1;
    } else if (moto1->directions == BAS && moto1->y < model->lignes - 1 && plateau[moto1->y+1][moto1->x] == 0) {
        moto1->y += 1;
    } else if (moto1->directions == DROITE && moto1->x < model->colonnes - 1 && plateau[moto1->y][moto1->x+1] == 0) {
        moto1->x += 1;
    } else if (moto1->directions == GAUCHE && moto1->x > 0 && plateau[moto1->y][moto1->x-1] == 0) {
        moto1->x -= 1;
    } else {
        printf("Joueur 2 gagné");
        return JOUEUR2;
    }

    if (moto2->directions == HAUT && moto2->y > 0 && plateau[moto2->y-1][moto2->x] == 0) {
        moto2->y -= 1;
    } else if (moto2->directions == BAS && moto2->y < model->lignes - 1 && plateau[moto2->y+1][moto2->x] == 0) {
        moto2->y += 1;
    } else if (moto2->directions == DROITE && moto2->x < model->colonnes - 1 && plateau[moto2->y][moto2->x+1] == 0) {
        moto2->x += 1;
    } else if (moto2->directions == GAUCHE && moto2->x > 0 && plateau[moto2->y][moto2->x-1] == 0) {
        moto2->x -= 1;
    } else {
        printf("Joueur 1 gagné");
        return JOUEUR1;
    }

    plateau[moto1->y][moto1->x] = moto1->valeur;
    plateau[moto2->y][moto2->x] = moto2->valeur;

    return CONTINUER;
}

void free_jeu(int **plateau, Model model) {
    for (int i = 0; i < model.lignes; i++) {
        free(plateau[i]);
    }
    free(plateau);
}
