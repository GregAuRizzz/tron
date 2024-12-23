#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <view/view_sdl.h>
#include <view/view_ncurses.h>

int main(int argc, char *argv[]) {
    char choix = ' ';
    int width = 50, height = 50; 

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
        initialisation_ncurses(height,width);

    } else {
        printf("Option non valide. Veuillez utiliser -ncurse ou -sdl.\n");
    }

    return 0;
}
