#ifndef MODEL_H
#define MODEL_H


typedef enum Directions {HAUT,BAS,GAUCHE,DROITE} Directions;

typedef struct Moto {
    int x,y;
    Directions directions;
    int valeur; // Moto 1 = 1 moto 2 = 2, et mur = 0 par exemple
} Moto;

typedef struct Model {
    int lignes,colonnes;
} Model;

int ** creationDuJeu(Moto * m,Moto * m2,Model * model);


void free_jeu(int **plateau, Model model);

#endif