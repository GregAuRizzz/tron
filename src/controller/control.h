#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include "model/model.h"
#include "view/view_sdl.h"
#include <ncurses.h>

void events_pendant_le_jeu(SDL_Event *event, Moto *moto1, Moto *moto2,int * game_started,Model * model,int ** plateau);
void events(SDL_Window * window,SDL_Event *event, int *running, Moto *moto1, Moto *moto2, Model *model, int **plateau);
int events_ncurses(Moto *moto1, Moto *moto2, int **plateau, Model *model);
void clique_bouton_start(SDL_Window * window, SDL_Event *event, int mouseX, int mouseY, int *game_started, Moto *moto1, Moto *moto2, int **plateau, Model *model);
void clique_bouton_restart(SDL_Window *window, SDL_Event *event, int mouseX, int mouseY, Moto *moto1, Moto *moto2, int **plateau, Model *model,int * game_started);
void clavier_evenement(SDL_Keycode key, Moto *moto1, Moto *moto2);
int menu_navigation_ncurses(int current_choice, int num_options);

#endif
