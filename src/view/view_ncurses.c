#include <ncurses.h>
#include "model/model.h"
#include "controller/control.h"

void afficher_plateau(int **plateau, Model *model) {
    for (int i = 0; i < model->lignes; i++) {
        for (int j = 0; j < model->colonnes; j++) {
            char symbol = '.';
            if (plateau[i][j] == 1) {
                symbol = '1';
            } else if (plateau[i][j] == 2) {
                symbol = '2';
            }
            mvprintw(i, j * 2, "%c", symbol);
        }
    }
    refresh();
}


void boucle_ncurses(int **plateau, Moto *moto1, Moto *moto2, Model *model) {
    Gagnant result = CONTINUER;

    while (result == CONTINUER) {
        clear();

        afficher_plateau(plateau, model); 

        result = events_ncurses(moto1, moto2, plateau, model);

        refresh();  
        napms(200);
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


void initialisation_ncurses(int height, int width) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    resizeterm(height, width); 

    Moto *moto1 = malloc(sizeof(Moto));
    Moto *moto2 = malloc(sizeof(Moto));
    Model *model = malloc(sizeof(Model));

    model->lignes = height / 2;
    model->colonnes = width / 2;

    int **plateau = creationDuJeu(moto1, moto2, model);

    boucle_ncurses(plateau, moto1, moto2, model);

    free_jeu(plateau, *model);
    free(moto1);
    free(moto2);
    free(model);

    endwin();
}
