#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>


#include "model/model.h"
#include "controller/control.h"


int initialisation_sdl();

void destroy_start_button();

void PrintPlateau(Model *model, int **plateau);

void afficher_bouton_start();

void afficher_bouton_restart();

#endif
