#include "control.h"

void events_pendant_le_jeu(SDL_Event *event, Moto *moto1, Moto *moto2, int *game_started, Model *model, int **plateau) {
    while (SDL_PollEvent(event) && game_started) {
        if (event->type == SDL_KEYDOWN) {
            break;
        }
    }
    PrintPlateau(model, plateau);
    clavier_evenement(event->key.keysym.sym, moto1, moto2);
}

void events(SDL_Window *window, SDL_Event *event, int *running, Moto *moto1, Moto *moto2, Model *model, int **plateau) {
    int game_started = 0;
    while (*running) {
        while (SDL_PollEvent(event)) {
            switch (event->type) {
                case SDL_QUIT:
                    *running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    clique_bouton_start(window, event, event->button.x, event->button.y, &game_started, moto1, moto2, plateau, model);
                    clique_bouton_restart(window, event, event->button.x, event->button.y, moto1, moto2, plateau, model,&game_started);
                    break;

                    break;
                default:
                    break;
            }
        }
    }
}


int events_ncurses(Moto *moto1, Moto *moto2, int **plateau, Model *model) {
    int ch = ERR;

    nodelay(stdscr, TRUE);

    if ((ch = getch()) != ERR) {
        switch (ch) {
            case 'z': 
                if (moto1->directions == GAUCHE || moto1->directions == DROITE) {
                    moto1->directions = HAUT;
                }
                break;
            case 'q':
                if (moto1->directions == HAUT || moto1->directions == BAS) {
                    moto1->directions = GAUCHE;
                }
                break;
            case 's': 
                if (moto1->directions == GAUCHE || moto1->directions == DROITE) {
                    moto1->directions = BAS;
                }
                break;
            case 'd': 
                if (moto1->directions == HAUT || moto1->directions == BAS) {
                    moto1->directions = DROITE;
                }
                break;
            case KEY_UP: 
                if (moto2->directions == GAUCHE || moto2->directions == DROITE) {
                    moto2->directions = HAUT;
                }
                break;
            case KEY_DOWN: 
                if (moto2->directions == GAUCHE || moto2->directions == DROITE) {
                    moto2->directions = BAS;
                }
                break;
            case KEY_LEFT: 
                if (moto2->directions == HAUT || moto2->directions == BAS) {
                    moto2->directions = GAUCHE;
                }
                break;
            case KEY_RIGHT: 
                if (moto2->directions == HAUT || moto2->directions == BAS) {
                    moto2->directions = DROITE;
                }
                break;
            default:
                break;
        }
    }
    return avancer(plateau, moto1, moto2, model);
}

int menu_navigation_ncurses(int current_choice, int num_options) {
    int key = getch(); 
    switch (key) {
        case KEY_UP: 
            current_choice = (current_choice == 0) ? num_options - 1 : current_choice - 1;
            break;
        case KEY_DOWN: 
            current_choice = (current_choice == num_options - 1) ? 0 : current_choice + 1;
            break;
        case '\n': 
            return -1; 
        default:
            break;
    }
    return current_choice;
}


void clique_bouton_restart(SDL_Window *window, SDL_Event *event, int mouseX, int mouseY, Moto *moto1, Moto *moto2, int **plateau, Model *model,int * game_started) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int buttonWidth = 200;
    int buttonHeight = 100;
    int buttonX = (width - buttonWidth) / 2;
    int buttonY = height - buttonHeight - 25;

    if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        free_jeu(plateau, *model);
        plateau = creationDuJeu(moto1, moto2, model);
        start_jeu(window, event, plateau, moto1, moto2, model, game_started);
    }
}


void clique_bouton_start(SDL_Window *window, SDL_Event *event, int mouseX, int mouseY, int *game_started, Moto *moto1, Moto *moto2, int **plateau, Model *model) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int buttonWidth = 200;
    int buttonHeight = 100;
    int buttonX = (width - buttonWidth) / 2;
    int buttonY = (height - buttonHeight) / 2;

    if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        *game_started = 1;
        destroy_start_button();
        start_jeu(window, event, plateau, moto1, moto2, model, game_started);
    }
}

void clavier_evenement(SDL_Keycode key, Moto *moto1, Moto *moto2) {
    switch (key) {
        case SDLK_z:
            if (moto1->directions == GAUCHE || moto1->directions == DROITE) {
                moto1->directions = HAUT;
            }
            break;
        case SDLK_q:
            if (moto1->directions == HAUT || moto1->directions == BAS) {
                moto1->directions = GAUCHE;
            }
            break;
        case SDLK_s:
            if (moto1->directions == GAUCHE || moto1->directions == DROITE) {
                moto1->directions = BAS;
            }
            break;
        case SDLK_d:
            if (moto1->directions == HAUT || moto1->directions == BAS) {
                moto1->directions = DROITE;
            }
            break;
        case SDLK_UP:
            if (moto2->directions == GAUCHE || moto2->directions == DROITE) {
                moto2->directions = HAUT;
            }
            break;
        case SDLK_DOWN:
            if (moto2->directions == DROITE || moto2->directions == GAUCHE) {
                moto2->directions = BAS;
            }
            break;
        case SDLK_LEFT:
            if (moto2->directions == HAUT || moto2->directions == BAS) {
                moto2->directions = GAUCHE;
            }
            break;
        case SDLK_RIGHT:
            if (moto2->directions == HAUT || moto2->directions == BAS) {
                moto2->directions = DROITE;
            }
            break;
        default:
            break;
    }
}
