#include <SDL2/SDL.h>
#include <stdio.h>
#include "control.h"
#include "model/model.h"
#include "view/sdlInterface.h"

void events(SDL_Event *event, int *running, Moto * moto1, Moto * moto2,Model * model,int ** plateau) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *running = 0;
                break;

            case SDL_KEYDOWN:
                PrintPlateau(model,plateau);
                printf("%s\n",SDL_GetKeyName(event->key.keysym.sym));
                clavier_evenement(event->key.keysym.sym, moto1, moto2);
                break;

            case SDL_MOUSEBUTTONDOWN:
                clique_souris(event->button.x, event->button.y, running);
                // start_jeu(plateau,moto1,moto2,model);
                break;

            default:
                break;
        }
    }
}

void clique_souris(int mouseX, int mouseY, int *running) {
    int buttonWidth = 200;
    int buttonHeight = 100;
    int buttonX = (800 - buttonWidth) / 2;
    int buttonY = (600 - buttonHeight) / 2;

    if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
        mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        printf("Bouton cliqué\n");
        destroy_start_button();
        *running = 0;
    }
}

void clavier_evenement(SDL_Keycode key, Moto * moto1, Moto * moto2) {
    switch (key) {
        case SDLK_z:
            if ((moto1->directions == GAUCHE) || (moto1->directions == DROITE)) {
                moto1->directions = HAUT;
            }
            break;
        case SDLK_q:
            if ((moto1->directions == HAUT) || (moto1->directions == BAS)) {
                moto1->directions = GAUCHE;
            }
            break;
        case SDLK_s:
            if ((moto1->directions == GAUCHE) || (moto1->directions == DROITE)) {
                moto1->directions = BAS;
            }
            break;
        case SDLK_d:
            if ((moto1->directions == HAUT) || (moto1->directions == BAS)) {
                moto1->directions = DROITE;
            }
            break;
        case SDLK_UP:
            if ((moto2->directions == GAUCHE) || (moto2->directions == DROITE)) {
                moto2->directions = HAUT;
            }
            break;
        case SDLK_DOWN:
            if ((moto2->directions == DROITE) || (moto2->directions == GAUCHE)) {
                moto2->directions = BAS;
            }
            break;
        case SDLK_LEFT:
            if ((moto2->directions == HAUT) || (moto2->directions == BAS)) {
                moto2->directions = GAUCHE;
            }
            break;
        case SDLK_RIGHT:
            if ((moto2->directions == HAUT) || (moto2->directions == BAS)) {
                moto2->directions = DROITE;
            }
            break;
        default:
            break;
    }
}
