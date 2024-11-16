#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdlInterface.h"
#include <assert.h>

int counter = 0;

windowManager *windowManager_init(char *name, int w, int h) {
    int counter = 0;
    if (counter == 0) {
        printf("[LOG] Initialisation de la SDL.\n");
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
            return NULL;
        }
    }

    windowManager *window = (windowManager *)malloc(sizeof(windowManager));
    assert(window);

    SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &window->window, &window->renderer);
    if (!window->window || !window->renderer) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre ou du renderer : %s\n", SDL_GetError());
        free(window);
        return NULL;
    }

    SDL_SetWindowTitle(window->window, name);
    counter++;
    printf("[LOG] Fenêtre créée avec succès. Nombre de fenêtres actives : %d\n", counter);

    return window;
}

int initialisation_sdl() {
    windowManager *wm = windowManager_init("Tron", 800, 600 );
        SDL_Event event;
        int running = 1;
        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = 0;
                }
            }

            // Couleur d'arrière-plan (noir)
            SDL_SetRenderDrawColor(wm->renderer, 19, 19, 40, 255);
            SDL_RenderClear(wm->renderer);
            SDL_RenderPresent(wm->renderer);
        }

        windowManager_destroy(wm);
        return 0;
}


void windowManager_destroy(windowManager *window) {
    if (!window || !window->window || !window->renderer) return;

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);

    counter--;
    printf("[LOG] Fenêtre détruite. Nombre de fenêtres actives : %d\n", counter);

    if (counter == 0) {
        SDL_Quit();
        printf("[LOG] SDL quittée.\n");
    }
}