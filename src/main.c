#include <stdio.h>
#include <stdlib.h>
#include "view/sdl.h"

int main() {
    char choix;
    do {
        printf("\nSouhaitez-vous ncurses (n) ou sdl (s) ? (s,n) : ");
        choix = getchar();
        while (getchar() != '\n');
    } while (choix != 's' && choix != 'n');

    if (choix == 'n') {
        printf("Lancement de SDL\n");
    } else if (choix == 's') {
        printf("Lancement de ncruse\n");
    }

    return 0;
}
