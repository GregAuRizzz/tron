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

    moto2->x = (colonnes/5)*4;
    moto2->y = lignes/2;
    moto2->valeur = 2;

    plateau[moto1->y][moto1->x] = moto1->valeur;
    plateau[moto2->y][moto2->x] = moto2->valeur;

    printf("%d, %d\n",moto1->x,moto1->y);
    printf("%d, %d\n",moto2->x,moto2->y);
    return plateau;
}

void start_jeu(int **plateau, Moto * moto1,Moto * moto2,Model * model) {
    while (verif_collision(plateau,moto1,moto2) == CONTINUER) {
        PrintPlateau(model,plateau);
        avancer(plateau,&moto1,&moto2);
        sleep(3);
    };
}

void avancer(int **plateau, Moto * moto1,Moto * moto2) {
    printf("avancer\n");
    if (moto1->directions == HAUT) moto1->x -= 1;
    else if (moto1->directions == BAS) moto1->x += 1;
    else if (moto1->directions == DROITE) moto1->y -= 1;
    else if (moto1->directions == GAUCHE) moto1->y += 1;
    if (moto2->directions == HAUT) moto1->x -= 1;
        else if (moto2->directions == BAS) moto2->x += 1;
        else if (moto2->directions == DROITE) moto2->y -= 1;
        else if (moto2->directions == GAUCHE) moto2->y += 1;
    plateau[moto1->y][moto1->x] = moto1->valeur;
    plateau[moto2->y][moto2->x] = moto2->valeur;
}

Gagnant verif_collision(int **plateau, Moto * moto1,Moto * moto2) {
    int CoMoto1[2] = {moto1->x,moto1->y};
    int CoMoto2[2] = {moto2->x,moto2->y};
    // je teste si la moto est rentré dans l'autre moto :
    if ( (plateau[CoMoto1[1]][CoMoto1[0]] == (plateau[CoMoto2[1]][CoMoto2[0]] == -1)) || (plateau[CoMoto1[1]][CoMoto1[0]] == moto2->valeur && plateau[CoMoto2[1]][CoMoto2[0]] == moto1->valeur)) {
        return JOUEUR2;
    }
    // je teste si la moto 1 a rencontré un mur ou l'autre moto
    else if ((plateau[CoMoto1[1]][CoMoto1[0]] == -1) || (plateau[CoMoto1[1]][CoMoto1[0]] == moto2->valeur)) {
        return JOUEUR2;
    }
    // pareil qu'avant
    else if ((plateau[CoMoto2[1]][CoMoto2[0]] == -1) || (plateau[CoMoto2[1]][CoMoto2[0]] == moto1->valeur)) {
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
