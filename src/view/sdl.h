#pragma once

#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} windowManager;

static int counter = 0;

/**
 * @brief Cette fonction essaie de créer une fenêtre. Si la SDL n'est pas encore
 * initialiée alors cette fonction le fera.
 *
 * @param name est le nom de la fenêtre.
 * @param w est la largeur de la fenêtre.
 * @param h est la hauteur de la fenêtre.
 * @return une fenêtre manager si possible, et null sinon.
 */
windowManager *windowManager_init(char *name, int w, int h);
void windowManager_destroy(windowManager *window);