#include <ncurses.h>
#include "model.h"
#include "control.h"

void afficher_plateau(int **plateau, Model *model) {
    for (int i = 0; i < model->lignes; i++) {
        for (int j = 0; j < model->colonnes; j++) {
            if (plateau[i][j] == 0) {
                mvprintw(i, j * 2, "."); 
            } else if (plateau[i][j] == 1) {
                mvprintw(i, j * 2, "1"); 
            } else if (plateau[i][j] == 2) {
                mvprintw(i, j * 2, "2"); 
            }
        }
    }
}

void boucle_ncurses(int **plateau, Moto *moto1, Moto *moto2, Model *model) {
    int ch;
    Gagnant result = CONTINUER;

    while (result == CONTINUER) {
        clear();
        afficher_plateau(plateau, model);
        refresh();

        events_ncurses(moto1, moto2, model, plateau);

        result = avancer(plateau, moto1, moto2, model);
    }

    clear();
    if (result == JOUEUR1) {
        mvprintw(model->lignes / 2, model->colonnes, "Joueur 1 gagne!");
    } else if (result == JOUEUR2) {
        mvprintw(model->lignes / 2, model->colonnes, "Joueur 2 gagne!");
    } else {
        mvprintw(model->lignes / 2, model->colonnes, "Egalite!");
    }
    refresh();
    getch();
}

void lancer_ncurses(int **plateau, Moto *moto1, Moto *moto2, Model *model) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    boucle_ncurses(plateau, moto1, moto2, model);

    endwin();
}