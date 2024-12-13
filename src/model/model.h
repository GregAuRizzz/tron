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

int ** creationDuJeu(Moto * moto1, Moto * moto2, Model * model);

typedef enum GAGNANT {JOUEUR1,JOUEUR2,CONTINUER} Gagnant;

void start_jeu(int **plateau, Moto * moto1,Moto * moto2,Model * model);

Gagnant verif_collision(int **plateau, Moto * moto1,Moto * moto2);

void avancer(int **plateau, Moto * moto1,Moto * moto2);


void free_jeu(int **plateau, Model model);

#endif