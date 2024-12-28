#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "view/view_sdl.h"
#include "controller/control.h"

#ifndef MODEL_H
#define MODEL_H

typedef enum Directions {HAUT,BAS,GAUCHE,DROITE} Directions;
typedef enum GAGNANT {JOUEUR1,JOUEUR2,CONTINUER,EGALITE} Gagnant;


typedef struct Moto {
    int x,y;
    Directions directions;
    int valeur;
} Moto;


typedef struct Model {
    int lignes,colonnes;
} Model;


const char* gagnant_message(Gagnant resultat);
int ** creationDuJeu(Moto * moto1,Moto * moto2,Model * model);
void start_jeu(SDL_Window * window,SDL_Event * event,int **plateau, Moto * moto1,Moto * moto2,Model * model,int *game_started);
Gagnant avancer(int **plateau, Moto *moto1, Moto *moto2,Model * model);
void free_jeu(int **plateau, Model model);
const char* gagnant_message(Gagnant resultat);

#endif