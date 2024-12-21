#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdlInterface.h"
#include "model/model.h"
#include "controller/control.h"

SDL_Texture *StartBouton;
SDL_Renderer *renderer;
SDL_Texture *backgroundTexture;
SDL_Texture *Logo;

void destroy_resources(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *backgroundTexture, SDL_Texture *StartBouton) {
    if (StartBouton) SDL_DestroyTexture(StartBouton);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void PrintPlateau(Model *model, int **plateau) {
    int i, j;
    int cellWidth = 800 / model->colonnes;
    int cellHeight = 600 / model->lignes;

    int offsetX = (800 - (model->colonnes * cellWidth)) / 2;
    int offsetY = (600 - (model->lignes * cellHeight)) / 2;

    for (i = 0; i < model->lignes - 2; i++) {
        for (j = 0; j < model->colonnes - 2; j++) {
            SDL_Rect cellRect = { offsetX + j * cellWidth, offsetY + i * cellHeight, cellWidth, cellHeight };

            if (plateau[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
            } 
            else if(plateau[i][j] == 2) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
            }

            SDL_RenderFillRect(renderer, &cellRect); 
        }
    }
    SDL_RenderPresent(renderer);
}

void destroy_start_button() {
    SDL_RenderClear(renderer);

    // Redessiner le fond
    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}

void afficher_bouton_start(SDL_Renderer *renderer, SDL_Texture *StartBouton,SDL_Texture * logo) {
    SDL_Rect buttonRect = { (800 - 200) / 2, (600 - 100) / 2, 200, 100 };
    SDL_RenderCopy(renderer, StartBouton, NULL, &buttonRect);

    SDL_Rect logoRect = { (600 - 200) / 2, (300 - 100) / 2, 500, 200 };
    SDL_RenderCopy(renderer, logo, NULL, &logoRect);
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

    SDL_Window *window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        perror("Erreur SDL_CreateWindow");
        destroy_resources(window, NULL, NULL, NULL);
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        perror("Erreur SDL_CreateRenderer");
        destroy_resources(window, NULL, NULL, NULL);
        return -1;
    }

    SDL_Surface *backgroundSurface = IMG_Load("src/utils/img/background.png");
    if (!backgroundSurface) {
        perror("Erreur IMG_Load (background)");
        destroy_resources(window, renderer, NULL, NULL);
        return -1;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (!backgroundTexture) {
        perror("Erreur SDL_CreateTextureFromSurface (background)");
        destroy_resources(window, renderer, NULL, NULL);
        return -1;
    }

    SDL_Surface *buttonSurface = IMG_Load("src/utils/img/start_bouton.png");
    if (!buttonSurface) {
        perror("Erreur IMG_Load (button)");
        destroy_resources(window, renderer, backgroundTexture, NULL);
        return -1;
    }

    StartBouton = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);

    if (!StartBouton) {
        perror("Erreur SDL_CreateTextureFromSurface (button)");
        destroy_resources(window, renderer, backgroundTexture, NULL);
        return -1;
    }


    SDL_Surface *LogoSurface = IMG_Load("src/utils/img/logo.png");
    if (!buttonSurface) {
        perror("Erreur IMG_Load (Logo)");
        destroy_resources(window, renderer, backgroundTexture, NULL);
        return -1;
    }
    Logo = SDL_CreateTextureFromSurface(renderer, LogoSurface);
    SDL_FreeSurface(LogoSurface);

    SDL_Event event;
    int running = 1;
    Moto *moto1 = malloc(sizeof(Moto));
    Moto *moto2 = malloc(sizeof(Moto));

    Model *model = malloc(sizeof(Model));
    if (model == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    model->colonnes = 50;
    model->lignes = 21;

    int **plateau = creationDuJeu(moto1, moto2, model);

    SDL_SetRenderDrawColor(renderer, 19, 19, 40, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    afficher_bouton_start(renderer, StartBouton,Logo);
    SDL_RenderPresent(renderer);

    events(&event, &running, moto1, moto2, model, plateau);

    destroy_resources(window, renderer, backgroundTexture, StartBouton);

    return 0;
}
