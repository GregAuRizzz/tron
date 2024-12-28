#include "control.h"


// Fonction qui s'active uniquement pendant que le jeu est en cours
void events_pendant_le_jeu(SDL_Event *event, Moto *moto1, Moto *moto2, int *game_started, Model *model, int **plateau) {
    while (SDL_PollEvent(event) && game_started) {
        if (event->type == SDL_KEYDOWN) {
            break;
        }
    }
    PrintPlateau(model, plateau);
    clavier_evenement(event->key.keysym.sym, moto1, moto2); // check si on peut changer de directions
}

// Capter les évents pour les boutons start/restart ainsi que si on quitte l'application
void events(SDL_Window *window, SDL_Event *event, int *running, Moto *moto1, Moto *moto2, Model *model, int **plateau) {
    int game_started = 0;
    while (*running) {
        while (SDL_PollEvent(event)) {
            switch (event->type) {
                case SDL_QUIT: // quitter
                    *running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN: // clique quelque part
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

// Copie de la fonction SDL clavier_evenement() qui permet de détecter les events, et avancer sur le plateau
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

// évènements ncurses, avec conditions ternaires prcq c'est cool un coup 
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

// Savoir si le bouton restart a été cliqué, dans le cas positif alors ça relance une partie 
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


// Calculer les positions du bouton start, qui permet de savoir si il est cliqué ou pas, si oui ça détruit le bouton 
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

// Switch case qui permet de savoir si on peut se déplacer, en fonction de la position actuelle
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
