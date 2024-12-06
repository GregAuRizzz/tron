#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL2/SDL.h>

#include "model/model.h"

struct Tron;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} windowManager;

typedef struct {
  void *data;
  void (*affichage)(void *data, struct Tron *game);
  int (*getNextAction)(void *data, int *ligne, int *colonne);
} userInterface;

int initialisation_sdl();


windowManager *windowManager_init(char *name, int w, int h);

void windowManager_destroy(windowManager *window);

#endif
