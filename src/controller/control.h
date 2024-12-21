// src/controller/control.h
#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>
#include "model/model.h"

// Déclaration des fonctions
void events_pendant_le_jeu(SDL_Event *event, Moto *moto1, Moto *moto2,int * game_started,Model * model,int ** plateau);
void events(SDL_Event *event, int *running, Moto *moto1, Moto *moto2, Model *model, int **plateau);
void clique_bouton_start(SDL_Event *event,int mouseX, int mouseY, int *game_started,Moto * moto1,Moto *moto2,int **plateau,Model * model);
void clavier_evenement(SDL_Keycode key, Moto *moto1, Moto *moto2);

#endif // CONTROL_H
