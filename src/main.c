#include <stdio.h>
#include <stdlib.h>
#include <view/sdlInterface.h>

int main() {
    char choix;
    do {
        printf("\nSouhaitez-vous ncurses (n) ou sdl (s) ? (tapez s ou n) : ");
        choix = getchar();
        while (getchar() != '\n');
    } while (choix != 's' && choix != 'n');

    if (choix == 's') {
        printf("Lancement de SDL\n");
        initialisation_sdl();

    } else if (choix == 'n') {
        printf("Lancement de ncruse\n");
    }

    return 0;
}
