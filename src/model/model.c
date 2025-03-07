#include "model.h"


// Affichage du gagnant
const char* gagnant_message(Gagnant resultat) {
    switch (resultat) {
        case JOUEUR1: return "Le joueur 1 a gagné !";
        case JOUEUR2: return "Le joueur 2 a gagné !";
        case EGALITE: return "Égalité !";
        case CONTINUER: return "";
        default: return "Erreur inconnue.";
    }
}


// Création du plateau qui est sous forme de tableaux, ainsi que placement des motos et instanciation des motos 
int **creationDuJeu(Moto *moto1, Moto *moto2, Model *model) {
    int colonnes = model->colonnes;
    int lignes = model->lignes;

    int **plateau = malloc(lignes * sizeof(int*));
    assert(plateau);

    for (int i = 0; i < lignes; i++) {
        plateau[i] = malloc(colonnes * sizeof(int));
        assert(plateau[i]);
    }

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            plateau[i][j] = 0;
        }
    }

    // On instancie les coordonnées des motos, ainsi que leur direction (choisis arbitrairement mais facilement modulable)
    moto1->x = colonnes / 5;
    moto1->y = lignes / 2;
    moto1->valeur = 1;
    moto1->directions = HAUT;

    moto2->x = (colonnes / 5) * 4;
    moto2->y = lignes / 2;
    moto2->valeur = 2;
    moto2->directions = BAS;

    // Les premières cases sont donc coloriés en fonction de la valeur
    plateau[moto1->y][moto1->x] = moto1->valeur;
    plateau[moto2->y][moto2->x] = moto2->valeur;
    
    return plateau;
}

// Boucle principale, qui permet de connaitre en temps réel les évents et retourne quel joueur a gagné 
void start_jeu(SDL_Window *window, SDL_Event *event, int **plateau, Moto *moto1, Moto *moto2, Model *model, int *game_started) {
    int width, height;

    // Tant que on peut avancer, on écoute les events
    while (avancer(plateau, moto1, moto2, model) == CONTINUER) {
        events_pendant_le_jeu(event, moto1, moto2, game_started, model, plateau);
        usleep(40000);
    }

    // On print les joueurs (pour l'instant console, mais on peut l'afficher en haut dans la sdl par exmeple)
    // problème au niveau de sdl_ttf pour aficher du texte donc impossible à faire
    Gagnant winner = avancer(plateau, moto1, moto2, model);
    if (winner == JOUEUR1) {
        printf("Joueur bleu gagnant \n");
    } else if (winner == JOUEUR2) {
        printf("Joueur rouge gagnant \n");
    } else {
        printf("Égalité\n");
    }
        
    afficher_bouton_restart();
    SDL_GetWindowSize(window, &width, &height);
}

// Permet d'avancer les motos, si et seulement si c'est possible et que la partie ne se termine pas, si y'a un gagnant il est retourné (structure Gagnant)
Gagnant avancer(int **plateau, Moto *moto1, Moto *moto2, Model *model) {
    int retour = 0;


    // on gère les directions de la moto 1
    if (moto1->directions == HAUT && moto1->y > 0 && plateau[moto1->y - 1][moto1->x] == 0) {
        moto1->y -= 1;
    } else if (moto1->directions == BAS && moto1->y < model->lignes - 1 && plateau[moto1->y + 1][moto1->x] == 0) {
        moto1->y += 1;
    } else if (moto1->directions == DROITE && moto1->x < model->colonnes - 1 && plateau[moto1->y][moto1->x + 1] == 0) {
        moto1->x += 1;
    } else if (moto1->directions == GAUCHE && moto1->x > 0 && plateau[moto1->y][moto1->x - 1] == 0) {
        moto1->x -= 1;
    } else {
        retour += 5; 
    }

    // on gère les directions de la moto 2
    if (moto2->directions == HAUT && moto2->y > 0 && plateau[moto2->y - 1][moto2->x] == 0) {
        moto2->y -= 1;
    } else if (moto2->directions == BAS && moto2->y < model->lignes - 1 && plateau[moto2->y + 1][moto2->x] == 0) {
        moto2->y += 1;
    } else if (moto2->directions == DROITE && moto2->x < model->colonnes - 1 && plateau[moto2->y][moto2->x + 1] == 0) {
        moto2->x += 1;
    } else if (moto2->directions == GAUCHE && moto2->x > 0 && plateau[moto2->y][moto2->x - 1] == 0) {
        moto2->x -= 1;
    } else {
        retour += 10;
    }

    // si l'une des motos a pour valeur la moto de l'autre et vice versa, alors égalité
    if (moto1->x == moto2->x && moto1->y == moto2->y) {
        return EGALITE;
    }

    // En fonction de l'incrémentation, on retourne qui a gagné
    if (retour == 0) {
        plateau[moto1->y][moto1->x] = moto1->valeur;
        plateau[moto2->y][moto2->x] = moto2->valeur;
    } else if (retour == 5) {
        return JOUEUR2; 
    } else if (retour == 10) {
        return JOUEUR1;
    } else if (retour == 15) {
        return EGALITE; 
    }

    return CONTINUER;  
}

// Free du jeu
void free_jeu(int **plateau, Model model) {
    for (int i = 0; i < model.lignes; i++) {
        free(plateau[i]);
    }
    free(plateau);
}
