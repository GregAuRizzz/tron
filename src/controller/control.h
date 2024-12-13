#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>
#include "model/model.h"
#include "view/sdlInterface.h"



void events(SDL_Event *event, int *running,Moto * moto1,Moto * moto2,Model * model,int ** plateau);
void clavier_evenement(SDL_Keycode key, Moto * moto1, Moto * moto2);
void clique_souris(int mouseX, int mouseY, int *running);

#endif
