#include <ncurses.h>
#include "model/model.h"
#include "controller/control.h"

// Permet d'afficher le plateau en temps réel
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

// Boucle principale du jeu, retourne le gagnant
void boucle_ncurses(int **plateau, Moto *moto1, Moto *moto2, Model *model) {
    Gagnant result;

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); 

    const char *replay_prompt = "Voulez-vous rejouer ? (o/n)";

    int replay_x = (max_x - strlen(replay_prompt)) / 2;
    int replay_y = max_y / 4 + 2;

    do {
        result = CONTINUER;

        while (result == CONTINUER) {
            clear();
            afficher_plateau(plateau, model);

            result = events_ncurses(moto1, moto2, plateau, model);

            refresh();  
            napms(200);
        }

        clear();
        if (result == JOUEUR1) {
            mvprintw(max_y / 4 + 1, (max_x - 17) / 2, "Joueur 1 gagne!");
        } else if (result == JOUEUR2) {
            mvprintw(max_y / 4 + 1, (max_x - 17) / 2, "Joueur 2 gagne!");
        } else {
            mvprintw(max_y / 4 + 1, (max_x - 8) / 2, "Egalite!");
        }
        refresh();

        mvprintw(replay_y, replay_x, "%s", replay_prompt);
        refresh();

        char choice;
        do {
            choice = getch();
        } while (choice != 'o' && choice != 'n');

        if (choice == 'o') {
            free_jeu(plateau, *model);
            plateau = creationDuJeu(moto1, moto2, model);
        } else {
            break; 
        }
    } while (1);

    clear();
    mvprintw(max_y / 4, (max_x - 19) / 2, "Merci d'avoir joué !");
    refresh();
    napms(2000);
}

// Initialisation de la ncurse
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

// affichage du menu et navigation dedans
int display_menu() {
    initscr();           
    start_color();       
    noecho();            
    curs_set(FALSE);     
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);  
    init_pair(2, COLOR_WHITE, COLOR_BLACK); 

    const char *options[] = {
        "1. Lancer le jeu",
        "2. Quitter"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int choice = 0; 

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    const char *tron[] = {
        "_____ ____  ____  _   _",
        "  |  (  _ \\( __ )| \\ | |",
        "  |   )   /| __ ||  \\| |",
        "  |  (__\\_)(____)|__|\\_|"
    };

    int tron_height = sizeof(tron) / sizeof(tron[0]);

    int tron_x = (max_x - strlen(tron[0])) / 2;
    int tron_y = (max_y - tron_height) / 6;

    while (1) {
        clear(); 

        for (int i = 0; i < max_x; i++) {
            mvprintw(tron_y - 1, i, "_");
        }

        for (int i = 0; i < tron_height; i++) {
            mvprintw(tron_y + i, tron_x, "%s", tron[i]);
        }

        for (int i = 0; i < max_x; i++) {
            mvprintw(tron_y + tron_height, i, "_");
        }

        const char *title = "Bienvenue dans le jeu Tron !";
        mvprintw(tron_y + tron_height + 2, (max_x - strlen(title)) / 2, "%s", title);

        const char *instructions = "Utilisez les flèches pour naviguer, et Entrée pour sélectionner.";
        mvprintw(tron_y + tron_height + 3, (max_x - strlen(instructions)) / 2, "%s", instructions);

        for (int i = 0; i < num_options; ++i) {
            if (i == choice) {
                attron(COLOR_PAIR(1)); 
                mvprintw(max_y / 2 + i, (max_x - strlen(options[i])) / 2, "%s", options[i]);
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2)); 
                mvprintw(max_y / 2 + i, (max_x - strlen(options[i])) / 2, "%s", options[i]);
                attroff(COLOR_PAIR(2));
            }
        }

        int new_choice = menu_navigation_ncurses(choice, num_options);
        if (new_choice == -1) { 
            endwin(); 
            return choice;
        }
        choice = new_choice; 
    }

    endwin(); 
    return choice;
}