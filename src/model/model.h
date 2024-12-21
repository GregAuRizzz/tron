#include "../view/sdlInterface.h"

#ifndef MODEL_H
#define MODEL_H


typedef enum Directions {HAUT,BAS,GAUCHE,DROITE} Directions;

typedef struct Moto {
    int x,y;
    Directions directions;
    int valeur;
} Moto;

typedef struct Model {
    int lignes,colonnes;
} Model;

int ** creationDuJeu(Moto * moto1, Moto * moto2, Model * model);

typedef enum GAGNANT {JOUEUR1,JOUEUR2,CONTINUER,EGALITE} Gagnant;

void start_jeu(SDL_Event * event,int **plateau, Moto * moto1,Moto * moto2,Model * model,int *game_started);

Gagnant avancer(int **plateau, Moto * moto1,Moto * moto2,Model * model);

void free_jeu(int **plateau, Model model);

#endif