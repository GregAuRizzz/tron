#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <view/view_sdl.h>
#include <view/view_ncurses.h>

int main(int argc, char *argv[]) {
    char choix = ' ';
    int width = 600, height = 600;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-ncurse") == 0) {
            choix = 'n';
        } else if (strcmp(argv[i], "-sdl") == 0) {
            choix = 's';
        } else if (strcmp(argv[i], "-taille") == 0 && i + 2 < argc) {
            width = atoi(argv[i + 1]);
            height = atoi(argv[i + 2]);
            i += 2;
        }
    }

    if (choix == 's') {
        initialisation_sdl(width, height);

    } else if (choix == 'n') {
        width = width / 10;
        height = height / 10;
        if (width < 50 || height < 50) {
            width = 50;
            height = 50;
        }

        int menu_choice = display_menu();
        switch (menu_choice) {
            case 0: // Start Game
                initialisation_ncurses(height, width);
                break;
            case 1: // Quit
                printf("Merci d'avoir joué !\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }

    } else {
        printf("Option non valide. Veuillez utiliser -ncurse ou -sdl.\n");
    }

    return 0;
}
