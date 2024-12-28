#include "view_sdl.h"


// Les variables globales sont utiles ici puisque ça permet de ne pas utiliser des paramètres inutiles, j'aurai pu passer des pointeurs
// et mettre les SDL texture dans une structure, mais par rapport à la taille du projet c'était overkill, même si c'est pas toujours la meilleure pratique
SDL_Texture *StartBouton;
SDL_Renderer *renderer;
SDL_Texture *backgroundTexture;
SDL_Texture *Logo;
SDL_Window *window;
SDL_Texture *RestartBouton;


// destruction des ressources, si jamais y'a un problème a l'initialisation
void destroy_resources(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *backgroundTexture, SDL_Texture *StartBouton, SDL_Texture *RestartBouton) {
    if (RestartBouton) SDL_DestroyTexture(RestartBouton);
    if (StartBouton) SDL_DestroyTexture(StartBouton);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

// Affichage du plateau, en parcourant la boucle
void PrintPlateau(Model *model, int **plateau) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int cellWidth = width / (model->colonnes + 2);
    int cellHeight = (height - 100) / (model->lignes + 2);

    int offsetX = (width - (model->colonnes * cellWidth)) / 2;
    int offsetY = (height - (model->lignes * cellHeight) - 100) / 2;

    for (int i = 0; i < model->lignes; i++) {
        for (int j = 0; j < model->colonnes; j++) {
            SDL_Rect cellRect = { offsetX + j * cellWidth, offsetY + i * cellHeight, cellWidth, cellHeight };

            if (plateau[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else if (plateau[i][j] == 2) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }

            SDL_RenderFillRect(renderer, &cellRect);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer);
}

// Disparition du bouton 
void destroy_start_button() {
    SDL_RenderClear(renderer);
    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }
    SDL_RenderPresent(renderer);
}

// Affichage du bouton start (simple)
void afficher_bouton_start(SDL_Renderer *renderer, SDL_Texture *StartBouton, SDL_Texture *logo) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int logoWidth, logoHeight;
    SDL_QueryTexture(logo, NULL, NULL, &logoWidth, &logoHeight);

    logoWidth /= 2;
    logoHeight /= 2;

    SDL_Rect logoRect = { (width - logoWidth) / 2, 20, logoWidth, logoHeight };
    SDL_RenderCopy(renderer, logo, NULL, &logoRect);

    int buttonWidth = 200, buttonHeight = 100;
    SDL_Rect buttonRect = { (width - buttonWidth) / 2, (height - buttonHeight) / 2, buttonWidth, buttonHeight };
    SDL_RenderCopy(renderer, StartBouton, NULL, &buttonRect);

    SDL_RenderPresent(renderer);
}

// Affichage du bouton restart (simple)
void afficher_bouton_restart() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int buttonWidth = 200, buttonHeight = 100;
    SDL_Rect buttonRect = { (width - buttonWidth) / 2, height - buttonHeight - 25, buttonWidth, buttonHeight };
    SDL_RenderCopy(renderer, RestartBouton, NULL, &buttonRect);

    SDL_RenderPresent(renderer);
}

// Initialisation de la sdl, et gestion des erreurs
int initialisation_sdl(int height_sdl, int width_sdl) {


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        perror("Erreur SDL_Init");
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        perror("Erreur IMG_Init");
        SDL_Quit();
        return -1;
    }

    window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_sdl, height_sdl, SDL_WINDOW_SHOWN);
    if (!window) {
        perror("Erreur SDL_CreateWindow");
        destroy_resources(window, NULL, NULL, NULL, NULL);
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        perror("Erreur SDL_CreateRenderer");
        destroy_resources(window, NULL, NULL, NULL, NULL);
        return -1;
    }

    SDL_Surface *backgroundSurface = IMG_Load("src/utils/img/background.png");
    if (!backgroundSurface) {
        perror("Erreur IMG_Load (background)");
        destroy_resources(window, renderer, NULL, NULL, NULL);
        return -1;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    SDL_Surface *startButtonSurface = IMG_Load("src/utils/img/start_bouton.png");
    if (!startButtonSurface) {
        perror("Erreur IMG_Load (start bouton)");
        destroy_resources(window, renderer, backgroundTexture, NULL, NULL);
        return -1;
    }
    StartBouton = SDL_CreateTextureFromSurface(renderer, startButtonSurface);
    SDL_FreeSurface(startButtonSurface);

    SDL_Surface *logoSurface = IMG_Load("src/utils/img/logo.png");
    if (!logoSurface) {
        perror("Erreur IMG_Load (logo)");
        destroy_resources(window, renderer, backgroundTexture, StartBouton, NULL);
        return -1;
    }
    Logo = SDL_CreateTextureFromSurface(renderer, logoSurface);
    SDL_FreeSurface(logoSurface);

    SDL_Surface *restartButtonSurface = IMG_Load("src/utils/img/restart_bouton.png");
    if (!restartButtonSurface) {
        perror("Erreur IMG_Load (restart bouton)");
        destroy_resources(window, renderer, backgroundTexture, StartBouton, NULL);
        return -1;
    }
    RestartBouton = SDL_CreateTextureFromSurface(renderer, restartButtonSurface);
    SDL_FreeSurface(restartButtonSurface);





    SDL_Event event;
    int running = 1;
    Moto *moto1 = malloc(sizeof(Moto));
    Moto *moto2 = malloc(sizeof(Moto));
    Model *model = malloc(sizeof(Model));

    if (model == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // modulable :
    model->colonnes = 150;
    model->lignes = 100;

    int **plateau = creationDuJeu(moto1, moto2, model);

    // Démarrage, affichage du menu :
    SDL_SetRenderDrawColor(renderer, 19, 19, 40, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


    afficher_bouton_start(renderer, StartBouton, Logo);
    SDL_RenderPresent(renderer);

    events(window, &event, &running, moto1, moto2, model, plateau);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    afficher_bouton_restart(renderer, RestartBouton, Logo);

    destroy_resources(window, renderer, backgroundTexture, StartBouton, RestartBouton);

    return 0;
}
