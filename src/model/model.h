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

typedef enum GAGNANT {JOUEUR1,JOUEUR2,CONTINUER,EGALITE} Gagnant;

void start_jeu(int **plateau, Moto * moto1,Moto * moto2,Model * model);


<<<<<<< HEAD
Gagnant avancer(int **plateau, Moto * moto1,Moto * moto2,Model * model);

=======
>>>>>>> 68f8036fcaed78f6d044559e10333ca20d3efe3a

void free_jeu(int **plateau, Model model);

#endif