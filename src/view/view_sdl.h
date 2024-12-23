#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "model/model.h"
#include "controller/control.h"

struct Tron;



typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} windowManager;


int initialisation_sdl();

void destroy_start_button();

void PrintPlateau(Model *model, int **plateau);

windowManager *windowManager_init(char *name, int w, int h);

void windowManager_destroy(windowManager *window);

void afficher_bouton_start();

void afficher_bouton_restart();



#endif
