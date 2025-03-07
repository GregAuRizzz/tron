#ifndef NCURSE_INTERFACE_H
#define NCURSE_INTERFACE_H

#include "model/model.h"
#include "controller/control.h"

void afficher_plateau(int **plateau, Model *model);
void boucle_ncurses(int **plateau, Moto *moto1, Moto *moto2, Model *model);
void initialisation_ncurses(int width, int height);
int display_menu();

#endif