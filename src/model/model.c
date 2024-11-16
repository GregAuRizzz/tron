#include <stdio.h>
#include <assert.h>
#include <model.h>

typedef enum Direction {GAUCHE,DROITE,HAUT,BAS} Direction;

typedef struct Moto {
    Direction Direction;
};

int * creationDuJeu() {

    int colonnes = 100;
    int lignes = 100;
    int *plateau =  malloc(lignes*sizeof(int));

    for (int i = 0;i!=lignes;i++) {
        plateau[i] = malloc(colonnes*sizeof(int));
    }
    return plateau;
}