#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "sdlInterface.h"
#include "model/model.h"

void destroy_erreur(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *backgroundTexture, SDL_Texture *buttonTexture) {
    if (buttonTexture) SDL_DestroyTexture(buttonTexture);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int initialisation_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        perror("Erreur SDL_Init");
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        perror("Erreur IMG_Init");
        SDL_Quit();
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        perror("Erreur SDL_CreateWindow");
        destroy_erreur(window, NULL, NULL, NULL);
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        perror("Erreur SDL_CreateRenderer");
        destroy_erreur(window, NULL, NULL, NULL);
        return -1;
    }

    SDL_Surface *backgroundSurface = IMG_Load("src/utils/img/background.png");
    if (!backgroundSurface) {
        perror("Erreur IMG_Load (background)");
        destroy_erreur(window, renderer, NULL, NULL);
        return -1;
    }

    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (!backgroundTexture) {
        perror("Erreur SDL_CreateTextureFromSurface (background)");
        destroy_erreur(window, renderer, NULL, NULL);
        return -1;
    }

    SDL_Surface *buttonSurface = IMG_Load("src/utils/img/start_bouton.png");
    if (!buttonSurface) {
        perror("Erreur IMG_Load (button)");
        destroy_erreur(window, renderer, backgroundTexture, NULL);
        return -1;
    }

    SDL_Texture *buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);

    if (!buttonTexture) {
        perror("Erreur SDL_CreateTextureFromSurface (button)");
        destroy_erreur(window, renderer, backgroundTexture, NULL);
        return -1;
    }

    SDL_Event event;
    int running = 1;
    int buttonWidth = 200;
    int buttonHeight = 100;
    int buttonX = (800 - buttonWidth) / 2;
    int buttonY = (600 - buttonHeight) / 2;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
                    mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
                    printf("click\n");
                    running = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 19, 19, 40, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_Rect buttonRect = {buttonX, buttonY, buttonWidth, buttonHeight};
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

        SDL_RenderPresent(renderer);
    }

    destroy_erreur(window, renderer, backgroundTexture, buttonTexture);

    return 0;
}
