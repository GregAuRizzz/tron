#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

// Structure Bouton (17/11/2024)
typedef struct { 
    SDL_Rect rect;
    SDL_Color color;        
    void (*onClick)();      
} Button;

// Création bouton (17/11/2024)
void button(SDL_Renderer *renderer, Button button) {
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
    SDL_RenderFillRect(renderer, &button.rect);
}

// EventClick bouton (17/11/2024)
void buttonEvent(Button *button, SDL_Event *event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        if (x >= button->rect.x && x <= button->rect.x + button->rect.w &&
            y >= button->rect.y && y <= button->rect.y + button->rect.h) {
            if (button->onClick) {
                button->onClick();
            }
        }
    }
}

SDL_Texture *renderText(const char *message, const char *fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    if (!font) {
        fprintf(stderr, "Erreur TTF_OpenFont : %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
    if (!surf) {
        TTF_CloseFont(font);
        fprintf(stderr, "Erreur TTF_RenderText_Blended : %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

// Pour test le Bouton (17/11/2024)
void startGame() {
    printf("Le jeu commence !\n");
}

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        fprintf(stderr, "Erreur IMG_Init : %s\n", IMG_GetError());
        return -1;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer) != 0) {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

void setWindowColor(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *image = NULL;
    SDL_Texture *textTexture = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color noir = {0, 0, 0, 255};

    if (init(&window, &renderer, 640, 480) != 0)
        goto Quit;

    image = IMG_LoadTexture(renderer, "images/fond_accueil.jpg");
    if (!image) {
        fprintf(stderr, "Erreur IMG_LoadTexture : %s\n", IMG_GetError());
        goto Quit;
    }

    Button startButton = {{220, 190, 200, 100}, {0, 128, 255, 0}, startGame};

    textTexture = renderText("Start", "font/arcade.ttf", noir, 24, renderer);
    if (!textTexture) {
        goto Quit;
    }

    SDL_Rect textRect = {0, 0, 0, 0};
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = startButton.rect.x + (startButton.rect.w - textRect.w) / 2;
    textRect.y = startButton.rect.y + (startButton.rect.h - textRect.h) / 2;

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            buttonEvent(&startButton, &event);
        }

        setWindowColor(renderer, blanc);
        SDL_RenderCopy(renderer, image, NULL, NULL);
        button(renderer, startButton);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
    }

    statut = EXIT_SUCCESS;

Quit:
    if (textTexture)
        SDL_DestroyTexture(textTexture);
    if (image)
        SDL_DestroyTexture(image);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return statut;
}
